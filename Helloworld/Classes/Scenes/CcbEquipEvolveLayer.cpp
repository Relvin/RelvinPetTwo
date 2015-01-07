#include "CcbEquipEvolveLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "EquipDataMgr.h"
#include "ItemDataMgr.h"
#include "CcbItemInfoButtonLayer.h"
#include "PacketDataMgr.h"
#include "EmblemDataMgr.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "UISupport.h"
#include "MusicCtrl.h"

CcbEquipEvolveLayer::~CcbEquipEvolveLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLevel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttriType1);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttr1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttriType2);
	CC_SAFE_RELEASE_NULL(m_pSpriteAttr2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoLv);
	CC_SAFE_RELEASE_NULL(m_pLayerParent2);
	CC_SAFE_RELEASE_NULL(m_pLayerNextIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteNextStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextEvoLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedLevelText);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedLevel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttriType1);
	CC_SAFE_RELEASE_NULL(m_pSpriteNextAttr1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttriType2);
	CC_SAFE_RELEASE_NULL(m_pSpriteNextAttr2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri2);
	CC_SAFE_RELEASE_NULL(m_pSpriteCurStar);
	CC_SAFE_RELEASE_NULL(m_pLayerCurIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurEvoLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurLevel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType1);
	CC_SAFE_RELEASE_NULL(m_pSpriteCurAttr1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType2);
	CC_SAFE_RELEASE_NULL(m_pSpriteCurAttr2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri2);
	CC_SAFE_RELEASE_NULL(m_pLayerElem_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemHaveNum1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNeedNum1);
	CC_SAFE_RELEASE_NULL(m_pNodeParent1);
	CC_SAFE_RELEASE_NULL(m_pLayerElem_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemHaveNum2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNeedNum2);
	CC_SAFE_RELEASE_NULL(m_pNodeParent2);
	CC_SAFE_RELEASE_NULL(m_pControlButtonEvolve);
	CC_SAFE_RELEASE_NULL(m_pLayerParent1);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEquipEvolveLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipEvolveLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipEvolveLayer", CcbEquipEvolveLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/iteminfo_button.ccb]", [ccb/iteminfo_button.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/arrowright.ccb]", [ccb/arrowright.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_evo.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/
CcbEquipEvolveLayer* CcbEquipEvolveLayer::m_curScene = NULL;

bool CcbEquipEvolveLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_isConditionsEnough = false;
	return true;
}

void CcbEquipEvolveLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    m_curScene = this;
}

void CcbEquipEvolveLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEquipEvolveLayer::onExit()
{
    m_curScene = NULL;
	CCLayer::onExit();
}

void CcbEquipEvolveLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipEvolveLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLevel", CCLabelTTF*, this->m_pLabelTTFLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttriType1", CCLabelTTF*, this->m_pLabelTTFAttriType1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttr1", CCSprite*, this->m_pSpriteAttr1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri1", CCLabelTTF*, this->m_pLabelTTFAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttriType2", CCLabelTTF*, this->m_pLabelTTFAttriType2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteAttr2", CCSprite*, this->m_pSpriteAttr2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri2", CCLabelTTF*, this->m_pLabelTTFAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoLv", CCLabelTTF*, this->m_pLabelTTFEvoLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent2", CCLayer*, this->m_pLayerParent2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerNextIcon", CcbItemIconLayer*, this->m_pLayerNextIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNextStar", CCSprite*, this->m_pSpriteNextStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextName", CCLabelTTF*, this->m_pLabelTTFNextName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextEvoLv", CCLabelTTF*, this->m_pLabelTTFNextEvoLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedLevelText", CCLabelTTF*, this->m_pLabelTTFNeedLevelText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedLevel", CCLabelTTF*, this->m_pLabelTTFNeedLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttriType1", CCLabelTTF*, this->m_pLabelTTFNextAttriType1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNextAttr1", CCSprite*, this->m_pSpriteNextAttr1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri1", CCLabelTTF*, this->m_pLabelTTFNextAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttriType2", CCLabelTTF*, this->m_pLabelTTFNextAttriType2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNextAttr2", CCSprite*, this->m_pSpriteNextAttr2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri2", CCLabelTTF*, this->m_pLabelTTFNextAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCurStar", CCSprite*, this->m_pSpriteCurStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerCurIcon", CcbItemIconLayer*, this->m_pLayerCurIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurName", CCLabelTTF*, this->m_pLabelTTFCurName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurEvoLv", CCLabelTTF*, this->m_pLabelTTFCurEvoLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurLevel", CCLabelTTF*, this->m_pLabelTTFCurLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType1", CCLabelTTF*, this->m_pLabelTTFCurAttriType1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCurAttr1", CCSprite*, this->m_pSpriteCurAttr1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri1", CCLabelTTF*, this->m_pLabelTTFCurAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType2", CCLabelTTF*, this->m_pLabelTTFCurAttriType2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteCurAttr2", CCSprite*, this->m_pSpriteCurAttr2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri2", CCLabelTTF*, this->m_pLabelTTFCurAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem_1", CcbItemIconLayer*, this->m_pLayerElem_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemHaveNum1", CCLabelTTF*, this->m_pLabelTTFItemHaveNum1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNeedNum1", CCLabelTTF*, this->m_pLabelTTFItemNeedNum1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeParent1", CCNode*, this->m_pNodeParent1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem_2", CcbItemIconLayer*, this->m_pLayerElem_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemHaveNum2", CCLabelTTF*, this->m_pLabelTTFItemHaveNum2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNeedNum2", CCLabelTTF*, this->m_pLabelTTFItemNeedNum2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeParent2", CCNode*, this->m_pNodeParent2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvolve", CCControlButton*, this->m_pControlButtonEvolve);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerParent1", CCLayer*, this->m_pLayerParent1);

	return false;
}

