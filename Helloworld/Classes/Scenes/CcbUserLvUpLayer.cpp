#include "CcbUserLvUpLayer.h"
//#include "CcbManager.h"
#include "GameSession.h"
#include "PetBattleData.h"
#include "FightAI.h"
#include "UISupport.h"
#include "GuideData.h"
#include "ConfigGet.h"
#include "ResourceDefine.h"
#include "CcbFightRewardLayer.h"
#include "MusicCtrl.h"
#include "ResourceStringClient.h"
#include "ResourcePic.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbUserLvUpLayer::~CcbUserLvUpLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerFuncBg);
    CC_SAFE_RELEASE_NULL(m_pSpriteText_GongNengKaiFang);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurEnergy);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextEnergy);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurStage);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextStage);
    CC_SAFE_RELEASE_NULL(m_pSpriteStageUp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFLv_0);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEquip_Lv1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFEquip_Lv0);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPet_Lv1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPet_Lv0);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbUserLvUpLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbUserLvUpLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbUserLvUpLayer", CcbUserLvUpLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/user_levelup.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbUserLvUpLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbUserLvUpLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_player_lv_up));
}

void CcbUserLvUpLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_rank_up));
}

void CcbUserLvUpLayer::onExit()
{
	CCLayer::onExit();
}

void CcbUserLvUpLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbUserLvUpLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerFuncBg", CCLayer*, this->m_pLayerFuncBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteText_GongNengKaiFang", CCSprite*, this->m_pSpriteText_GongNengKaiFang);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurEnergy", CCLabelTTF*, this->m_pLabelTTFCurEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextEnergy", CCLabelTTF*, this->m_pLabelTTFNextEnergy);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurStage", CCLabelTTF*, this->m_pLabelTTFCurStage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextStage", CCLabelTTF*, this->m_pLabelTTFNextStage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStageUp", CCSprite*, this->m_pSpriteStageUp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv_0", CCLabelTTF*, this->m_pLabelTTFLv_0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquip_Lv1", CCLabelTTF*, this->m_pLabelTTFEquip_Lv1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEquip_Lv0", CCLabelTTF*, this->m_pLabelTTFEquip_Lv0);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPet_Lv1", CCLabelTTF*, this->m_pLabelTTFPet_Lv1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPet_Lv0", CCLabelTTF*, this->m_pLabelTTFPet_Lv0);


	return false;
}

bool CcbUserLvUpLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbUserLvUpLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbUserLvUpLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbUserLvUpLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbUserLvUpLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbUserLvUpLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pSpriteStageUp->setVisible(false);
    m_pSpriteText_GongNengKaiFang->setVisible(false);
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
}



void CcbUserLvUpLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (m_delegate) {
        CcbFightRewardLayer* expLayer = dynamic_cast<CcbFightRewardLayer*>(m_delegate);
        if (expLayer) {
            expLayer->onLvUpEnd();
        }
    }
    
    removeFromParent();
}

