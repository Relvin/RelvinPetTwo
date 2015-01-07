#ifndef __CsvReader_h__
#define __CsvReader_h__

#include <string>
#include <vector>
#include <map>

/**
 *
 csv文件格式规则：
 
 1、用换行符分割数据行，每一行的单元格内容之间用逗号分隔。
 
 2、如果单元格的内容本身有逗号，这个单元格的内容将会用引号包含。
 
 3、如果单元格的内容本身有引号，
 
 引号不在首或尾，这个单元格内容不会被引号包含。
 
 引号在首或尾，这个单元格内容会被引号包含且原来首尾的引号会被转义。
 
 */

class CsvReader
{
public:
    
    typedef std::string                 CSV_PATH_TYPE;
    typedef std::string                 CSV_CELL_TYPE;
    typedef std::vector<CSV_CELL_TYPE>  CSV_ROW_TYPE;
    typedef std::vector<CSV_ROW_TYPE>   CSV_TABLE_TYPE;
    typedef unsigned int                CSV_SIZE_TYPE;
    
    // 完整文件路径}
    CsvReader( const CSV_PATH_TYPE path );
    virtual ~CsvReader();
    
    bool load( CSV_SIZE_TYPE colAsKey = 0, bool withColumnHeader = false );
    bool loadWithData( const char* data, CSV_SIZE_TYPE colAsKey = 0, bool withColumnHeader = false );
    
    CSV_SIZE_TYPE rowCount() const;
    
    CSV_SIZE_TYPE colCount() const;
    
    const CSV_ROW_TYPE* getRow( CSV_SIZE_TYPE rowIdx ) const;

    const CSV_ROW_TYPE* findByKey( CSV_CELL_TYPE key ) const;
    
    const CSV_CELL_TYPE* getCell( CSV_SIZE_TYPE rowIdx, CSV_SIZE_TYPE colIdx ) const;
    
    int getColumnIdxByHeaderId( int id ) const;

protected:
    
    bool loadInner( CSV_SIZE_TYPE colAsKey, bool withColumnHeader );

    const char *m_pBuffer;
    unsigned long m_pos;
    unsigned long m_bufferSize;
    
    bool m_initialized;
    
    std::map< CSV_CELL_TYPE, const CSV_ROW_TYPE* > m_keyMap;
    
    CSV_PATH_TYPE   m_filePath;
    CSV_TABLE_TYPE  m_table;
    CSV_ROW_TYPE	m_header;
    
private:
    
    bool readRow( CSV_ROW_TYPE& row );
    char readCell( CSV_CELL_TYPE& cell );
    char readChar();
    unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
    
};

#endif
