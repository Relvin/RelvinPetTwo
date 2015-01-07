#include "CcbEmblemIcon.h"
//#include "CcbManager.h"

#include "EmblemDataMgr.h"
#include "ConfigGet.h"
#include "Emblem.h"
#include "CcbEmblemInfoLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEmblemIcon::~CcbEmblemIcon()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonShowEmblem);
	CC_SAFE_RELEASE_NULL(m_pSpriteIconFrame);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemIcon( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemIcon( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemIcon", CcbEmblemIconLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/emblem_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemIcon::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEmblemIcon::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEmblemIcon::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEmblemIcon::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemIcon::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemIcon::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonShowEmblem", CCControlButton*, this->m_pControlButtonShowEmblem);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIconFrame", CCSprite*, this->m_pSpriteIconFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);

	return false;
}

bool CcbEmblemIcon::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemIcon::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemIcon::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemIcon::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSkill", CcbEmblemIcon::onPressControlButtonSkill);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemIcon::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}



void CcbEmblemIcon::onPressControlButtonSkill(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CcbEmblemInfoLayer::showEmblemInfo(m_dwEmblemObjId);
}

void CcbEmblemIcon::loadData(uint32 dwEmblemObjId)
{
    if (dwEmblemObjId == 0) {
        setVisible(false);
        return;
    }
    m_dwEmblemObjId = dwEmblemObjId;
    
    CEmblem* emblem = g_EmblemData->getEmblemByObjId(m_dwEmblemObjId);
    if (!emblem) {
        m_dwEmblemObjId = 0;
        return;
    }
    setVisible(true);
    
    EmblemConfig::STC_EMBLEM_CONFIG* emCfg = GET_CONFIG_STC(EmblemConfig, emblem->getdwIndexId());
    
    if (!emCfg) {
        return;
    }
    //icon
    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_EmblemData->getIconPath(emblem->getdwIndexId()).c_str()));
    
    if (emblem->getbyLv() == 0) {
        m_pLabelTTFLv->setString("");
    }
    else
    {
        m_pLabelTTFLv->setString(CCString::createWithFormat("%d", emblem->getbyLv())->getCString());
    }
    
    m_pLabelTTFName->setString(emCfg->strName.c_str());
    
}
void CcbEmblemIcon::setEnable(bool enable)
{
    m_pControlButtonShowEmblem->setVisible(enable);

}

void CcbEmblemIcon::setIndex(uint32 index)
{
    EmblemConfig::STC_EMBLEM_CONFIG* emCfg = GET_CONFIG_STC(EmblemConfig, index);
    
    if (!emCfg) {
        return;
    }
    setVisible(true);
    
    //icon
    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_EmblemData->getIconPath(index).c_str()));
    
    m_pLabelTTFName->setString(emCfg->strName.c_str());
}
void CcbEmblemIcon::setLv(uint8 lv)
{
    if (lv == 0) {
        m_pLabelTTFLv->setVisible(false);
        return;
    }
    m_pLabelTTFLv->setVisible(true);
    m_pLabelTTFLv->setString(CCString::createWithFormat("%d", lv)->getCString());
}



