#include "CcbEmblemIconLayer.h"
#include "CcbEmblemChooseListLayer.h"
#include "EmblemDataMgr.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "FlyTextLayer.h"
#include "CcbEmblemEnhanceLayer.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEmblemIconLayer::~CcbEmblemIconLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteTick);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLayerClip);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemIconLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemIconLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemIconLayer", CcbEmblemIconLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_choose_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemIconLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEmblemIconLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEmblemIconLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEmblemIconLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemIconLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemIconLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteTick", CCSprite*, this->m_pSpriteTick);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerClip", CCLayer*, this->m_pLayerClip);

	return false;
}

bool CcbEmblemIconLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemIconLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemIconLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemIconLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemIconLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_isSelected= false;
    
    m_btnChoose = CCScrollButton::createTransWithHightLight();
    m_btnChoose->setPreferredSize(m_pLayerIcon->getContentSize() - CCSizeMake(4, 4));
    m_btnChoose->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbEmblemIconLayer::onPressControlButtonChoose), CCControlEventTouchUpInside);
    
    m_btnChoose->setPosition(ccp(getWidth(m_pLayerIcon) * 0.5 - 1, getHeight(m_pLayerIcon)*0.5 - 1));
    m_btnChoose->setAnchorPoint(ccp(0.5, 0.5));
//    m_btnChoose->setClipRect(CCRectMake(0, 0, getWidth(m_pSpriteIcon), getHeight(m_pSpriteIcon)));
    
    m_pLayerIcon->addChild(m_btnChoose, 1);
    m_pLayerIcon->setBtnEnable(false);
}

void CcbEmblemIconLayer::onPressControlButtonChoose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    m_isSelected = !m_isSelected;
    if (m_isSelected) {
        bool flag = g_EmblemData->addSelected(m_dwEmbObjId);
        if (!flag) {
//            FlyTextLayer::showTips(CCString::createWithFormat(GET_STR(Str_most_choose), g_EmblemData->getSelected().size())->getCString());
            m_isSelected = false;
        }
    }
    else
    {
        g_EmblemData->delSelected(m_dwEmbObjId);
    }
    m_pSpriteTick->setVisible(m_isSelected);
    if (m_delegate) {
        m_delegate->reflashSelected();
    }
}

void CcbEmblemIconLayer::setEmbObjId(uint32 dwObjId)
{
    m_dwEmbObjId = dwObjId;
    loadData();
}

void CcbEmblemIconLayer::loadData()
{
    CEmblem* emb = g_EmblemData->getEmblemByObjId(m_dwEmbObjId);
    if (!emb) {
        return;
    }
    
    EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
    if (!embCfg) {
        return;
    }
    
    //徽章Icon}
    m_pLayerIcon->loadIndexData(emb->getdwIndexId());
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->showName();
    m_pLayerIcon->showLv(emb->getbyLv());
//    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_EmblemData->getIconPath(emb->getdwIndexId()).c_str()));
    //徽章名}
//    m_pLabelTTFName->setString(embCfg->strName.c_str());
    //选中}
    m_isSelected = g_EmblemData->isSelected(m_dwEmbObjId);
    m_pSpriteTick->setVisible(m_isSelected);
    
    if (!m_isSelected && g_EmblemData->getSelected().size() >= embSelMax) {
        isCanSelect(false);
    }
    else{
        isCanSelect(true);
    }
}

void CcbEmblemIconLayer::setRect(CCRect rect)
{
    m_btnChoose->setClipRect(rect);
}

void CcbEmblemIconLayer::isCanSelect(bool isCan)
{
    m_pLayerClip->setVisible(!isCan);
}


