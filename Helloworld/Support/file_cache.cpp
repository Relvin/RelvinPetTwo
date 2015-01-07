//
//  file_cache.cpp
//  HappyHero
//
//  Created by YUXIAOFEI on 14-8-8.
//
//

#include "file_cache.h"

FileLoadCache& FileLoadCache::getInstance(){
    static FileLoadCache inst;
    return inst;
}

unsigned char* FileLoadCache::getFileData(const std::string &filename, unsigned long *size)
{
    auto itor = cache_.find(filename);
    if(itor != cache_.end())
    {
        *size = itor->second.size;
        return itor->second.data;
    }
    else
    {
        std::string path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename( filename.c_str() );
        FileData data;
        data.data = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(path.c_str(), "rb", &data.size);
        cache_[filename] = data;
        
        *size = data.size;
        
        return data.data;
    }
}

void FileLoadCache::clearCache()
{
    for (auto itor = cache_.begin(); itor != cache_.end(); ++itor) {
        delete itor->second.data;
    }
    cache_.clear();
}

