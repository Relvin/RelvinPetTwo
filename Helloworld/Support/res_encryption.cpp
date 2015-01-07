//
//  res_encryption.cpp
//  cocos2d_libs
//
//  Created by YUXIAOFEI on 14-4-9.
//
//

#include "res_encryption.h"
#include <stdint.h>

/*
 * Decrypt block by XXTEA.
 * Params:
 *   block - block of encrypted data
 *   len   - length of block
 *   key   - 128b key
 */

#define DELTA 0x9e3779b9
#define MX (z>>5^y<<2) + (y>>3^z<<4)^(sum^y) + (key[p&3^e]^z)

void xxteadecrypt(uint32_t *block, uint32_t len, uint32_t *key)
{
    uint32_t z=block[len-1], y=block[0], sum=0, e;
    int32_t p, q;
    
    q = 6 + 52/len;
    sum = q*DELTA ;
    while (sum != 0) {
        e = (sum >> 2) & 3;
        for (p=len-1; p>0; p--)
        {
            z = block[p-1];
            block[p] -= MX;
            y = block[p];
        }
        z = block[len-1];
        block[0] -= MX;
        y =  block[0];
        sum -= DELTA;
    }
}

/*
 * Crypt block by XXTEA.
 * Params:
 *   block - block of input data
 *   len   - length of block
 *   key   - 128b key
 */
void xxteacrypt(uint32_t *block, uint32_t len, uint32_t *key)
{
    uint32_t z=block[len-1], y=block[0], sum=0, e;
    int32_t p, q;
    
    q = 6 + 52/len;
    while (q-- > 0) {
        sum += DELTA;
        e = (sum >> 2) & 3;
        for (p=0; p<len-1; p++)
        {
            y = block[p+1];
            block[p] += MX;
            z = block[p];
        }
        y = block[0];
        block[len-1] += MX;
        z = block[len-1];
    }
}

ResEncryption& ResEncryption::GetInstance()
{
    static ResEncryption ins;
    return ins;
}

ResEncryption::ResEncryption()
{
    // key
    const char* key = "128b72ec55cd18355758c471ba1e6e75";
    memset(_key, 0, sizeof(_key));
    memcpy(_key, key, strlen(key) <= sizeof(_key) ? strlen(key) : sizeof(_key));
    
    // suffix to encrytp
//    _suffix.push_back(".png");
//    _suffix.push_back(".jpg");
    _suffix.push_back(".plist");
    _suffix.push_back(".csv");
}

// max encrypt 4k
const int max_encrypt_size_in_byte = 1024 * 4;

void ResEncryption::Encrypt(void *data_, int size_, const char* file_name_)
{
    if (data_ && size_ >= 8 && NeedsEncryption(file_name_)) {
        if(size_ > max_encrypt_size_in_byte) size_ = max_encrypt_size_in_byte;
        xxteacrypt((uint32_t *)data_, size_ / 4, (uint32_t *)_key);
    }
}

void ResEncryption::Decrypt(void *data_, int size_, const char *file_name_)
{
    if (data_ && size_ >= 8 && NeedsEncryption(file_name_)) {
        if(size_ > max_encrypt_size_in_byte) size_ = max_encrypt_size_in_byte;
        xxteadecrypt((uint32_t *)data_, size_ / 4, (uint32_t *)_key);
    }
}

int StringUtilEndsWith(const char *str, const char *suffix)
{
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

bool ResEncryption::NeedsEncryption(const char *file_name_)
{
    for (SuffixContainer::iterator itor = _suffix.begin(); itor != _suffix.end(); ++itor) {
        if (StringUtilEndsWith(file_name_, (*itor).c_str())) {
            return true;
        }
    }
    return false;
}
