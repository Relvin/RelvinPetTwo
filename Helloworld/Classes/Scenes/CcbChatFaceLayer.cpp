#include "CcbChatFaceLayer.h"
//#include "CcbManager.h"
#include "CcbChatLayer.h"
#include "FlyTextLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbChatFaceLayer::~CcbChatFaceLayer()
{
    CC_SAFE_RELEASE_NULL(m_pMenuFace);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbChatFaceLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbChatFaceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbChatFaceLayer", CcbChatFaceLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/chat_face.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbChatFaceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbChatFaceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    setTouchEnabled(true);
}

void CcbChatFaceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbChatFaceLayer::onExit()
{
	CCLayer::onExit();
}

void CcbChatFaceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbChatFaceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pMenuFace", CCMenu*, this->m_pMenuFace);
	return false;
}

bool CcbChatFaceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。}
    bool bRet = false;
    if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }
    
    return bRet;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChatFaceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChatFaceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onPressMenuItemTouch", CcbChatFaceLayer::onPressMenuItemTouch);

	return NULL;
}

SEL_CCControlHandler CcbChatFaceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChatFaceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pMenuFace->setTouchPriority(kCCMenuHandlerPriority-11);
}

void CcbChatFaceLayer::onPressMenuItemTouch(CCObject* pSender)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
	CCMenuItemImage* pMenuItem = (CCMenuItemImage*)pSender;
    if (pMenuItem) {
        
        if (CcbChatLayer::getInstance()->faceNum() > 1) {
            CCString* pStr = CCString::createWithFormat(GET_STR(Str_face_not_too_much), 1 + 1);
            FlyTextLayer::showTips(pStr->getCString());
            removeFromParent();
            return;
        }
        
        CcbChatLayer::getInstance()->addFaceCode(pMenuItem->getTag());
    }
    removeFromParent();
}

bool CcbChatFaceLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCSize faceSize = this->getContentSize();
    CCPoint parentPoint = this->getParent()->getPosition();
    CCSize parentSize = this->getParent()->getContentSize();
    parentPoint = ccpSub(parentPoint, ccp(parentSize.width*0.5, parentSize.height*0.5));
    
//    CCLog("face pos:[%f,%f],\n gl face pos:[%f, %f],\n ui face pos:[%f, %f],\n parent pos:[%f, %f].", facePoint.x, facePoint.y, GlFacePoint.x, GlFacePoint.y, UiFacePoint.x, UiFacePoint.y, parentPoint.x, parentPoint.y);
    
    CCRect faceRect = CCRectMake(parentPoint.x, parentPoint.y, faceSize.width, faceSize.height);
    
//    CCPoint touchPoint = pTouch->getLocationInView(); //OpenGL
    CCPoint touch1Point = pTouch->getLocation();    //Screen

    if (!faceRect.containsPoint(touch1Point)) {
//        FlyTextLayer::showTips(GET_STR(Str_touch_the_face));
        removeFromParent();
    }
    
    return true;
}







