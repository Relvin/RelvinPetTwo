//
//  GameStateManager.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-8-2.}
//
//

#ifndef __HelloWorld__GameStateManager__
#define __HelloWorld__GameStateManager__

//#include "Defines.h"

#include <string>

class GameStateManager {
    
public:
    static GameStateManager* sharedManager();
    
    void Initialize();
    void Reload();
private:
    std::string remotePath;
};

#endif /* defined(__HelloWorld__GameStateManager__) */
