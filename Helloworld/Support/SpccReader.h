#ifndef __SPCC_READER_H__
#define __SPCC_READER_H__

#include "string.h"
#include "SpccData.h"
#include "ByteBuffer.h"

class SpccReader
{
public:
    static SpccReader* sharedSpccReader();
    
public:
    bool readConfigFromFile( std::string path, SpccEffectConfig& out );
    
protected:
    
    EffectFrameInfo readFrame( ByteBuffer& buffer );
    
private:
    static SpccReader* m_instance;
};


#endif
