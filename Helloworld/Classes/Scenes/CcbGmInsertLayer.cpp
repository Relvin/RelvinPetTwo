#include "CcbGmInsertLayer.h"
//#include "CcbManager.h"

#include <stdlib.h>

USING_NS_CC;
USING_NS_CC_EXT;

CcbGmInsertLayer::~CcbGmInsertLayer()
{
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteNum);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGmInsertLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGmInsertLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGmInsertLayer", CcbGmInsertLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm_insert.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGmInsertLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
//    CCTextFieldTTF* pInfo = CCTextFieldTTF::textFieldWithPlaceHolder("1", CCSizeMake(56, 24), kCCTextAlignmentCenter, "", 15);
//    m_pTextFieldAutoInfo =  CCTextFieldAuto::create(pInfo);
//    
//	pInfo->setColor( ccWHITE );
//	pInfo->setPosition(ccp(23, 0));
//    pInfo->setDelegate(m_pTextFieldAutoInfo);
//	//pUserName->setString("MM");
//    pInfo->setKeyboardType(KEY_BOARD_TYPE_NUMBER);
//	addChild(m_pTextFieldAutoInfo,10);
    
	return true;
}

void CcbGmInsertLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbGmInsertLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGmInsertLayer::onExit()
{
	CCLayer::onExit();
}

void CcbGmInsertLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGmInsertLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteNum", CCScale9Sprite*, this->m_pScale9SpriteNum);
	return false;
}

bool CcbGmInsertLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGmInsertLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGmInsertLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGmInsertLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonUp", CcbGmInsertLayer::onPressControlButtonUp);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonDown", CcbGmInsertLayer::onPressControlButtonDown);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGmInsertLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CCSize size = m_pScale9SpriteNum->getContentSize();
    float sX = m_pScale9SpriteNum->getScaleX();
    float sY = m_pScale9SpriteNum->getScaleY();
    size = CCSizeMake(size.width * sX, size.height * sY);
    CCPoint pos = m_pScale9SpriteNum->getPosition();
    CCPoint anp = m_pScale9SpriteNum->getAnchorPoint();
    m_pScale9SpriteNum->removeFromParent();
    m_pEditInfo = CCEditBox::create(size, m_pScale9SpriteNum);
    m_pEditInfo->setAnchorPoint(anp);
    m_pEditInfo->setPosition(pos);
    m_pEditInfo->setDelegate(this);
    m_pEditInfo->setFontColor(ccWHITE);
    m_pEditInfo->setFontName(A_Font);
    m_pEditInfo->setFontSize(12);
    m_pEditInfo->setMaxLength(10);
    //m_pEditInfo->setPlaceholderFontColor(ccWHITE);
    m_pEditInfo->setReturnType(kKeyboardReturnTypeDone);
    m_pEditInfo->setInputMode(kEditBoxInputModeNumeric);
    
    addChild(m_pEditInfo);
}



void CcbGmInsertLayer::onPressControlButtonUp(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if (m_num < UINT32_MAX) {
        m_num++;
    }
    setNum(m_num);
}

void CcbGmInsertLayer::onPressControlButtonDown(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if (m_num > 0) {
        m_num--;
    }
    setNum(m_num);
}

void CcbGmInsertLayer::setNum(uint32 num)
{
    m_num = num;
    CCString *str = CCString::createWithFormat("%u", m_num);
    m_pEditInfo->setText(str->getCString());
}


void CcbGmInsertLayer::editBoxReturn(CCEditBox* editBox)
{
//    CCPoint pos = this->getParent()->getParent()->getPosition();
//    pos.y -= 100;
//    this->getParent()->getParent()->setPosition(pos);
//    CCEditBox::keyboardWillHide(info);
    long int num = atoll(m_pEditInfo->getText());
    if (num < 0) {
        num = 0;
    }
    else if (num > UINT32_MAX)
    {
        num = UINT32_MAX;
    }
    m_num = num;
    CCString *str = CCString::createWithFormat("%u", m_num);
    m_pEditInfo->setText(str->getCString());
}



