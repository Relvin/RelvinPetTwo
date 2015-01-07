#pragma once

#ifndef _ANY_TYPE_H_
#define _ANY_TYPE_H_

#include<string>
#include<vector>
#include<map>

typedef enum {
	//integer
	eAnyTypeIntegerType = 0x00,
	eAnyTypeInt8,
	eAnyTypeUInt8,
	eAnyTypeInt16,
	eAnyTypeUInt16,
	eAnyTypeInt32,
	eAnyTypeUInt32,
	eAnyTypeInt64,
	eAnyTypeUInt64,

	//real number
	eAnyTypeRealNumberType = 0x20,
	eAnyTypeFloat,
	eAnyTypeDouble,

	//pointers
	eAnyTypePointerType = 0x40,
	eAnyTypePString,
	eAnyTypePVoid,

	//object, will delete
	eAnyTypeObjectType = 0x60,
	eAnyTypeString,
	eAnyTypeVector, //vector<anytype>
	eAnyTypeMap1A, //map<unsigned char,anytype>
	eAnyTypeMapAA, //map<anytype,anytype>

	eAnyTypeMask = 0xe0,
	eAnyTypeUnknown = 0x80,
} eAnyType; //unsigned char

class AnyType;

template<typename T>
inline eAnyType getParameterType() { return eAnyTypeUnknown; }
template<>inline eAnyType getParameterType<unsigned char>() { return eAnyTypeUInt8; }
template<>inline eAnyType getParameterType<unsigned short>() { return eAnyTypeUInt16; }
template<>inline eAnyType getParameterType<unsigned int>() { return eAnyTypeUInt32; }
template<>inline eAnyType getParameterType<char>() { return eAnyTypeInt8; }
template<>inline eAnyType getParameterType<short>() { return eAnyTypeInt16; }
template<>inline eAnyType getParameterType<int>() { return eAnyTypeInt32; }
template<>inline eAnyType getParameterType<float>() { return eAnyTypeFloat; }
template<>inline eAnyType getParameterType<double>() { return eAnyTypeDouble; }
template<>inline eAnyType getParameterType<void*>() { return eAnyTypePVoid; }
template<>inline eAnyType getParameterType<std::string*>() { return eAnyTypePString; }
template<>inline eAnyType getParameterType<std::string>() { return eAnyTypeString; }
template<>inline eAnyType getParameterType<std::vector<AnyType> >() { return eAnyTypeVector; }
template<>inline eAnyType getParameterType<std::map<unsigned char,AnyType> >() { return eAnyTypeMap1A; }
template<>inline eAnyType getParameterType<std::map<AnyType,AnyType> >() { return eAnyTypeMapAA; }

inline bool isAnyTypeInteger	(eAnyType e) { return (((unsigned char)e)&eAnyTypeMask)==eAnyTypeIntegerType; }
inline bool isAnyTypeRealNumber	(eAnyType e) { return (((unsigned char)e)&eAnyTypeMask)==eAnyTypeRealNumberType; }
inline bool isAnyTypePointer	(eAnyType e) { return (((unsigned char)e)&eAnyTypeMask)==eAnyTypePointerType; }
inline bool isAnyTypeObject		(eAnyType e) { return (((unsigned char)e)&eAnyTypeMask)==eAnyTypeObjectType; }
inline bool isAnyTypeUnknown	(eAnyType e) { return (((unsigned char)e)&eAnyTypeMask)==eAnyTypeUnknown; }
inline bool isAnyTypeUnsignedInteger(eAnyType e) { return isAnyTypeInteger(e) && !(((unsigned char)e)&1); }
inline bool isAnyTypeSignedInteger(eAnyType e) { return isAnyTypeInteger(e) && (((unsigned char)e)&1); }

void* copyObject(eAnyType t,const void* p);
void deleteObject(eAnyType t,void* p);
bool isObjectEqual(eAnyType t,const void* p1,const void* p2);

class AnyType {
public:
	//-----constructor/destructor-----//
	AnyType():_data((void*)0),_type(eAnyTypePVoid) {}
	template<typename T> //non-object
	AnyType(T data):_type(getParameterType<T>()),_data(data) {}
	template<typename T> //object
	AnyType(const T& data,bool copy):_type(getParameterType<T*>()),_data(&data) {
		if(copy) {
			_type = getParameterType<T>();
			_data.m_pVoid = copyObject(_type,_data.m_pVoid);
		}
	}
	AnyType(const AnyType& rhs):_data(rhs._data),_type(rhs._type) {
		if(isAnyTypeObject(_type))
			_data.m_pVoid = copyObject(_type,_data.m_pVoid);
	}
	~AnyType() { clear(); }

