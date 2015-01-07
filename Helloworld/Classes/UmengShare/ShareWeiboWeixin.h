//
//  ShareWeiboWeixin.h
//  HelloWorld
//
//  Created by jun on 14-4-17.
//
//


#include "Singleton.h"
#include <map>
#include "SystemMessageProtocol.h"

class ShareWeiboWeixin
: public Singleton<ShareWeiboWeixin>
, public SystemMessageProtocol
{
public:
    void onShareWeibo(const char *text);
    void onShareWeiXin(const char *text);
    virtual void systemMessageOKTapped(SystemMessage *systemMessage);
    static void shareCallback(int platform, int stCode,
                              const std::string& errorMsg);
    static void authCallback(int platform, int stCode,
                             const std::map<std::string, std::string>& data);
private:
    std::string m_shareText;
};

