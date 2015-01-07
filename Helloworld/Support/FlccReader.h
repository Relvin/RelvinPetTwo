
#ifndef __FlccReader_h__
#define __FlccReader_h__

#include "FlccData.h"
#include "string.h"
#include "ByteBuffer.h"

class FlccReader
{
    
// static
public:
    
    static FlccReader* sharedFlccReader();
    
public:
    
    bool readConfigFromFile( std::string path, FlccAnimationConfig& out );
    
protected:
    
    ActionInfo readAction( ByteBuffer* buffer );
    PartInfo readPart( ByteBuffer* buffer, uint8 nFrame );
    FrameInfo readFrame( ByteBuffer* buffer );
    SymbolInfo readSymbol( ByteBuffer* buffer );
    
    
private:
    static FlccReader* m_instance;
    
    
    
    
};

#endif
