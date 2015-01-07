#include "CcbItemInfoLayer.h"
#include "CcbManager.h"
#include "EnumDefines.h"
#include "ConfigGet.h"
#include "PacketDataMgr.h"
#include "ResourceDefine.h"
#include "ResourceStringClient.h"
#include "CcbItemIconLayer.h"
#include "MusicCtrl.h"


void CShowItemInfo::Show(uint32 dwItemID)
{
    Create();
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2122))
    {
        pScene->removeChildByTag(2122);
    }
    CcbItemInfoLayer* pLayer = (CcbItemInfoLayer*)CcbManager::sharedManager()->LoadCcbItemInfoLayer(pScene);
    pLayer->retain();
    pScene->addChild(pLayer, 1000, 2122);
    pLayer->setItemID(dwItemID);
    pLayer->autorelease();
}

void CShowItemInfo::Close()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    if (pScene->getChildByTag(2122))
    {
        pScene->removeChildByTag(2122);
    }
    Destory();
}

CcbItemInfoLayer::~CcbItemInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemText);
	CC_SAFE_RELEASE_NULL(m_pControlButtonOk);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPro_2);
//	CC_SAFE_RELEASE_NULL(m_pSpritePro_2);
	CC_SAFE_RELEASE_NULL(m_pLayerPro_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPro_1);
//	CC_SAFE_RELEASE_NULL(m_pSpritePro_1);
	CC_SAFE_RELEASE_NULL(m_pLayerPro_1);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFProText_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFProText_2);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbItemInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbItemInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbItemInfoLayer", CcbItemInfoLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/item_info.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbItemInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbItemInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbItemInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbItemInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbItemInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbItemInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemName", CCLabelTTF*, this->m_pLabelTTFItemName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemText", CCLabelTTF*, this->m_pLabelTTFItemText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonOk", CCControlButton*, this->m_pControlButtonOk);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPro_2", CCLabelTTF*, this->m_pLabelTTFPro_2);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePro_2", CCSprite*, this->m_pSpritePro_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPro_2", CCLayer*, this->m_pLayerPro_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPro_1", CCLabelTTF*, this->m_pLabelTTFPro_1);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePro_1", CCSprite*, this->m_pSpritePro_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPro_1", CCLayer*, this->m_pLayerPro_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProText_1", CCLabelTTF*, this->m_pLabelTTFProText_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFProText_2", CCLabelTTF*, this->m_pLabelTTFProText_2);
	return false;
}

bool CcbItemInfoLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbItemInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbItemInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbItemInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonOk", CcbItemInfoLayer::onPressControlButtonOk);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbItemInfoLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonOk->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority * 2 - 1);
    m_pLabelTTFItemText->noStroke();
}

void CcbItemInfoLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority * 2, true);
}

bool CcbItemInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
    
}

void CcbItemInfoLayer::onPressControlButtonOk(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    CShowItemInfo::Get()->Close();
}

void CcbItemInfoLayer::setItemID(uint32 dwItemID)
{
    if (dwItemID == 0)
    {
        m_pLabelTTFItemName->setString("");
        m_pLabelTTFItemText->setString("");
//        m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(PIC_DEFAULT));
        return;
    }
    
    m_pLayerIcon->loadIndexData(dwItemID);
    m_pLayerIcon->showIconOnly();
    m_pLayerIcon->setBtnEnable(false);
    m_pLabelTTFItemName->setString(g_PacketDataMgr->GetObjectNameByIndex(dwItemID).c_str());
    m_pLabelTTFItemText->setString(g_PacketDataMgr->GetObjectDescByIndex(dwItemID).c_str());
    
    //显示属性}
    uint8 byProType[2];
    byProType[0] = 0;
    byProType[1] = 0;
    uint32 dwProValue[2];
    switch (dwItemID / E_UNITE_BASE_FABIO) {
        case E_UNITE_TYPE_EQUIP:
        {
            EquipNewConfig::STC_EQUIP_CONFIG* pEquipConfig = GET_CONFIG_STC(EquipNewConfig, dwItemID);
            if (pEquipConfig) {
                byProType[0] = pEquipConfig->byEffectType1;
                byProType[1] = pEquipConfig->byEffectType2;
                dwProValue[0] = pEquipConfig->wEffectValue1;
                dwProValue[1] = pEquipConfig->wEffectValue2;
            }
            
        }
            break;
            
        case E_UNITE_TYPE_RUNES:
        {
            RuneConfig::STC_RUNE_CONFIG* pRuneConfig = GET_CONFIG_STC(RuneConfig, dwItemID);
            if (pRuneConfig) {
                byProType[0] = pRuneConfig->byEffectType1;
                dwProValue[0] = pRuneConfig->wEffectValue1;
                byProType[1] = pRuneConfig->byEffectType2;
                dwProValue[1] = pRuneConfig->wEffectValue2;
            }
        }
            break;
            
        default:
            break;
    }
    
    CCLayer* arrProLayer[2];
//    CCSprite* arrProSprite[2];
    CCLabelTTF* arrProLbl[2];
    CCLabelTTF* arrProTextLbl[2];
    arrProLayer[0] = m_pLayerPro_1;
    arrProLayer[1] = m_pLayerPro_2;
    m_pLayerPro_1->setVisible(false);
    m_pLayerPro_2->setVisible(false);
    
//    arrProSprite[0] = m_pSpritePro_1;
//    arrProSprite[1] = m_pSpritePro_2;
    arrProLbl[0] = m_pLabelTTFPro_1;
    arrProLbl[1] = m_pLabelTTFPro_2;
    
    arrProTextLbl[0] = m_pLabelTTFProText_1;
    arrProTextLbl[1] = m_pLabelTTFProText_2;
    
    int cnt = 0;
    for (int i = 0; i < 2; i++) {
        if (byProType[i] == 0) {
            continue;
        }
        arrProLayer[cnt]->setVisible(true);
//        arrProSprite[cnt]->setDisplayFrame(g_PacketDataMgr->getAttrTexture(byProType[i]));
        arrProLbl[cnt]->setString(CCString::createWithFormat("+%d", dwProValue[i])->getCString());
        arrProTextLbl[cnt]->setString(g_PacketDataMgr->getAttrText(byProType[i]).c_str());
        cnt++;
    }
    
}







