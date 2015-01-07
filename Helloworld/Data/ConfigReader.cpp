
#include "ConfigReader.h"
//#include "CCFileUtils.h"
#include<cstdio>
#include "cocos2d.h"
USING_NS_CC;


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


bool CConfigReader::init(CConfigReader::path_type path) {
	if( _initialized ) return false;

	//FILE* fp = fopen(, "r");

	unsigned long buffSize = 0l;
//	m_pBuffer = CCFileUtils::getFileData(path.c_str(), "rb", &buffSize);
    m_pBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &buffSize);
	if( !m_pBuffer ) return false;
	m_Pos = 0l;
	m_bufferSize = buffSize;
	//CCLOG("start loading %s, size %u",path.c_str(),buffSize);
//	int nRow = 0;
	while(true) {
		row_type current_row;
		if( !readRow(current_row) ) break;
		_table.push_back(current_row);
	}
    // [2014-06-17] memory leaks?
    CC_SAFE_DELETE_ARRAY(m_pBuffer);
	//CCLOG("load data end %s",path.c_str());
	//fclose(fp);
	return (_initialized = true);
}

bool CConfigReader::readRow(CConfigReader::row_type &pRow) {
	while(true) {
		CConfigReader::cell_type current_cell;
		char c=readCell(current_cell);
		if( current_cell.size()>0 || c!=(char)(EOF) )
			pRow.push_back(current_cell);
		if( c!=',' )break;
	}
	return ( pRow.size()>0 );
}
char CConfigReader::FGETC()
{
	if (m_Pos == m_bufferSize)
	{
		return EOF;
	}
	return m_pBuffer[m_Pos++];
}
char CConfigReader::readCell(CConfigReader::cell_type &pCell) {
	char c;
	while(true) { //leading \r \n
		c=FGETC();
		if( c==(char)(EOF) ) return c; //文件结尾
		if( c!='\r' && c!='\n' ) break;
	}
	int quote_count = 0;
	if( c=='"' ) {
		quote_count = 1;
		c=FGETC();
	}
	while(true) {
		if( c=='"' ) {
			quote_count++;
			if( quote_count&1 ) pCell+=c; //奇数个引号时添加引号
		} else if( c==',' ) {
			if( quote_count&1 ) pCell+=c; //奇数个引号时','不是分隔符
			else break;
		} else if( c=='\n' || c=='\r' || c==(char)(EOF) ) {
			break;
		} else {
			if (c == 'n' && pCell.size() && pCell[pCell.size() - 1] == '\\') {
				pCell[pCell.size() - 1] = '\n';
			}
			else {
				pCell+=c;
			}
		}
		c=FGETC();
	}
	return c; //返回最后一个字符
}
//#endif
