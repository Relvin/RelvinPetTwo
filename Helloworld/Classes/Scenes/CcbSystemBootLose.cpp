#include "CcbSystemBootLose.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "BackCtrl.h"
#include "GuideData.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "FlyTextLayer.h"
#include "EquipDataMgr.h"
#include "GameSession.h"
#include "Role.h"
#include "TeamCtrl.h"
#include "Team.h"
#include "Pet.h"
#include "UISupport.h"
#include "PacketDataMgr.h"
#include "FightAI.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbSystemBootLose::~CcbSystemBootLose()
{
    CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonTeam);
    CC_SAFE_RELEASE_NULL(m_pControlButtonGacha);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEquip);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEvo);
    CC_SAFE_RELEASE_NULL(m_pControlButtonEnh);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSystemBootLose( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSystemBootLose( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbSystemBootLose", CcbSystemBootLoseLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/system_boot_lose.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbSystemBootLose::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbSystemBootLose::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    checkBtn();
}

void CcbSystemBootLose::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbSystemBootLose::onExit()
{
	CCLayer::onExit();
}

void CcbSystemBootLose::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbSystemBootLose::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonTeam", CCControlButton*, this->m_pControlButtonTeam);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonGacha", CCControlButton*, this->m_pControlButtonGacha);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip", CCControlButton*, this->m_pControlButtonEquip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEvo", CCControlButton*, this->m_pControlButtonEvo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEnh", CCControlButton*, this->m_pControlButtonEnh);

	return false;
}

bool CcbSystemBootLose::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbSystemBootLose::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSystemBootLose::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbSystemBootLose::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbSystemBootLose::onPressControlButtonBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonTeam", CcbSystemBootLose::onPressControlButtonTeam);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquip", CcbSystemBootLose::onPressControlButtonEquip);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEvolve", CcbSystemBootLose::onPressControlButtonEvolve);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEnh", CcbSystemBootLose::onPressControlButtonEnh);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonGacha", CcbSystemBootLose::onPressControlButtonGacha);
	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbSystemBootLose::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonBack->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonTeam->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonGacha->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonEvo->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonEquip->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
    m_pControlButtonEnh->setTouchPriority(kCCMenuHandlerPriority*2 - 1);
}



void CcbSystemBootLose::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_FRIEND) {
        BackCtrl::ChangeRootScene(kFriendUnitScene);
        return;
    }
    BackCtrl::BacktoUpperScene();
}

void CcbSystemBootLose::onPressControlButtonTeam(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::ChangeRootScene(kTeamScene);
}

void CcbSystemBootLose::onPressControlButtonGacha(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::ChangeRootScene(kGachaScene);
}

void CcbSystemBootLose::onPressControlButtonEnh(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_INTENSIFY_PRIMARY);
    BackCtrl::ChangeRootScene(kPetBagScene);
}

void CcbSystemBootLose::onPressControlButtonEvolve(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    CPetCtrl::Get()->SetPetBagType(CPetCtrl::Get()->E_BAG_ENTER_TYPE_EVOLVE);
    BackCtrl::ChangeRootScene(kPetBagScene);
}

void CcbSystemBootLose::onPressControlButtonEquip(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_EQUIP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    g_EquipData->SetDressEquipPart(0);
    g_EquipData->setIsEquipShow(false);
    BackCtrl::ChangeRootScene(kEquipIntegrationScene);
}

