#include "ConfigBase.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "cocos2d.h"
#endif

ConfigBase::ConfigBase()
:m_bInited(false), m_pReader(NULL), m_bUseRawData( false ), m_pRawData( NULL )
{
    
}

ConfigBase::~ConfigBase()
{
    if ( m_pReader )
    {
        delete m_pReader;
    }
}

bool ConfigBase::Load( const char* filePath )
{
    if ( m_bInited ) return true;
    
    if ( !m_bUseRawData )
    {
        m_pFilePath = std::string( filePath );
        m_pReader = new CsvReader( m_pFilePath.c_str() );
        
        if ( m_pReader->load( 0, true ) )
        {
            ClearData();
            return m_bInited = true;
        }
    }
    else
    {
        m_pReader = new CsvReader( "" );
        if ( m_pReader->loadWithData( m_pRawData, 0, true ) )
        {
            ClearData();
            return m_bInited = true;
        }
    }
    return false;
}
#include "cstdio"

bool ConfigBase::LoadRawData( const char* data )
{
    m_bUseRawData 	= true;
    m_pRawData		= data;
    return Load( "" );
}

bool ConfigBase::Reload( const char* filePath )
{
    // unsafe
    if ( m_bUseRawData ) return false;
    
    if ( m_bInited )
    {
        delete m_pReader;
        m_bInited = false;
        
        return Load( filePath );
    }
    
    return false;
}

void ConfigBase::ClearData()
{
    
}
