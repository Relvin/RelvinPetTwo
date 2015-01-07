#include "CcbCreateNameLayer.h"
#include "CcbManager.h"
#include "Defines.h"
#include "ConfigGet.h"
#include "GuideData.h"
#include "PetLoadingLayer.h"
#include "MusicCtrl.h"
#include "GameSession.h"
#include "ConfigGet.h"
#include "SystemMessage.h"
#include "ResourceStringClient.h"


USING_NS_CC;
USING_NS_CC_EXT;

#define MAX_LENGTH 10

static int _calcCharCountUTF(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

CCScene* CreateNameScene::scene()
{
    CCScene* pScene = CCScene::create();
    CreateNameScene* pLayer = CreateNameScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool CreateNameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    addChild(CcbManager::sharedManager()->LoadCcbCreateNameLayer(this));
    return true;
}

void CreateNameScene::onEnter()
{
    CCLayer::onEnter();
}

void CreateNameScene::onExit()
{
    CCLayer::onExit();
}

#pragma mark CcbCreateNameLayer

CcbCreateNameLayer::~CcbCreateNameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteName);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRandom);
	CC_SAFE_RELEASE_NULL(m_pControlButtonConfirm);
    CC_SAFE_RELEASE_NULL(m_pLayerCenter);
}

//-- copy this to CcbManager
/*
 //CcbManager.h
 CCNode* LoadCcbCreateNameLayer( CCObject* owner );
 
 //CcbManager.cpp
 CCNode* CcbManager::LoadCcbCreateNameLayer( CCObject* owner ) {
 CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
 pLoaderLib->registerCCNodeLoader( "CcbCreateNameLayer", CcbCreateNameLayerLoader::loader() );
 
 
 CCBReader* pCCBReader = new CCBReader(pLoaderLib);
 CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/createname.ccbi", owner);
 pCCBReader->release();
 
 return pNode;
 }
 */


bool CcbCreateNameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbCreateNameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbCreateNameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    GuideData* pDate = GuideData::GetInstance();
    pDate->setStepId(GuideData::E_GUIDE_TRIGGER_NAME);
    pDate->connectToServer();     // Send 300 to server
    
    CCSize inputSize;
    CCPoint inputPos;
    
    inputSize = m_pScale9SpriteName->getContentSize();
    inputPos = m_pScale9SpriteName->getPosition();
    m_pScale9SpriteName->removeFromParent();
    
    m_pInputBox = CCEditBox::create(inputSize, m_pScale9SpriteName);
    m_pInputBox->setAnchorPoint(ccp(0.5, 0.5));
    m_pInputBox->setPosition(inputPos);
    
    m_pInputBox->setFontName(T_Font);
    m_pInputBox->setFontSize(16);
    m_pInputBox->setPlaceHolder(GET_STR(Str_input_name));
    m_pInputBox->setMaxLength(MAX_LENGTH + 6);
    m_pInputBox->setInputMode(kEditBoxInputModeAny);
    m_pInputBox->setReturnType(kKeyboardReturnTypeDone);
    m_pInputBox->setDelegate(this);
    
    m_pLayerCenter->addChild(m_pInputBox);
    
    m_vecFirstName.clear();
    m_vecSecondName.clear();
    std::map<uint32, RandomNameConfig::STC_RANDOM_NAME> ranNameMap = GET_CONFIG_MAP(RandomNameConfig);
    std::map<uint32, RandomNameConfig::STC_RANDOM_NAME>::iterator pIter;
    for (pIter = ranNameMap.begin(); pIter != ranNameMap.end(); pIter++) {
        RandomNameConfig::STC_RANDOM_NAME cfg;
        cfg = pIter->second;
        m_vecFirstName.push_back(cfg.strFistName);
        m_vecSecondName.push_back(cfg.strSecondName);
        m_vecThirdName.push_back(cfg.strThirdName);
    }
    
    onPressControlButtonRandom(NULL, CCControlStateSelected);
}

void CcbCreateNameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbCreateNameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCreateNameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteName", CCScale9Sprite*, this->m_pScale9SpriteName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRandom", CCControlButton*, this->m_pControlButtonRandom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonConfirm", CCControlButton*, this->m_pControlButtonConfirm);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerCenter", CCLayer*, this->m_pLayerCenter);
	return false;
}

bool CcbCreateNameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCreateNameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_MenuHandler CcbCreateNameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{
    
	return NULL;
}

SEL_CCControlHandler CcbCreateNameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRandom", CcbCreateNameLayer::onPressControlButtonRandom);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonConfirm", CcbCreateNameLayer::onPressControlButtonConfirm);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCreateNameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbCreateNameLayer::onPressControlButtonRandom(CCObject* pSender, CCControlEvent event)
{
    std::string strName;
    int nFirst = rand() % m_vecFirstName.size();
    int nSecond = rand() % m_vecSecondName.size();
    int nThird = rand() % m_vecThirdName.size();
    
    strName = m_vecFirstName[nFirst] + m_vecSecondName[nSecond] + m_vecThirdName[nThird];
    m_pInputBox->setText(strName.c_str());
}

void CcbCreateNameLayer::onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event)
{
    onConfirm();
}

void CcbCreateNameLayer::onConfirm()
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if (m_pInputBox->getText() == NULL) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_not_null));
        return;
    } else if (strlen(m_pInputBox->getText()) < 4) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_min_len));
        return;
    } else if ( _calcCharCountUTF(m_pInputBox->getText()) > MAX_LENGTH ) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_too_long));
        return;
    }
    PetLoadingLayer::sharedLayer()->WaitForPacket(true);
    CGameSession::SendChooseName(m_pInputBox->getText());
}

#pragma mark EditBox Delegate
void CcbCreateNameLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox)
{
    
}

void CcbCreateNameLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox)
{
    
}

void CcbCreateNameLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text)
{
    
}

void CcbCreateNameLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox)
{
    onConfirm();
}