void CcbUserLvUpLayer::loadData()
{
    CRole* role = CGameSession::GetRole();
    STC_BATTLE_PRE_DATA perData = FightAI::Get()->getPerData();
    
    //等级}
    CCString* str = CCString::createWithFormat("%s%d", SB_Lv, role->GetwRoleLv());
    m_pLabelTTFLv->setString(str->getCString());
    //升级前}
    str->initWithFormat("%s%d", SB_Lv, perData.wUserLv);
    m_pLabelTTFLv_0->setString(str->getCString());
    //体力}
    str->initWithFormat("%d", perData.dwCurEnergy);
    m_pLabelTTFCurEnergy->setString(str->getCString());
    //战位}
    if (perData.byCurFightCnt == role->GetdwBattleBagCnt()) {
        m_pLabelTTFCurStage->getParent()->setVisible(false);
    }
    str->initWithFormat("%d", perData.byCurFightCnt);
    m_pLabelTTFCurStage->setString(str->getCString());
    //宠物等级上限}
    str->initWithFormat("%d", perData.wUserLv);
    m_pLabelTTFPet_Lv0->setString(str->getCString());
    //装备强化等级上限}
    str->initWithFormat("%d", perData.wUserLv*2);
    m_pLabelTTFEquip_Lv0->setString(str->getCString());
    
    //升级后}
    //体力}
    str->initWithFormat("%d", role->GetdwEnergy());
    m_pLabelTTFNextEnergy->setString(str->getCString());
    
    std::map<uint16, std::string> mapOpenFunc;
    
//    bool isFightUp = role->GetdwBattleBagCnt() > perData.byCurFightCnt;
    float w = 0;
    //战位}
    str->initWithFormat("%d", role->GetdwBattleBagCnt());
    m_pLabelTTFNextStage->setString(str->getCString());
    
    //宠物等级上限}
    str->initWithFormat("%d", role->GetwRoleLv());
    m_pLabelTTFPet_Lv1->setString(str->getCString());
    //装备强化等级上限}
    str->initWithFormat("%d", role->GetwRoleLv()*2);
    m_pLabelTTFEquip_Lv1->setString(str->getCString());
    
    //TODO: 此处站位开放的判断是否和后面的开放判断重复？}
//    if (isFightUp) {
//        m_pLabelTTFNextStage->setColor(ccGREEN);
//        m_pSpriteStageUp->setVisible(true);
//        mapOpenFunc[GuideData::E_GUIDE_FUNC_ICON_FIGHT_CNT] = GET_STR(Str_team_site_open);
//    }

    //功能开放}
    uint16 sysLockId = GuideData::GetInstance()->checkSystemLock(GuideData::E_GUIDE_UNLOCK_TYPE_LV);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, sysLockId);
    if (cfg) {
        int len = 0;
        GET_ARRAY_LEN(cfg->wIcon, len);
        for (int i = 0; i < len; i++) {
            if (cfg->wIcon[i]) {
                mapOpenFunc[cfg->wIcon[i]] = cfg->strIconName[i];
            }
        }
    }
    if (mapOpenFunc.size() > 0) {
        m_pSpriteText_GongNengKaiFang->setVisible(true);
        w = getWidth(m_pLayerFuncBg) / mapOpenFunc.size();
    }
    
    uint8 count = 0;
    std::map<uint16, std::string>::iterator it = mapOpenFunc.begin();
    
    CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    pCache->addSpriteFramesWithFile(
                                    GET_PIC(Pic_unit_plist),
                                    GET_PIC(Pic_unit_pvr_ccz)
                                    );
    pCache->addSpriteFramesWithFile(
                                    GET_PIC(Pic_main_plist),
                                    GET_PIC(Pic_main_pvr_ccz)
                                    );
    
    for (; it != mapOpenFunc.end(); it++) {
        if (!it->first) {
            continue;
        }
        std::string path = PIC_DEFAULT;
        switch (it->first) {
            case GuideData::E_GUIDE_FUNC_ICON_FIGHT_CNT:
            case GuideData::E_GUIDE_FUNC_ICON_EDIT_TEAM:
                path = GET_PIC(Btn_edit_team); //队伍编辑}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_EQUIP:
                path = GET_PIC(Btn_equip_enhance); //装备一览}
                break;

            case GuideData::E_GUIDE_FUNC_ICON_ARENA:
                path = GET_PIC(Btn_arena);//竞技场}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_MY_STERY:
                path = GET_PIC(Btn_mystery_shop);//神秘商店}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_SPECIAL_STAGE:
                path = GET_PIC(Btn_hero_map);   // 精英关卡}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_ACTIVITY_STAGE:
                path = GET_PIC(Btn_active); //活动关卡（遗迹）}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_RUNE_INLAY:
                path = GET_PIC(Btn_emblem); //符文镶嵌}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_PATA:
                path = GET_PIC(Btn_active); //Tower[遗迹]}
                break;
            case GuideData::E_GUIDE_FUNC_ICON_BADGE:
                path = GET_PIC(Btn_badage); //BADGE
                break;

            default:
                continue;
                break;
        }
        
        CCSprite* func = NULL;
        if (it->first == GuideData::E_GUIDE_FUNC_ICON_MY_STERY || it->first == GuideData::E_GUIDE_FUNC_ICON_SPECIAL_STAGE) {
            func = CCSprite::create(path.c_str());
        } else {
            CCSpriteFrame* pFrame = pCache->spriteFrameByName(path.c_str());
            func = CCSprite::createWithSpriteFrame(pFrame);
        }

        func->setPosition(ccp((count+0.5)*w, getHeight(m_pLayerFuncBg)*0.5));
        func->setAnchorPoint(ccp(0.5, 0.5));
        m_pLayerFuncBg->addChild(func);
        
        CCLabelTTF* lblName = CCLabelTTF::create(it->second.c_str(), FONT_FZCQJW, 13);
        lblName->setPosition(ccp(getCenterX(func), getBottom(func)));
        lblName->setAnchorPoint(ccp(0.5, 0));
        m_pLayerFuncBg->addChild(lblName);
        
        count++;
    }
}

bool CcbUserLvUpLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbUserLvUpLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}



