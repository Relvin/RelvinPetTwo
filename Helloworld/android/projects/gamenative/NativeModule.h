//
#ifndef NativeHandler_H
#define NativeHandler_H


#include <iostream>
#include "Defines.h"
#include "PlatformMgr.h"

#include "cocos2d.h"
USING_NS_CC;

using namespace platform;

#define ACT_NATIVE_SHARE_SUCCESS	"ShareSuccess"

class NativeModule : public Module, public CCObject
{
public:
	NativeModule();
	void processCalls(float dt);
	virtual std::string onCall(std::string action, std::string params);

private:
	void pushResult(Request request);
	bool popResult(Request &request);
	vector<Request> mResults;
	pthread_mutex_t mutex;
};




#endif