bool CcbEquipEvolveLayer::onAssignCCBCustomProperty(CCObject *pTarget, const char *pMemberVariableName, CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipEvolveLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipEvolveLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipEvolveLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvolve", CcbEquipEvolveLayer::onPressControlButtonEvolve);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipEvolveLayer::onNodeLoaded(CCNode *pNode, CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CreateEquipData();
}



void CcbEquipEvolveLayer::onPressControlButtonEvolve(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    CGameSession::SendReqEquipEvolve(g_EquipData->GetChosenEquipKeyID());
}


void CcbEquipEvolveLayer::CreateEquipData()
{
    m_isConditionsEnough = true;
    m_pControlButtonEvolve->setEnabled(true);
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    if (!pEquip)
    {
        m_pLayerParent1->setVisible(false);
        m_pLayerParent2->setVisible(false);
        return;
    }
    
    //add by Relvin need modify
//    if (pEquip->GetLevel() < pEquip->GetConfigData().wEvoLV)
//    {
//        m_pControlButtonEvolve->setEnabled(false);
//        m_pLabelTTFNeedLevel->setColor(ccRED);
//    }
//    else{
//        m_pLabelTTFNeedLevel->setColor(ccWHITE);
//    }
    
    CCString* str = CCString::create("");
    
    STC_EQUIP_EVO_SHOW_INFO arrStc[2];
    std::vector<CCNode*> curNodes;
    curNodes.clear();
    
    //进阶前}
    STC_EQUIP_EVO_SHOW_INFO curInfo;
    curInfo.wIndex = pEquip->GetIndex();
    curInfo.strName = pEquip->GetConfigData().strName;
    curInfo.byEvoLv = pEquip->getEvoLv();
    curInfo.byLv = pEquip->GetLevel();
    curInfo.byStar = pEquip->GetConfigData().byStar;
    curInfo.byType1 = pEquip->GetConfigData().byEffectType1;
    curInfo.byType2 = pEquip->GetConfigData().byEffectType2;
    
    //add by Relvin need modify
    float evoAdd = 1 ;//+ (float)pEquip->GetConfigData().wEvoCoef / 10000;
    curInfo.dwValue1 = pEquip->GetConfigData().wEffectValue1 + (pEquip->GetLevel() - 1) * pEquip->GetConfigData().wGrowthRate1 * evoAdd;
    curInfo.dwValue2 = pEquip->GetConfigData().wEffectValue2 + (pEquip->GetLevel() - 1) * pEquip->GetConfigData().wGrowthRate2 * evoAdd;
    arrStc[0] = curInfo;
    
    //材料}
    //add by Relvin need modify
#if 0
    if (pEquip->GetConfigData().dwEvoMaterial1) {
        m_pLayerElem_1->getParent()->setVisible(true);
        m_pLayerElem_1->loadIndexData(pEquip->GetConfigData().dwEvoMaterial1);
        m_pLayerElem_1->showIconOnly();
        
        uint32 dwItemHave = g_PacketDataMgr->GetItemCountByIndex(pEquip->GetConfigData().dwEvoMaterial1);
        str->initWithFormat("%d", dwItemHave);
        m_pLabelTTFItemHaveNum1->setString(str->getCString());
        str->initWithFormat("%d", pEquip->GetConfigData().dwEvoMaterialAttri1);
        m_pLabelTTFItemNeedNum1->setString(str->getCString());
        if (dwItemHave < pEquip->GetConfigData().dwEvoMaterialAttri1)
        {
            m_pLabelTTFItemHaveNum1->setColor(ccRED);
            m_isConditionsEnough = false;
        }
        else
        {
            m_pLabelTTFItemHaveNum1->setColor(ccWHITE);
            
        }
        
    }
    else{
        m_pLayerElem_1->getParent()->setVisible(false);
    }
    
    
    if (pEquip->GetConfigData().dwEvoMaterial2) {
        m_pLayerElem_1->getParent()->setVisible(true);
        
        m_pLayerElem_2->loadIndexData(pEquip->GetConfigData().dwEvoMaterial2);
        m_pLayerElem_2->showIconOnly();
        
        uint32 dwItemHave = g_PacketDataMgr->GetItemCountByIndex(pEquip->GetConfigData().dwEvoMaterial2);
        str->initWithFormat("%d", dwItemHave);
        m_pLabelTTFItemHaveNum2->setString(str->getCString());
        str->initWithFormat("%d", pEquip->GetConfigData().dwEvoMaterialAttri2);
        m_pLabelTTFItemNeedNum2->setString(str->getCString());
        if (dwItemHave < pEquip->GetConfigData().dwEvoMaterialAttri2)
        {
            m_pLabelTTFItemHaveNum2->setColor(ccRED);
            m_isConditionsEnough = false;
        }
        else
        {
            m_pLabelTTFItemHaveNum2->setColor(ccWHITE);
            //                m_isConditionsEnough = true;
        }
    }
    else{
        m_pLayerElem_1->getParent()->setVisible(false);
    }
    
    
    if (pEquip->GetConfigData().dwEvoID != 0)
    {
        //未进阶到最高}
        m_pLayerParent1->setVisible(true);
        m_pLayerParent2->setVisible(false);
        EquipConfig::STC_EQUIP_CONFIG* pConfig = GET_CONFIG_STC(EquipConfig, pEquip->GetConfigData().dwEvoID);
        if (!pConfig)
        {
            CCLog("Equip.csv read error, can not find ID, %ud", pEquip->GetConfigData().dwEvoID);
            return;
        }
        curNodes.push_back(m_pLayerCurIcon);
        curNodes.push_back(m_pSpriteCurStar);
        curNodes.push_back(m_pLabelTTFCurName);
        curNodes.push_back(m_pLabelTTFCurEvoLv);
        curNodes.push_back(m_pLabelTTFCurLevel);
        curNodes.push_back(m_pLabelTTFCurAttriType1);
        curNodes.push_back(m_pLabelTTFCurAttri1);
        curNodes.push_back(m_pSpriteCurAttr1);
        curNodes.push_back(m_pLabelTTFCurAttriType2);
        curNodes.push_back(m_pLabelTTFCurAttri2);
        curNodes.push_back(m_pSpriteCurAttr2);
        
        
        //进阶后}
        STC_EQUIP_EVO_SHOW_INFO nextInfo;
        nextInfo.wIndex = pConfig->dwIndex;
        nextInfo.strName = pConfig->strName;
        nextInfo.byEvoLv = pEquip->getEvoLv() + 1;
        nextInfo.byLv = pEquip->GetConfigData().wEvoLV;
        nextInfo.byStar = pConfig->byStar;
        nextInfo.byType1 = pConfig->byEffectType1;
        nextInfo.byType2 = pConfig->byEffectType2;
        evoAdd = 1 + (float)pConfig->wEvoCoef / 10000;
        nextInfo.dwValue1 = pConfig->wEffectValue1 + (pEquip->GetLevel() - 1) * pConfig->wGrowthRate1 * evoAdd;
        nextInfo.dwValue2 = pConfig->wEffectValue2 + (pEquip->GetLevel() - 1) * pConfig->wGrowthRate2 * evoAdd;
        arrStc[1] = nextInfo;
        
        std::vector<CCNode* >nextNodes;
        nextNodes.clear();
        nextNodes.push_back(m_pLayerNextIcon);
        nextNodes.push_back(m_pSpriteNextStar);
        nextNodes.push_back(m_pLabelTTFNextName);
        nextNodes.push_back(m_pLabelTTFNextEvoLv);
        nextNodes.push_back(m_pLabelTTFNeedLevel);
        nextNodes.push_back(m_pLabelTTFNextAttriType1);
        nextNodes.push_back(m_pLabelTTFNextAttri1);
        nextNodes.push_back(m_pSpriteNextAttr1);
        nextNodes.push_back(m_pLabelTTFNextAttriType2);
        nextNodes.push_back(m_pLabelTTFNextAttri2);
        nextNodes.push_back(m_pSpriteNextAttr2);
        mapAllNode[1] = nextNodes;
        
    }
    else{
        //进阶到最高}
        m_pLayerParent1->setVisible(false);
        m_pLayerParent2->setVisible(true);
        
        curNodes.push_back(m_pLayerIcon);
        curNodes.push_back(m_pSpriteStar);
        curNodes.push_back(m_pLabelTTFName);
        curNodes.push_back(m_pLabelTTFEvoLv);
        curNodes.push_back(m_pLabelTTFLevel);
        curNodes.push_back(m_pLabelTTFAttriType1);
        curNodes.push_back(m_pLabelTTFAttri1);
        curNodes.push_back(m_pSpriteAttr1);
        curNodes.push_back(m_pLabelTTFAttriType2);
        curNodes.push_back(m_pLabelTTFAttri2);
        curNodes.push_back(m_pSpriteAttr2);
    }
#endif
    
    mapAllNode[0] = curNodes;
    for (int i = 0; i < 2; i++) {
        STC_EQUIP_EVO_SHOW_INFO info = arrStc[i];
        std::vector<CCNode* > nodes = mapAllNode[i];
        if (nodes.size() == 0) {
            continue;
        }
        for (int k = 0; k < nodes.size(); k++) {
            CCNode* node = nodes[k];
            if (!node) {
                continue;
            }
            switch (k) {
                case 0:
                {   //icon
                    CcbItemIconLayer* icon = (CcbItemIconLayer*)node;
                    icon->loadIndexData(info.wIndex);
                    icon->showIconOnly();
                    icon->setBtnEnable(false);
                }
                    break;
                case 1:
                {   //星级}
                    CCSprite* star = (CCSprite*)node;
                    star->removeAllChildren();
                    CCTexture2D *td = star->getTexture();
//                    uint8 starLv = info.byStar;
                    for (int s = 1; s < info.byStar; s++) {
                        CCSprite *st = CCSprite::createWithTexture(td);
                        st->setAnchorPoint(ccp(0, 0));
                        st->setPosition(ccp(s*getWidth(st), 0));
                        star->addChild(st);
                    }
                    star->setContentSize(CCSizeMake(info.byStar*td->getContentSize().width, getHeight(star)));
                }
                    break;
                case 2:
                {   //名字}
                    ((CCLabelTTF*)node)->setString(info.strName.c_str());
                }
                    break;
                case 3:
                {   //进阶等级}
                    ((CCLabelTTF*)node)->setString(CCString::createWithFormat("+%d",info.byEvoLv)->getCString());
                    ((CCLabelTTF*)node)->setPositionX(getRight(nodes[2]));
                }
                    break;
                case 4:
                {   //等级}
                    ((CCLabelTTF*)node)->setString(CCString::createWithFormat("%s%d",SB_Lv,info.byLv)->getCString());
                }
                    break;
                case 5:
                {   //属性1文字}
                    if (info.byType1) {
                        ((CCLabelTTF*)node)->setString(g_PacketDataMgr->getAttrText(info.byType1).c_str());
                    }
                    else{
                        node->setVisible(false);
                    }
                        
                }
                    break;
                case 6:
                {   //属性1数值}
                    if (info.byType1) {
                        ((CCLabelTTF*)node)->setString(CCString::createWithFormat("%d",info.dwValue1)->getCString());
                    }
                    else{
                        node->setVisible(false);
                    }
                }
                    break;
                case 7:
                {   //属性1图标}
                    if (info.byType1) {
                        ((CCSprite*)node)->setDisplayFrame(g_PacketDataMgr->getAttrTexture(info.byType1));
                    }
                    else{
                        node->setVisible(false);
                    }
                    
                }
                    break;
                case 8:
                {   //属性2文字}
                    if (info.byType2) {
                        ((CCLabelTTF*)node)->setString(g_PacketDataMgr->getAttrText(info.byType2).c_str());
                    }
                    else{
                        node->setVisible(false);
                    }
                    
                }
                    break;
                case 9:
                {   //属性2数值}
                    if (info.byType2) {
                        ((CCLabelTTF*)node)->setString(CCString::createWithFormat("%d",info.dwValue2)->getCString());
                    }
                    else{
                        node->setVisible(false);
                    }
                }
                    break;
                case 10:
                {   //属性2图标}
                    if (info.byType2) {
                        ((CCSprite*)node)->setDisplayFrame(g_PacketDataMgr->getAttrTexture(info.byType2));
                    }
                    else{
                        node->setVisible(false);
                    }
                    
                }
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    if (!m_isConditionsEnough)//按钮禁用}
    {
        m_pControlButtonEvolve->setEnabled(false);
    }
}

void CcbEquipEvolveLayer::ResetData()
{
    CreateEquipData();
    
}

