#include "CsvReader.h"
#include "Defines.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Log.h"

#ifdef COCOS2D_VERSION
#include "cocos2d.h"
#endif

CsvReader::CsvReader( const CSV_PATH_TYPE path )
:m_filePath( path ), m_bufferSize(0), m_pos(0), m_pBuffer(NULL)
, m_initialized( false )
{
}

CsvReader::~CsvReader()
{
    if ( m_pBuffer )
    {
        delete[] m_pBuffer;
    }
}

bool CsvReader::load( CSV_SIZE_TYPE colAsKey, bool withColumnHeader )
{
    if ( m_initialized ) return false;
    
#ifdef COCOS2D_VERSION
    m_pBuffer = (const char*)cocos2d::CCFileUtils::sharedFileUtils()->getFileData( m_filePath.c_str(), "rb", &m_bufferSize );
#else
    m_pBuffer = getFileData( m_filePath.c_str(), "rb", &m_bufferSize );
#endif
    
    bool ret = loadInner( colAsKey, withColumnHeader );
    
    CC_SAFE_DELETE_ARRAY(m_pBuffer);
//    // delete buffer
//    // @yuxiaofei
//    if (m_pBuffer) {
//        delete[] m_pBuffer;
//        m_pBuffer = 0;
//    }
    
    return ret;
}

bool CsvReader::loadWithData( const char* data, CSV_SIZE_TYPE colAsKey, bool withColumnHeader )
{
	m_pBuffer 		= data;
	m_bufferSize	= strlen( m_pBuffer );
	bool ret = loadInner( colAsKey, withColumnHeader );
	m_pBuffer		= 0;	// prevent delete
	return ret;
}

bool CsvReader::loadInner( CSV_SIZE_TYPE colAsKey, bool withColumnHeader )
{
	if ( !m_pBuffer ) return false;

	m_pos = 0L;
	m_table.clear();

	while ( true )
	{
		CSV_ROW_TYPE row;
		if ( !readRow( row ) )
			break;

		if ( m_table.size() == 0 && withColumnHeader )
		{
			// this's header;
			m_header = row;
			withColumnHeader = false;
		}
		else
		{
			m_table.push_back( row );
		}
	}

	for ( CSV_TABLE_TYPE::const_iterator iter = m_table.begin(); iter != m_table.end(); ++iter )
	{
		m_keyMap.insert( std::make_pair( (*iter)[colAsKey], &(*iter)) );
	}

	// debug

//
//	 for ( CSV_TABLE_TYPE::const_iterator iter = m_table.begin(); iter != m_table.end(); ++iter )
//	 {
//		 for (CSV_ROW_TYPE::const_iterator row = (*iter).begin(); row != (*iter).end(); ++row )
//		 {
//			 printf( "%s\t", (*row).size() == 0 ? "EMPTY" : (*row).c_str() );
//		 }
//		 printf( "\n" );
//	 }


	return m_initialized = true;
}

int CsvReader::getColumnIdxByHeaderId( int id ) const
{
	for ( int i = 0; i < m_header.size(); i++ )
	{
		if ( atoi( m_header[i].c_str() ) == id ) return i;
	}
	return -1;
}

CsvReader::CSV_SIZE_TYPE CsvReader::rowCount() const
{
    if ( !m_initialized ) return 0;
    
    return m_table.size();
}

CsvReader::CSV_SIZE_TYPE CsvReader::colCount() const
{
    if ( !m_initialized ) return 0;
    
    return m_table[0].size();
}

const CsvReader::CSV_ROW_TYPE* CsvReader::getRow( CSV_SIZE_TYPE rowIdx ) const
{
    if ( rowIdx < rowCount() )
    {
        return &m_table[ rowIdx ];
    }
    
    return NULL;
}

const CsvReader::CSV_CELL_TYPE* CsvReader::getCell( CSV_SIZE_TYPE rowIdx, CSV_SIZE_TYPE colIdx ) const
{
    const CSV_ROW_TYPE* pRow = getRow( rowIdx );
    
    if ( !pRow || colIdx >= pRow->size() ) return NULL;
    
    return &(*pRow)[colIdx];
}

const CsvReader::CSV_ROW_TYPE* CsvReader::findByKey( CSV_CELL_TYPE key ) const
{
    std::map< CSV_CELL_TYPE, const CSV_ROW_TYPE* >::const_iterator iter = m_keyMap.find( key );
    
    if ( iter != m_keyMap.end() )
    {
        return iter->second;
    }
    
    return NULL;
}

bool CsvReader::readRow(CSV_ROW_TYPE &row)
{
    while ( true )
    {
        CSV_CELL_TYPE cell;
        char lastChar = readCell( cell );
        
        if (lastChar == '\r') {
            readChar();
        }

        /**
            android ndk r8 gcc 4.4.3 compiler bug: EOF is treated as unsigned char, so the == operator fails
            @yuxiaofei
         */
        if ( (lastChar == '\n' || lastChar == (char)EOF) && row.size() == 0 ) return false;
        
        row.push_back( cell );

        if ( lastChar != ',' ) break;
    }
    
    return true;
}

char CsvReader::readCell(CSV_CELL_TYPE &cell)
{
    char c = readChar();
    
    if ( c == (char)EOF || c == '\r' || c == '\n' ) return c;
    
    bool startWithQuote = ( c == '"' );
    bool preQuote = false;
    
    if ( startWithQuote ) c = readChar();
    
    while ( true )
    {
        if ( c == '"' )
        {
            if ( !startWithQuote || preQuote )
            {
                // xxx"xxx      ( start without quote ) 
                // "xxx""xxx"   ( start with quote but preQuote )
                cell += c;
                preQuote = false;
            }
            else 
            {
                // it's preQuote
                preQuote = true;
            }
        }
        else if ( c == ',' )
        {
            if ( startWithQuote && preQuote )
            {
                // "xxxx",
                break;
            }
            else if ( startWithQuote )
            {
                // "xxxx,xx"
                cell += c;
            }
            else 
            {
                // xxxx,
                break;
            }
            
            preQuote = false;
        }
        else if ( c == '\n' || c == '\r' || c == (char)(EOF) )
        {
            break;
        }
        else 
        {
            cell += c;
            
            preQuote = false;
        }
        
        c = readChar();
    }
    
    return c;
}

char CsvReader::readChar()
{    
    if ( m_pos == m_bufferSize )
    {
        return (char)EOF;
    }
    
    return m_pBuffer[m_pos++];
}

unsigned char* CsvReader::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
    unsigned char * pBuffer = NULL;
    
    *pSize = 0;
    do 
    {
        // read the file from hardware
        FILE *fp = fopen(pszFileName, pszMode);
        
        if ( !fp ) break;
        
        fseek(fp,0,SEEK_END);
        *pSize = ftell(fp);
        fseek(fp,0,SEEK_SET);
        pBuffer = new unsigned char[*pSize];
        *pSize = fread(pBuffer,sizeof(unsigned char), *pSize,fp);
        fclose(fp);
    } while (0);
    
    return pBuffer;
}
