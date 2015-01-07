#ifndef __CONFIG_BASE_H__
#define __CONFIG_BASE_H__

#include "CsvReader.h"
#include <string>

#define CONFIG_GET_BY_ID( retType, keyType )										\
protected: std::map<keyType, retType> m_mapConfig;								\
public: retType* GetById( keyType id )											\
{																				\
std::map<keyType, retType>::iterator it = m_mapConfig.find( id );			\
if ( it == m_mapConfig.end() )												\
{																			\
IME_ERROR( "CONFIG ERROR - %s - ID(%d) not found", #retType, id );		\
}																			\
return it == m_mapConfig.end() ? NULL : &(it->second);						\
}                                                                               \
virtual void ClearData()                                                        \
{                                                                               \
m_mapConfig.clear();                                                        \
}

#define CONFIG_GET_MAP( retType, keyType )				\
public: std::map<keyType, retType>& GetMap()		\
{													\
return m_mapConfig;								\
}

class CsvReader;

class ConfigBase
{
public:
    ConfigBase();
    virtual ~ConfigBase();
    
    virtual bool Load( const char* filePath );
    virtual bool LoadRawData( const char* data );
    virtual bool Reload( const char* filePath );
    
    virtual void ClearData();
    
protected:
    bool 		m_bInited;
    std::string m_pFilePath;
    CsvReader* 	m_pReader;
    
    bool 		m_bUseRawData;
    const char* m_pRawData;
};


#endif
