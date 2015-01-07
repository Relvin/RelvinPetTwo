//
//  SystemMessageProtocol.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-11-26.}
//
//

#ifndef __HelloWorld__SystemMessageProtocol__
#define __HelloWorld__SystemMessageProtocol__

#include "cocos2d.h"
class SystemMessage;
//USING_NS_CC;
class SystemMessageProtocol {
public:
	virtual void systemMessageOKTapped(SystemMessage *systemMessage);
	virtual void systemMessageCancelTapped(SystemMessage *systemMessage);
};

#endif /* defined(__HelloWorld__SystemMessageProtocol__) */
