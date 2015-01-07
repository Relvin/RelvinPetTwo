//}
//  DirOperate.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-28.}
//
//

#ifndef __HelloWorld__DirOperate__
#define __HelloWorld__DirOperate__

#include <iostream>

class DirOperate {
    
public:
    // return 0 indicate exist, otherwise -1.
    static int DirIsExist( const char* path );
    // return 0 indicate success, otherwise -1.
    static int DirCreate( const char* path );
    
    static int DelFile(const char* path, bool delRoot = false);
};

#endif /* defined(__HelloWorld__DirOperate__) */
