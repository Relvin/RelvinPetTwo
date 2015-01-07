//
//  file_cache.h
//  HappyHero
//
//  Created by YUXIAOFEI on 14-8-8.
//
//

#ifndef __HappyHero__file_cache__
#define __HappyHero__file_cache__

#include <iostream>
#include "cocos2d.h"

class FileLoadCache
{
public:
    static FileLoadCache& getInstance();

    // @return  Don't deallocate it
    unsigned char* getFileData(const std::string& filename, unsigned long *size);

    // clear when resources updated
    void clearCache();
protected:
    struct FileData
    {
        FileData() : data(NULL), size(0){};
        
        unsigned char*  data;
        unsigned long  size;
    };
    std::map<std::string, FileData>    cache_;
};

#endif /* defined(__HappyHero__file_cache__) */
