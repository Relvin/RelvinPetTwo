#include "CcbEquipStrengthenLayer.h"
#include "Equip.h"
#include "EquipDataMgr.h"
#include "Defines.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "EnumDefines.h"
#include "UISupport.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "PacketDataMgr.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "PetLoadingLayer.h"
#include "GuideBtnPos.h"

#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include "AnalysicsManager.h"
#endif

USING_NS_CC;
USING_NS_CC_EXT;

CcbEquipStrengthenLayer::~CcbEquipStrengthenLayer()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonEvolve);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoMoney);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin);
    CC_SAFE_RELEASE_NULL(m_pLayerElem_1);
    CC_SAFE_RELEASE_NULL(m_pLayer_no_1);
    CC_SAFE_RELEASE_NULL(m_pSprite_no_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemHaveNum1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNeedNum1);
    CC_SAFE_RELEASE_NULL(m_pNodeParent1);
    CC_SAFE_RELEASE_NULL(m_pLayerElem_2);
    CC_SAFE_RELEASE_NULL(m_pLayer_no_2);
    CC_SAFE_RELEASE_NULL(m_pSprite_no_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemHaveNum2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFItemNeedNum2);
    CC_SAFE_RELEASE_NULL(m_pNodeParent2);
    CC_SAFE_RELEASE_NULL(m_pNodeEvo);
    CC_SAFE_RELEASE_NULL(m_pNodeUnevo);
    CC_SAFE_RELEASE_NULL(m_pLayerNextIcon);
    CC_SAFE_RELEASE_NULL(m_pLayerEvoIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoCurAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoNextAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttriType1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoCurAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoNextAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttriType2);
    CC_SAFE_RELEASE_NULL(m_pLayerCurIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurName);
    CC_SAFE_RELEASE_NULL(m_pLayerEvo);
    CC_SAFE_RELEASE_NULL(m_pLayerSuit);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuit_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuitDes_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuit_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuitDes_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuit_3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFSuitDes_3);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttriType1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttriType2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri2);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStrengthen);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStrengthenMAX);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCostMoney);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCoin_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurStrength);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurLevel);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextLevel);
    CC_SAFE_RELEASE_NULL(m_pLayerStrengthen);
    CC_SAFE_RELEASE_NULL(m_pLabelEvoCurName);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhCurAttriType1);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhCurAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhCurAttriType2);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhCurAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhNextAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelEnhNextAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType1_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttriType2_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoCoin);

}