void CcbSystemBootLose::checkBtn()
{
    CRole *role = CGameSession::GetRole();
    //宠物强化
    bool isPetEnh = false;
    bool isPetEvo = false;
    CTeam* team = CTeamCtrl::GetCurTeam();
    for (int i = 1; i < team->getarrPetObId().size(); i++) {
        if (!team->getarrPetObId()[i]) {
            continue;
        }
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[i]);
        if (!pet) {
            continue;
        }
        if (pet->GetbyLv() < role->GetwRoleLv()) {
            isPetEnh = true;
        }
        //判进化
        uint16 curId = GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv());
        EvolveConfig::STC_EVOLVE_CONFIG* curCfg = GET_CONFIG_STC(EvolveConfig, curId);
        if (!curCfg) {
            continue;
        }
        EvolveConfig::STC_EVOLVE_CONFIG* nextCfg = GET_CONFIG_STC(EvolveConfig, curCfg->wNextId);
        if (!nextCfg) {
            continue;
        }
        if (nextCfg->wPetLv <= pet->GetbyLv()) {
            isPetEvo = true;
        }
        break;
    }
    if (isPetEnh) {
        //判断是否有材料宠
        if(CPetCtrl::Get()->selectEnhanceElemAuto() > 0){
            CPetCtrl::Get()->ClearSelectedPet();
        }
        else{
            isPetEnh = false;
        }
        
    }
    if (isPetEnh) {
        m_pControlButtonEnh->getParent()->setVisible(true);
    }
    else{
        m_pControlButtonEnh->getParent()->setVisible(false);
    }
    //宠物进阶
    if (isPetEvo && role->GetwRoleLv() >= 18) {
        m_pControlButtonEvo->getParent()->setVisible(true);
    }
    else{
        m_pControlButtonEvo->getParent()->setVisible(false);
    }
    
    //装备
    bool isEquip = false;
    for (int i = 1; i < team->getarrPetObId().size(); i++) {
        if (!team->getarrPetObId()[i]) {
            continue;
        }
        CPet *pet = CPetCtrl::Get()->GetPetByObjId(team->getarrPetObId()[i]);
        if (!pet) {
            continue;
        }
        std::map<uint8, uint32>mapEquip = g_EquipTeamData->getEquipsBySite(i);
        std::map<uint8, uint32>::iterator it = mapEquip.begin();
        for (; it != mapEquip.end(); it++) {
            if (!it->second) {
                continue;
            }
            const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(it->second);
            if (!equip) {
                continue;
            }
            
            //强化
            if (equip->GetLevel() < role->GetwRoleLv() *2) {
                isEquip = true;
                break;
            }
            
            //进阶
            //add by Relvin need modify
//            if (equip->GetConfigData().dwEvoID && equip->GetLevel() >= equip->GetConfigData().wEvoLV) {
//                isEquip = true;
//                break;
//            }
        }
        if (isEquip) {
            break;
        }
    }
    if (isEquip && role->GetwRoleLv() >= 15) {
        m_pControlButtonEquip->getParent()->setVisible(true);
    }
    else{
        m_pControlButtonEquip->getParent()->setVisible(false);
    }
    
    if (role->GetwRoleLv() >= 18) {
        m_pControlButtonTeam->getParent()->setVisible(true);
    }
    else{
        m_pControlButtonTeam->getParent()->setVisible(false);
    }
    
    //调整位置
    std::vector<CCNode*> arrNode;
    float h = m_pControlButtonEnh->getParent()->getPositionY();
    arrNode.push_back(m_pControlButtonEnh->getParent());
    arrNode.push_back(m_pControlButtonEquip->getParent());
    arrNode.push_back(m_pControlButtonEvo->getParent());
    arrNode.push_back(m_pControlButtonTeam->getParent());
    for (int i = 0; i < arrNode.size(); i++) {
        if (arrNode[i]->isVisible()) {
            arrNode[i]->setPositionY(h);
            h -= getHeight(arrNode[i]);
        }
    }
}

void CcbSystemBootLose::showLose()
{
    CCNode* node = CcbManager::sharedManager()->LoadCcbSystemBootLose();
    if (node) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        node->setPosition(winSize / 2);
        node->setAnchorPoint(ccp(0.5, 0.5));
        node->ignoreAnchorPointForPosition(false);
        CCDirector::sharedDirector()->getRunningScene()->addChild(node, 999);
    }
}

bool CcbSystemBootLose::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbSystemBootLose::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority*2, true);
}



