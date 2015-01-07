#pragma once

#ifndef _DYNAMIC_STRUCT_H_
#define _DYNAMIC_STRUCT_H_

#include "ByteBuffer.h"
#include "AnyType.h"
#include <set>
#include <sstream>

inline ByteBuffer& operator>>(ByteBuffer& lhs,AnyType& rhs) {
	unsigned char type;
	lhs>>type;
	switch(type){
		case eAnyTypeInt8:		rhs.set(lhs.read<char>()); break;
		case eAnyTypeInt16:		rhs.set(lhs.read<short>()); break;
		case eAnyTypeInt32:		rhs.set(lhs.read<int>()); break;
		case eAnyTypeUInt8:		rhs.set(lhs.read<unsigned char>()); break;
		case eAnyTypeUInt16:	rhs.set(lhs.read<unsigned short>()); break;
		case eAnyTypeUInt32:	rhs.set(lhs.read<unsigned int>()); break;
		case eAnyTypeFloat:		rhs.set(lhs.read<float>()); break;
		case eAnyTypeDouble:	rhs.set(lhs.read<double>()); break;
		case eAnyTypeString:	{std::string s;lhs>>s;rhs.setObject(s);} break;
		case eAnyTypeVector:	{std::vector<AnyType> v;lhs>>v;rhs.setObject(v);} break;
		case eAnyTypeMap1A:		{std::map<unsigned char,AnyType> m;lhs>>m;rhs.setObject(m);} break;
		//case eAnyTypeMapAA:		{std::map<AnyType,AnyType> m;lhs>>m;rhs.setObject(m);} break;
	}
	return lhs;
}
inline ByteBuffer& operator<<(ByteBuffer& lhs,const AnyType& rhs) {
	lhs<<(unsigned char)rhs.type();
	switch(rhs.type()){
		case eAnyTypeInt8:		lhs<<rhs.get<int8>(); break;
		case eAnyTypeInt16:		lhs<<rhs.get<int16>(); break;
		case eAnyTypeInt32:		lhs<<rhs.get<int32>(); break;
		case eAnyTypeUInt8:		lhs<<rhs.get<uint8>(); break;
		case eAnyTypeUInt16:	lhs<<rhs.get<uint16>(); break;
		case eAnyTypeUInt32:	lhs<<rhs.get<uint32>(); break;
		case eAnyTypeFloat:		lhs<<rhs.get<float>(); break;
		case eAnyTypeDouble:	lhs<<rhs.get<double>(); break;
		case eAnyTypeString:	lhs<<rhs.get<std::string>(); break;
		case eAnyTypeVector:	lhs<<rhs.get<std::vector<AnyType> >(); break;
		case eAnyTypeMap1A:		lhs<<rhs.get<std::map<unsigned char,AnyType> >(); break;
		//case eAnyTypeMapAA:		lhs<<rhs.get<std::map<AnyType,AnyType> >(); break;
	}
	return lhs;
}

class CDynamicStruct {
public:
	typedef unsigned char key_type;
	//***** won't clear before load/save *****//
	//compact{uint8 count;(key=0)AnyType data;(key=1)AnyType data;...(key=count-1)AnyType data;}
	void loadDataCompact(ByteBuffer& data) {
		key_type count;
		data >> count;
		for(key_type i=0;i<(unsigned int)count;i++) data >> _data[i];
	}
	//loose{uint8 count;uint8 key;AnyType data;uint8 key;AnyType data;...;}
	void loadDataLoose(ByteBuffer& data) {
		key_type count;
		data >> count;
		while(count--){
			key_type key;
			data >> key;
			data >> _data[key];
		}
	}
	//compact
	bool saveDataCompact(ByteBuffer& data) const {
		unsigned int count = _data.size();
		for(key_type i=0;i<count;i++)
			if( _data.find(i)==_data.end() ) return false; //not continous, fail
		data << (key_type)count;
		for(std::map<key_type,AnyType>::const_iterator iter=_data.begin();iter!=_data.end();iter++)
			data << iter->second;
		return true;
	}
	//loose
	void saveDataLoose(ByteBuffer& data) const {
		data << (key_type)_data.size();
		for(std::map<key_type,AnyType>::const_iterator iter=_data.begin();iter!=_data.end();iter++)
			data << iter->first << iter->second;
	}
	//dirty
	void saveDataDirty(ByteBuffer& data) const {
		data << (key_type)_dirty.size();
		for(std::set<key_type>::const_iterator iter=_dirty.begin();iter!=_dirty.end();iter++)
			data << (key_type)(*iter) << _data.find(*iter)->second;
	}
	void toMap(std::map<key_type, AnyType> & mapData) const {
		mapData.clear();
		for(std::map<key_type,AnyType>::const_iterator iter=_data.begin();iter!=_data.end();iter++)
			mapData[iter->first] = iter->second;
	}
	std::string toString() const {
		std::ostringstream out;
		for(std::map<key_type,AnyType>::const_iterator iter=_data.begin();iter!=_data.end();iter++) {
			out << (int)iter->first << ':';
			eAnyType type=iter->second.type();
			if( isAnyTypeUnsignedInteger(type) )
				out << iter->second.getUnsignedInteger();
			else if( isAnyTypeSignedInteger(type) )
				out << iter->second.getSignedInteger();
			else if( isAnyTypeRealNumber(type) )
				out << iter->second.getDouble();
			else if( isAnyTypeObject(type) ) {
				if( type==eAnyTypeString )
					out << '"' << iter->second.get<std::string>() << '"';
				else if( type==eAnyTypeVector )
					out << "(vector)";
				else
					out << "(object)";
			} else out << "(pointer/unknown)";
			out << '\n';
		}
		return out.str();
	}

	//property
	AnyType getProperty(key_type key) { return _data[key]; }
	void setProperty(key_type key,AnyType value) {
		std::map<key_type,AnyType>::iterator iter = _data.find(key);
		if( iter==_data.end() ) {
			_data.insert(std::pair<key_type,AnyType>(key,value));
			_dirty.insert(key);
		} else if( !(iter->second==value) ) {
			iter->second = value;
			_dirty.insert(key);
		}
	}
	void clear() { _data.clear(); }
	void clearDirtyFlag() { _dirty.clear(); }
	unsigned int countProperty() { return _data.size(); }
	key_type countDirty() { return _dirty.size(); }
private:
	std::map<key_type,AnyType> _data;
	std::set<key_type> _dirty; //only response to setProperty
};

#endif