//-- copy this to CcbManager
/*
//CcbManager.h
CCNode* LoadCcbEquipStrengthenLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEquipStrengthenLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEquipStrengthenLayer", CcbEquipStrengthenLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back.ccb]", [ccb/header_back.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_strengthen.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbEquipStrengthenLayer* CcbEquipStrengthenLayer::m_curScene = NULL;

bool CcbEquipStrengthenLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

void CcbEquipStrengthenLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEquipStrengthenLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEquipStrengthenLayer::addGuideLayer)),
                                       NULL
                                       )
                    );
    
    this->runAction(
                    CCSequence::create(
                                       CCDelayTime::create(0.2f),
                                       CCCallFunc::create(this, callfunc_selector(CcbEquipStrengthenLayer::restoreTouch)),
                                       NULL
                                       )
                    );
}

void CcbEquipStrengthenLayer::restoreTouch() {
    m_bCanTouchBtn = true;
}

void CcbEquipStrengthenLayer::addGuideLayer()
{
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStrengthenMAX, GuideBtnPos::E_EQUIP_AUTO_EHAN);
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonEvolve, GuideBtnPos::E_EQUIP_EVOLVE);
        
        GuideData::GetInstance()->addGuideofEnum(
                                                 GuideData::E_SYS_GUIDE_4_EQUIP,
                                                 NULL
                                                 );
    }

}

void CcbEquipStrengthenLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEquipStrengthenLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEquipStrengthenLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvolve", CCControlButton*, this->m_pControlButtonEvolve);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoMoney", CCLabelTTF*, this->m_pLabelTTFEvoMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin", CCLabelTTF*, this->m_pLabelTTFCoin);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem_1", CcbItemIconLayer*, this->m_pLayerElem_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayer_no_1", CCLayer*, this->m_pLayer_no_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_1", CCSprite*, this->m_pSprite_no_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemHaveNum1", CCLabelTTF*, this->m_pLabelTTFItemHaveNum1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNeedNum1", CCLabelTTF*, this->m_pLabelTTFItemNeedNum1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeParent1", CCNode*, this->m_pNodeParent1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem_2", CcbItemIconLayer*, this->m_pLayerElem_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayer_no_2", CCLayer*, this->m_pLayer_no_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_no_2", CCSprite*, this->m_pSprite_no_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemHaveNum2", CCLabelTTF*, this->m_pLabelTTFItemHaveNum2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemNeedNum2", CCLabelTTF*, this->m_pLabelTTFItemNeedNum2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeParent2", CCNode*, this->m_pNodeParent2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeEvo", CCNode*, this->m_pNodeEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeUnevo", CCNode*, this->m_pNodeUnevo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEvoIcon",CcbItemIconLayer* , this->m_pLayerEvoIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerNextIcon", CcbItemIconLayer*, this->m_pLayerNextIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextName", CCLabelTTF*, this->m_pLabelTTFNextName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType1", CCLabelTTF*, this->m_pLabelTTFCurAttriType1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoCurAttri1", CCLabelTTF*, this->m_pLabelTTFEvoCurAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoNextAttri1", CCLabelTTF*, this->m_pLabelTTFEvoNextAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttriType1", CCLabelTTF*, this->m_pLabelTTFNextAttriType1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType2", CCLabelTTF*, this->m_pLabelTTFCurAttriType2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoCurAttri2", CCLabelTTF*, this->m_pLabelTTFEvoCurAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoNextAttri2", CCLabelTTF*, this->m_pLabelTTFEvoNextAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttriType2", CCLabelTTF*, this->m_pLabelTTFNextAttriType2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerCurIcon", CcbItemIconLayer*, this->m_pLayerCurIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurName", CCLabelTTF*, this->m_pLabelTTFCurName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerEvo", CCLayer*, this->m_pLayerEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerSuit", CCLayer*, this->m_pLayerSuit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuit_1", CCLabelTTF*, this->m_pLabelTTFSuit_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuitDes_1", CCLabelTTF*, this->m_pLabelTTFSuitDes_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuit_2", CCLabelTTF*, this->m_pLabelTTFSuit_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuitDes_2", CCLabelTTF*, this->m_pLabelTTFSuitDes_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuit_3", CCLabelTTF*, this->m_pLabelTTFSuit_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFSuitDes_3", CCLabelTTF*, this->m_pLabelTTFSuitDes_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttriType1", CCLabelTTF*, this->m_pLabelTTFAttriType1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri1", CCLabelTTF*, this->m_pLabelTTFCurAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri1", CCLabelTTF*, this->m_pLabelTTFNextAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttriType2", CCLabelTTF*, this->m_pLabelTTFAttriType2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri2", CCLabelTTF*, this->m_pLabelTTFCurAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri2", CCLabelTTF*, this->m_pLabelTTFNextAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrengthen", CCControlButton*, this->m_pControlButtonStrengthen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrengthenMAX", CCControlButton*, this->m_pControlButtonStrengthenMAX);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCostMoney", CCLabelTTF*, this->m_pLabelTTFCostMoney);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCoin_2", CCLabelTTF*, this->m_pLabelTTFCoin_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurStrength", CCLabelTTF*, this->m_pLabelTTFCurStrength);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurLevel", CCLabelTTF*, this->m_pLabelTTFCurLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextLevel", CCLabelTTF*, this->m_pLabelTTFNextLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerStrengthen", CCLayer*, this->m_pLayerStrengthen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelEvoCurName", CCLabelTTF*, this->m_pLabelEvoCurName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelEnhCurAttriType1",CCLabelTTF* ,this->m_pLabelEnhCurAttriType1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelEnhCurAttri1",CCLabelTTF* ,this->m_pLabelEnhCurAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelEnhCurAttriType2",CCLabelTTF* ,this->m_pLabelEnhCurAttriType2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this,"m_pLabelEnhCurAttri2",CCLabelTTF* ,this->m_pLabelEnhCurAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelEnhNextAttri1", CCLabelTTF*, this->m_pLabelEnhNextAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelEnhNextAttri2", CCLabelTTF*, this->m_pLabelEnhNextAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType1_2", CCLabelTTF*, this->m_pLabelTTFCurAttriType1_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttriType2_2", CCLabelTTF*, this->m_pLabelTTFCurAttriType2_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoCoin", CCLabelTTF*, this->m_pLabelTTFEvoCoin);
	return false;
}

bool CcbEquipStrengthenLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEquipStrengthenLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEquipStrengthenLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEquipStrengthenLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrengthen", CcbEquipStrengthenLayer::onPressControlButtonStrengthen);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrengthenMAX", CcbEquipStrengthenLayer::onPressControlButtonStrengthenMAX);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvolve", CcbEquipStrengthenLayer::onPressControlButtonEvolve);
    
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEquipStrengthenLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
//    m_isEnterFirst = true;
    arrPerValue[0] = 0;
    arrPerValue[1] = 0;
    m_isNeedFly = false;
//    CreateEquipData();
}

void CcbEquipStrengthenLayer::CreateEquipData()
{
    arrPerValue[0] = 0;
    arrPerValue[1] = 0;
    if (byShowLayerType == 0) {
        loadEnhData();
    }
    else
    {
        this->loadEvoData();
    }
    
    m_pLabelTTFCoin->setString(CCString::createWithFormat("%d", CGameSession::GetRole()->GetdwCoin())->getCString());
}
void CcbEquipStrengthenLayer::loadEnhData()
{
    byShowLayerType = 0;
    m_pLayerEvo->setVisible(false);
    m_pLayerStrengthen->setVisible(true);
    CRole* role = CGameSession::GetRole();
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    char szTemp[256] = "";
    //强化}
    if (pEquip)
    {
        //装备名字}
        if (pEquip->getEvoLv() > 0) {
            sprintf(szTemp, "%s+%d", pEquip->GetConfigData().strName.c_str(), pEquip->getEvoLv());
        }
        else{
            sprintf(szTemp, "%s", pEquip->GetConfigData().strName.c_str());
        }
        m_pLabelTTFCurName->setString(szTemp);
        uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pEquip->GetIndex());
        m_pLabelTTFCurName->setColor(g_PacketDataMgr->getQualityColor(quality));
        
        //等级}
        sprintf(szTemp, "%d / %d", pEquip->GetLevel(), role->GetwRoleLv()*2);
        m_pLabelTTFCurLevel->setString(szTemp);
        sprintf(szTemp, "%d / %d", pEquip->GetLevel()+1, role->GetwRoleLv()*2);
        m_pLabelTTFNextLevel->setString(szTemp);
        
        //装备属性}
        //属性类型}
        uint8 byProType[2];
        byProType[0] = pEquip->GetConfigData().byEffectType1;
        byProType[1] = pEquip->GetConfigData().byEffectType2;
        //当前属性值}
        uint32 dwProCurValue[2];
        
        dwProCurValue[0] = pEquip->getEquipAttrInfoByType(byProType[0]);
        dwProCurValue[1] = pEquip->getEquipAttrInfoByType(byProType[1]);
        
        //强化后属性值}
        uint32 dwProNextValue[2];
        dwProNextValue[0] = dwProCurValue[0] + pEquip->GetConfigData().wGrowthRate1;
        dwProNextValue[1] = dwProCurValue[1] + pEquip->GetConfigData().wGrowthRate2;

        CCLabelTTF* arrProName[2];
        CCLabelTTF* arrProLblCur[2];
        CCLabelTTF* arrProLblNext[2];
        arrProName[0] = m_pLabelEnhCurAttriType1;
        arrProName[1] = m_pLabelEnhCurAttriType2;
        arrProLblCur[0] = m_pLabelEnhCurAttri1;
        arrProLblCur[1] = m_pLabelEnhCurAttri2;
        arrProLblNext[0] = m_pLabelEnhNextAttri1;
        arrProLblNext[1] = m_pLabelEnhNextAttri2;
        
        int cnt = 0;
        CCString* str = CCString::create("");
        for (int i = 0; i < 2; i++) {
            if (byProType[i] == 0) {
                continue;
            }
            arrProLblCur[cnt]->getParent()->setVisible(true);
            arrProName[cnt]->setString(g_PacketDataMgr->getAttrText(byProType[i]).c_str());
            str->initWithFormat("+%d", dwProCurValue[i]);
            arrProLblCur[cnt]->setString(str->getCString());
            str->initWithFormat("+%d", dwProNextValue[i]);
            arrProLblNext[cnt]->setString(str->getCString());

            arrPerValue[cnt] = dwProCurValue[i];
            
            cnt++;
        }
        for (; cnt < 2; cnt++) {
            arrProLblCur[cnt]->getParent()->setVisible(false);
        }
        
        //Icon
        m_pLayerIcon->loadIndexData(pEquip->GetIndex());
        m_pLayerIcon->showIconOnly();
        m_pLayerIcon->showStarLv();
        m_pLayerIcon->setBtnEnable(false);
        
        //消耗金钱}
        uint32 dwStrengthenCost = 0;
        ExpConfig::STC_EXP_CONFIG *pExpConfig = GET_CONFIG_STC(ExpConfig, pEquip->GetLevel());
        if (pExpConfig)
        {
            dwStrengthenCost = pExpConfig->dwEquipCost * pEquip->GetConfigData().dwCostBaseValue / 100;
        }
        else
        {
            CCLOG("Error: get strengthen cost money config error.");
        }
        
        sprintf(szTemp, "%d", dwStrengthenCost);
        m_pLabelTTFCostMoney->setString(szTemp);
        
        
        m_pControlButtonStrengthen->setEnabled(true);
        m_pControlButtonStrengthenMAX->setEnabled(true);
        
        if (dwStrengthenCost > role->GetdwCoin()) {
            m_pLabelTTFCostMoney->setColor(ccRED);
        }
        else{
            m_pLabelTTFCostMoney->setColor(ccWHITE);
        }
        
        if (pEquip->GetLevel() >= role->GetwRoleLv() * 2) {
            m_pControlButtonStrengthen->setEnabled(false);
            m_pControlButtonStrengthenMAX->setEnabled(false);
        }
    }
}
void CcbEquipStrengthenLayer::loadEvoData()
{
    m_pLayerEvo->setVisible(true);
    m_pLayerStrengthen->setVisible(false);
    byShowLayerType = 1;

    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    char szTemp[256] = "";
    
    
    //进阶}
    if (pEquip->GetConfigData().dwEvoItemID == 0)
    {
        m_pNodeUnevo->setVisible(true);
        m_pNodeEvo->setVisible(false);
    }
    else
    {
        m_pNodeUnevo->setVisible(false);
        m_pNodeEvo->setVisible(true);
        
        bool m_isConditionsEnough = true;
        //未进阶到最高}
        LP_EQUIPEVO_CONFIG pEvoConfig = pEquip->GetEvoConfigDataByLv(pEquip->getEvoLv() + 1);
        if (!pEvoConfig)
        {
            CCLog("Equip.csv read error, can not find ID, %ud", pEquip->GetConfigData().dwEvoItemID);
            return;
        }
        
        m_pLayerEvoIcon->loadIndexData(pEquip->GetIndex());
        m_pLayerEvoIcon->showIconOnly();
        m_pLayerEvoIcon->showStarLv();
        m_pLayerEvoIcon->setBtnEnable(false);
        
        m_pLayerNextIcon->loadIndexData(pEquip->GetIndex());
        m_pLayerNextIcon->showIconOnly();
        m_pLayerNextIcon->showStarLv();
        m_pLayerNextIcon->setBtnEnable(false);
        
        //钱
        sprintf(szTemp, "%d", pEvoConfig->dwEvoCostMoney);
        m_pLabelTTFEvoMoney->setString(szTemp);
        CRole* role = CGameSession::GetRole();
        if (role->GetdwCoin() < pEvoConfig->dwEvoCostMoney) {
            m_pLabelTTFEvoMoney->setColor(ccRED);
        }
        else{
            m_pLabelTTFEvoMoney->setColor(ccWHITE);
        }
        
        memset(szTemp, '\0', sizeof(szTemp));
        sprintf(szTemp, "%d", role->GetdwCoin());
        m_pLabelTTFEvoCoin->setString(szTemp);
        
        //装备名}
        memset(szTemp, '\0', sizeof(szTemp));
        if (pEquip->getEvoLv() > 0) {
            sprintf(szTemp, "%s+%d", pEquip->GetConfigData().strName.c_str(), pEquip->getEvoLv());
        }
        else{
            sprintf(szTemp, "%s", pEquip->GetConfigData().strName.c_str());
        }
        m_pLabelEvoCurName->setString(szTemp);

        memset(szTemp, '\0', sizeof(szTemp));
        sprintf(szTemp, "%s+%d", pEquip->GetConfigData().strName.c_str(), pEquip->getEvoLv() + 1);
        m_pLabelTTFNextName->setString(szTemp);
        
        uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(pEquip->GetIndex());
        m_pLabelTTFNextName->setColor(g_PacketDataMgr->getQualityColor(quality));
        
        //属性类型}
        uint8 byProType[2];
        byProType[0] = pEquip->GetConfigData().byEvoType1;
        byProType[1] = pEquip->GetConfigData().byEvoType2;
        
        //当前属性值}
        float fProCurValue[2];
        
        
        fProCurValue[1] = pEquip->GetConfigData().dwEvoData2 * (pEquip->getEvoLv() + 1);
        
        //进阶后属性值}
        fProCurValue[0] = pEquip->GetConfigData().dwEvoData1 * pEquip->getEvoLv();
        fProCurValue[1] = pEquip->GetConfigData().dwEvoData2 * pEquip->getEvoLv();
        float fProNextValue[2];
        fProNextValue[0] = pEquip->GetConfigData().dwEvoData1 * (pEquip->getEvoLv() + 1);
        fProNextValue[1] = pEquip->GetConfigData().dwEvoData2 * (pEquip->getEvoLv() + 1);
        
        
        CCLabelTTF* arrProName[2];
        CCLabelTTF* arrProLblCur[2];
        CCLabelTTF* arrNextName[2];
        CCLabelTTF* arrNextLblCur[2];
        
        arrProName[0] = m_pLabelTTFCurAttriType1;
        arrProName[1] = m_pLabelTTFCurAttriType2;
        arrProLblCur[0] = m_pLabelTTFCurAttri1;
        arrProLblCur[1] = m_pLabelTTFCurAttri2;
        
        arrNextName[0] = m_pLabelTTFCurAttriType1_2;
        arrNextName[1] = m_pLabelTTFCurAttriType2_2;
        arrNextLblCur[0] = m_pLabelTTFNextAttri1;
        arrNextLblCur[1] = m_pLabelTTFNextAttri2;
        
        int cnt = 0;
        CCString* str = CCString::create("");
        for (int i = 0; i < 2; i++) {
            if (byProType[i] == 0) {
                continue;
            }
            arrProLblCur[cnt]->getParent()->setVisible(true);
            arrProName[cnt]->setString(g_PacketDataMgr->getAttrText(byProType[i]).c_str());
            arrNextName[cnt]->setString(g_PacketDataMgr->getAttrText(byProType[i]).c_str());
            
            if (pEquip->GetConfigData().byEvoDataType1 == 1 || fProCurValue[i] == 0) {
                str->initWithFormat("+%0.0f", fProCurValue[i]);
            }
            else
            {
                str->initWithFormat("+%0.1f%%", fProCurValue[i] / 100);
            }
            
            arrProLblCur[cnt]->setString(str->getCString());
            
            if (pEquip->GetConfigData().byEvoDataType2 == 1 || fProNextValue[i] == 0) {
                str->initWithFormat("+%0.0f", fProNextValue[i]);
                
            }
            else
            {
                str->initWithFormat("+%0.1f%%", fProNextValue[i] / 100);
            }
            
            
            arrNextLblCur[cnt]->setString(str->getCString());
            
            cnt++;
        }
        for (; cnt < 2; cnt++) {
            arrProLblCur[cnt]->getParent()->setVisible(false);
        }

        //进阶材料}
        //材料}

        if (pEvoConfig->dwEvoMaterial1) {
            m_pLayerElem_1->getParent()->setVisible(true);
            m_pLayerElem_1->loadIndexData(pEvoConfig->dwEvoMaterial1);
            m_pLayerElem_1->showIconOnly();
            m_pLayerElem_1->setIsShowDropInfo(true);
            
            uint32 dwItemHave = g_PacketDataMgr->GetItemCountByIndex(pEvoConfig->dwEvoMaterial1);
            str->initWithFormat("%d", dwItemHave);
            m_pLabelTTFItemHaveNum1->setString(str->getCString());
            str->initWithFormat("%d", pEvoConfig->dwEvoMaterial1Num);
            m_pLabelTTFItemNeedNum1->setString(str->getCString());
            if (dwItemHave < pEvoConfig->dwEvoMaterial1Num)
            {
                m_pLabelTTFItemHaveNum1->setColor(ccRED);
                m_pSprite_no_1->setVisible(true);
                m_pLayer_no_1->setVisible(true);
                m_isConditionsEnough = false;
            }
            else
            {
                m_pLabelTTFItemHaveNum1->setColor(ccWHITE);
                m_pSprite_no_1->setVisible(false);
                m_pLayer_no_1->setVisible(false);
            }
            
        }
        else{
            m_pLayerElem_1->getParent()->setVisible(false);
        }
        
        
        if (pEvoConfig->dwEvoMaterial2) {
            m_pLayerElem_1->getParent()->setVisible(true);
            
            m_pLayerElem_2->loadIndexData(pEvoConfig->dwEvoMaterial2);
            m_pLayerElem_2->showIconOnly();
            m_pLayerElem_2->setIsShowDropInfo(true);
            
            uint32 dwItemHave = g_PacketDataMgr->GetItemCountByIndex(pEvoConfig->dwEvoMaterial2);
            str->initWithFormat("%d", dwItemHave);
            m_pLabelTTFItemHaveNum2->setString(str->getCString());
            str->initWithFormat("%d", pEvoConfig->dwEvoMaterial2Num);
            m_pLabelTTFItemNeedNum2->setString(str->getCString());
            if (dwItemHave < pEvoConfig->dwEvoMaterial2Num)
            {
                m_pLabelTTFItemHaveNum2->setColor(ccRED);
                m_isConditionsEnough = false;
                m_pSprite_no_2->setVisible(true);
                m_pLayer_no_2->setVisible(true);
            }
            else
            {
                m_pLabelTTFItemHaveNum2->setColor(ccWHITE);
                m_pSprite_no_2->setVisible(false);
                m_pLayer_no_2->setVisible(false);
            }
        }
        else{
            m_pLayerElem_1->getParent()->setVisible(false);
        }
        
        m_pControlButtonEvolve->setEnabled(m_isConditionsEnough);
    }
}

void CcbEquipStrengthenLayer::onPressControlButtonStrengthen(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    m_isNeedFly = true;
    CGameSession::SendUpgradeEquip(g_EquipData->GetChosenEquipKeyID(), 0);
    byEnhCnt = 1;
}

void CcbEquipStrengthenLayer::onPressControlButtonStrengthenMAX(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    m_isNeedFly = true;
    CGameSession::SendUpgradeEquip(g_EquipData->GetChosenEquipKeyID(), 1);
    byEnhCnt = 1;
    
    CRole* pRole = CGameSession::GetRole();
    if (pRole->GetwRoleLv() < GUIDE_LV) {
        if (pRole->GetwGuideTrigger() == GuideData::E_SYS_GUIDE_END_EQUIP) {
            GuideData::GetInstance()->onlyRmGuideLayer();
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
            AnalysicsManager::sharedAnalyticsMgr()->SendEvent("equip_guide_end");
#endif
        } else {
            GuideData::GetInstance()->addGuideofEnum(
                                                     GuideData::E_SYS_GUIDE_7_HERO,
                                                     NULL
                                                     );
        }
    }
}

void CcbEquipStrengthenLayer::onPressControlButtonEvolve(CCObject* pSender, CCControlEvent event)
{
    if (!m_bCanTouchBtn) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    PetLoadingLayer::sharedLayer()->WaitForPacket();
    m_isNeedFly = true;
    byEnhCnt = 10;
    CGameSession::SendReqEquipEvolve(g_EquipData->GetChosenEquipKeyID());
    
    GuideData::GetInstance()->addGuideofEnum(
                                             GuideData::E_SYS_GUIDE_END_HERO,
                                             NULL
                                             );
}

void CcbEquipStrengthenLayer::handlerEnh()
{
    this->loadEnhData();
    PetLoadingLayer::sharedLayer()->End();
    
    m_pLabelTTFCoin->setString(CCString::createWithFormat("%d", CGameSession::GetRole()->GetdwCoin())->getCString());
    
    EffectLayer* effLayer = EffectLayer::create(E_ANI_EFFECT_EQUIP_ENH_EFF, 1.0 / 20.0);
    effLayer->setPosition(getCenter(m_pLayerIcon));
    effLayer->setAnchorPoint(ccp(0.5, 0.5));
    effLayer->ignoreAnchorPointForPosition(false);
    //    effLayer->setDelegate(this);
    effLayer->setScale(0.75);
    m_pLayerIcon->getParent()->addChild(effLayer, 1, 1212);
    effLayer->onRun();
    
    CCParticleSystemQuad* eff = CCParticleSystemQuad::create("ccbresources/12monthdate/equip/enh_one.plist");
    if (byEnhCnt > 1) {
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_armor_upgrade));
        eff = CCParticleSystemQuad::create("ccbresources/12monthdate/equip/enh_all.plist");
        CCParticleSystemQuad* effbg = CCParticleSystemQuad::create("ccbresources/12monthdate/equip/guanghuan.plist");
        effbg->setPosition(getCenter(m_pLayerIcon));
        effbg->setAnchorPoint(ccp(0.5, 0.5));
        effbg->ignoreAnchorPointForPosition(false);
        effbg->setScale(0.4 * 0.75);
        m_pLayerIcon->getParent()->addChild(effbg, 1);
        
    }
    else{
        CMusicCtrl::PlayEffect(GET_MUSIC(Eff_armor_lvup));
    }
    eff->setScale(0.6 * 0.75);
    eff->setPosition(getCenter(m_pLayerIcon));
    eff->setAnchorPoint(ccp(0.5, 0.5));
    eff->ignoreAnchorPointForPosition(false);
    m_pLayerIcon->getParent()->addChild(eff, 2);
}

void CcbEquipStrengthenLayer::handlerEvo()
{
    this->loadEvoData();
}

