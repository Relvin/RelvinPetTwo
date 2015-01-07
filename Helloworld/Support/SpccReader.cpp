#include "SpccReader.h"
#include "cocos2d.h"

USING_NS_CC;

SpccReader* SpccReader::m_instance = NULL;

SpccReader* SpccReader::sharedSpccReader()
{
    if ( m_instance == NULL ) m_instance = new SpccReader();
    return m_instance;
}

bool SpccReader::readConfigFromFile(std::string path, SpccEffectConfig &out)
{
    unsigned long size;
    unsigned char *m_pBuffer = CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &size );
    
    if ( m_pBuffer == NULL ) return false;
    
    ByteBuffer buffer( size );
    buffer.append( m_pBuffer, size );
    CC_SAFE_DELETE_ARRAY(m_pBuffer);
    
    uint16 frameCount;
    
    buffer >> frameCount;
    
    CCLog("frame Count : %d", frameCount);
    
    for ( int i = 0; i < frameCount; i++ )
    {
        out.frames.push_back( readFrame( buffer ) );
    }
    
    if ( buffer.rpos() < buffer.size() )
    {
        //CCLog("new format");
        uint32 t;
        CCLog("t size : %lu", sizeof(t));
        buffer >> t;
        
        
        
        out.lessScale = t * 0.001f;
    }
    else
    {
        out.lessScale = 1.0f;
    }
    
    return true;
}

EffectFrameInfo SpccReader::readFrame( ByteBuffer& buffer )
{
    EffectFrameInfo ret;
    buffer >> ret.byPngIdx;
    if ( ret.byPngIdx != -1 )
    {
        buffer >> ret.dwOffsetX >> ret.dwOffsetY;
    }
    return ret;
}