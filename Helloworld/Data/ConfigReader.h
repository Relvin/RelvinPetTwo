#pragma once

#ifndef _CONFIG_READER_H_
#define _CONFIG_READER_H_


#include<vector>
#include<string>
#include<cassert>
#include "cocos2d.h"


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//.csv file reader
class CConfigReader {
public:
	typedef std::string path_type;
	typedef std::string cell_type;
	typedef std::vector<cell_type> row_type;
	typedef std::vector<row_type> table_type;
	typedef unsigned int size_type;

	CConfigReader():_initialized(false){}

	bool init(path_type path);

	//property
	bool initialized() const {
		return _initialized;
	}
	size_type size() const {
		return _table.size();
	}
	size_type rowCount() const {
		return _table.size();
	}
	size_type colCount() const {
		if( !initialized() ) return 0;
		if( !_table.size() ) return 0;
		return _table[0].size();
	}
	row_type row(size_type r) const {
		if( r>=_table.size() ) return row_type();
		return _table[r];
	}
	cell_type cell(size_type r,size_type c) const {
		row_type current_row = row(r);
		if( c>=current_row.size() ) return cell_type();
		return current_row[c];
	}
private:
	//hidden private function
	bool readRow(CConfigReader::row_type& pRow);
	char readCell(CConfigReader::cell_type& pCell);

	char FGETC();
private:
	table_type _table;
	bool _initialized;

	unsigned char * m_pBuffer;
	unsigned long m_Pos;
	unsigned long m_bufferSize;
};
//#endif
#endif
