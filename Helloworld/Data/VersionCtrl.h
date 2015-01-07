//}
//  VersionCtrl.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-25.}
//
//

#ifndef __HelloWorld__VersionCtrl__
#define __HelloWorld__VersionCtrl__

#include <iostream>

class VersionCtrl {
    
public:
    /** 判断是否需要更新}*/
    bool needUpdate(int remote);
    /** 获得版本的值}*/
    const char* versionCode();
    /** 更新完成后的回调}*/
    void updateCallback(int latestVersion);
    
    VersionCtrl();
    virtual ~VersionCtrl();
    
    bool checkUseWhichResource();
private:
    int curVerCode();
};

#endif /* defined(__HelloWorld__VersionCtrl__) */
