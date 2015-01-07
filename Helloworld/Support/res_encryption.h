//
//  res_encryption.h
//  cocos2d_libs
//
//  Created by YUXIAOFEI on 14-4-9.
//
//

#ifndef __cocos2d_libs__res_encryption__
#define __cocos2d_libs__res_encryption__

#include <iostream>
#include <string>
#include <vector>

class ResEncryption
{
public:
    static ResEncryption& GetInstance();
    
    void Encrypt(void* data_, int size_, const char* file_name_);
    void Decrypt(void* data_, int size_, const char* file_name_);
    
    bool NeedsEncryption(const char* file_name_);

protected:
    ResEncryption();    
    
protected:
    typedef std::vector<std::string> SuffixContainer;
    SuffixContainer     _suffix;
    unsigned char       _key[16];
};

#endif /* defined(__cocos2d_libs__res_encryption__) */