	//-----property:type,get,set-----//
	eAnyType type() const { return _type; }
	template<typename T>
	T& get() {
		if(isAnyTypeObject(getParameterType<T>()))
			return *(T*)_data.m_pVoid;
		else
			return *(T*)(&_data);
	}
	template<typename T>
	const T& get() const {
		if(isAnyTypeObject(getParameterType<T>()))
			return *(const T*)_data.m_pVoid;
		else
			return *(const T*)(&_data);
	}
	unsigned int getUnsignedInteger() const { //for uint8/16/32, else return 0
		if(_type==eAnyTypeUInt8) return _data.m_uInt8;
		if(_type==eAnyTypeUInt32) return _data.m_uInt32;
		if(_type==eAnyTypeUInt16) return _data.m_uInt16;
		return 0;
	}
	int getSignedInteger() const { //for int8/16/32
		if(_type==eAnyTypeInt8) return _data.m_int8;
		if(_type==eAnyTypeInt32) return _data.m_int32;
		if(_type==eAnyTypeInt16) return _data.m_int16;
		return 0;
	}
	double getDouble() const { //for int/uint/float/double
		if(isAnyTypeRealNumber(_type)) {
			if(_type==eAnyTypeDouble) return _data.m_double;
			if(_type==eAnyTypeFloat) return _data.m_float;
		} else if(isAnyTypeUnsignedInteger(_type)) return getUnsignedInteger();
		else if(isAnyTypeSignedInteger(_type)) return getSignedInteger();
		return 0;
	}
	template<typename T> //non-object
	void set(T data) {
		clear();
		_type = getParameterType<T>();
		_data = uAnyType(data);
	}
	template<typename T> //object
	void setObject(const T& data) {
		clear();
		_type = getParameterType<T>();
		_data.m_pVoid = new T(data);
	}
	void set(const AnyType& rhs) {
		clear();
		_type = rhs._type;
		if(isAnyTypeObject(_type))
			_data.m_pVoid = copyObject(_type,rhs._data.m_pVoid);
		else
			_data = rhs._data;
	}

	//-----functions:del,clear-----//
	template<typename T>
	void del() {
		if(_data.m_pVoid && isAnyTypePointer(_type)) {
			delete (T*)(_data.m_pVoid);
			_data.m_pVoid = 0;
		}
	}
	void clear() {
		if(isAnyTypeObject(_type)) {
			deleteObject(_type,_data.m_pVoid);
			_data.m_pVoid = 0;
		}
	}

	//-----operator-----//
	template<typename T>
	AnyType& operator=(const T& rhs) {
		if( isAnyTypeObject(getParameterType<T>()) )
			setObject(rhs);
		else
			set(rhs);
		return *this;
	}
	AnyType& operator=(const AnyType& rhs) {
		set(rhs);
		return *this;
	}
	bool operator==(const AnyType& rhs) const {
		if( _type!=rhs._type ) return false;
		if( isAnyTypeObject(_type) ) {
			return isObjectEqual(_type,_data.m_pVoid,rhs._data.m_pVoid);
		} else {
			if( _type==eAnyTypeInt8 || _type==eAnyTypeUInt8 ) return _data.m_int8==rhs._data.m_int8;
			if( _type==eAnyTypeDouble ) return _data.m_double==rhs._data.m_double;
			if( _type==eAnyTypeInt16 || _type==eAnyTypeUInt16 ) return _data.m_int16==rhs._data.m_int16;
			return _data.m_int32==rhs._data.m_int32;
		}
	}
private:
	union uAnyType {
		uAnyType(char i8):m_int8(i8){}
		uAnyType(short i16):m_int16(i16){}
		uAnyType(int i32):m_int32(i32){}
		uAnyType(unsigned char u8):m_uInt8(u8){}
		uAnyType(unsigned short u16):m_uInt16(u16){}
		uAnyType(unsigned int u32):m_uInt32(u32){}
		uAnyType(float f):m_float(f){}
		uAnyType(double d):m_double(d){}
		template<typename T>
		uAnyType(T* p):m_pVoid((void*)p){}
		char m_int8;
		short m_int16;
		int m_int32;
		unsigned char m_uInt8;
		unsigned short m_uInt16;
		unsigned int m_uInt32;
		float m_float;
		double m_double;
		void* m_pVoid;
		//for debug
		std::string* m_pString;
		std::vector<AnyType>* m_pVector;
		std::map<unsigned char,AnyType>* m_pMap1A;
		std::map<AnyType,AnyType>* m_pMapAA;
	};
	uAnyType _data;
	eAnyType _type;
};


#endif