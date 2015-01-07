#include <iostream>
#include <string>
#include "FlccReader.h"
#include "FlccData.h"

FlccReader* FlccReader::m_instance = NULL;

FlccReader* FlccReader::sharedFlccReader()
{
    if ( m_instance == NULL )
    {
        m_instance = new FlccReader();
    }
    
    return m_instance;
}

bool FlccReader::readConfigFromFile( std::string path, FlccAnimationConfig& out )
{    
    unsigned long size;
    unsigned char *m_pBuffer = CCFileUtils::sharedFileUtils()->getFileData( path.c_str(), "rb", &size );
    
    if ( m_pBuffer == NULL ) return false;
    
    ByteBuffer buffer( size );

    buffer.append( m_pBuffer, size );
    CC_SAFE_DELETE_ARRAY( m_pBuffer);
    
    uint16 symbolCount;
    
    //~~~问题点：out.modelId 在新的中是没有的，这里不确定要不要~~~//}
    buffer >> out.modelId >> symbolCount;
    
    for ( int i = 0; i < symbolCount; i++ )
    {
        out.symbols.push_back( readSymbol( &buffer) );
    }
    
    uint8 actionCount;
    buffer >> actionCount;
    
    for ( int i = 0; i < actionCount; i++ )
    {
        out.actions.push_back( readAction(&buffer) );
    }
    
    //~~~问题点：下面这段在新的中是没有的，这里不确定要不要~~~//}
    if ( buffer.rpos() < buffer.size() )
    {
        uint32 t;
        buffer >> t;
        out.lessScale = t * 0.001f;
    }
    else
    {
        out.lessScale = 1.0f;
    }
    
    return true;

}

SymbolInfo FlccReader::readSymbol(ByteBuffer *buffer)
{
    SymbolInfo ret;
    *buffer >> ret.partId >> ret.alterId >> ret.frameId;
    
    //CCLog( "Symbol : %u, %u ", ret.partId, ret.alterId );
    
    int32 x, y;
    *buffer >> x >> y;
    ret.offset = ccp( x, y );
    return ret;
}

ActionInfo FlccReader::readAction(ByteBuffer* buffer)
{
    ActionInfo ret;
    uint8 partCount;
    
    *buffer >> ret.name >> ret.totalFrame >> partCount;
    
    //CCLog( "==== totalFrame ===== %s %d", ret.name.c_str(), ret.totalFrame );
    
    for ( int i = 0; i < partCount; i++ )
    {
        ret.parts.push_back( readPart(buffer, ret.totalFrame) );
    }
    
    return ret;
}

PartInfo FlccReader::readPart(ByteBuffer *buffer, uint8 nFrame )
{
    PartInfo ret;

    *buffer >> ret.partId >> ret.zOrder;
    
    for ( int i = 0; i < nFrame; i++ )
    {
        ret.frames.push_back( readFrame(buffer) );
    }
    
    return ret;
}

FrameInfo FlccReader::readFrame(ByteBuffer *buffer)
{
    FrameInfo ret;
    
    int a, b, c, d, tx, ty, alpha;
    *buffer >> a >> b >> c >> d >> tx >> ty >> alpha;
    ret.a = (float)a / 1000.0f;
    ret.b = (float)b / 1000.0f;
    ret.c = (float)c / 1000.0f;
    ret.d = (float)d / 1000.0f;
    ret.tx = (float)tx / 1000.0f;
    ret.ty = (float)ty / 1000.0f;
    ret.alpha = (float)alpha / 1000.0f;
    *buffer >> ret.alterId >> ret.frameId;
//    int x, y, rotation;
//    *buffer >> x >> y >> rotation;
//    
//    ret.x = (float)x;
//    ret.y = (float)y;
//    ret.rotation = (float)rotation / 100;
    
    return ret;
}