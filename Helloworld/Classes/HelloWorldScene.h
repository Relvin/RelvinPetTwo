#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Defines.h"
#include "WorldPacket.h"

class TextSparkLayer;
class TextCriticalLayer;

USING_NS_CC;
USING_NS_CC_EXT;
class HelloWorld : public cocos2d::CCLayer
{
public:
    enum
	{
		E_UNCONNECTED,
		E_LOGIN_CONNECTED,
		E_GAME_CONNECTED,
	};
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    static HelloWorld * GetCurrScene() { return m_currentScene;};
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    void SetConnectionStatus(uint8 byStatus) {m_byConnectStatus = byStatus;};
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    void onConnect();
    void onSend();
    bool ConnectToServer(std::string strIp, int nPort);
    void handlerTest(WorldPacket &packet);
    void onParticle(CCObject *sender);
    void onScroll();
    void onArena();
    void onCcbTest();
	void onCritical(CCObject *pObject);
	void onSpark(CCObject *pObject);
    
	void onStartGame(CCObject *pObject);
    
    void onOver(CCHttpClient* client, CCHttpResponse* response);
	void onMap(CCObject *pObject);
    
    virtual void onEnter();
    virtual void onExit();
    
    void onClickCcb(CCObject *pObject);
	void onClickSprite(CCObject *pObject);
	void onClickMemory(CCObject *pObject);
    
    void dataLoaded(float percent);
private:
    static HelloWorld *m_currentScene;
    CCLabelTTF *lblConn;
    //CCLabelTTF *lblSend;
    CCLabelTTF *lblConnResult;
    CCMenuItemLabel *btnConnect;
    TextCriticalLayer *pCritical;
    TextSparkLayer *pSpark;
    
    CCLabelTTF* ccbTime;
    CCLabelTTF* spriteTime;
    CCLabelTTF* memoryTime;
    
    void testFlcc();
    void update(float time);
    void update2(float time);

    std::vector<CCSprite*> arrPet;
    int cnt;
    int max;
    int Port;
    
    CCSprite *img1;
public:
    uint8 m_byConnectStatus;
};


#endif // __HELLOWORLD_SCENE_H__
