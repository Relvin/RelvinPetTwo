#include "CcbPetBattleLoading.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "GameSession.h"
#include "FightAI.h"
#include "CcbPetBattleLayer.h"
#include "Support.h"
#include "Role.h"
#include "MapScene.h"
#include "ConfigUtil.h"
#include "ResourceDefine.h"
#include "FightPet.h"
#include "PetCtrl.h"
#include "FightTeam.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "AltEffArmature.h"
#include "ArmatureManager.h"

//#include "StageScene.h"

//static std::vector<EpitasisConfig::STC_EPITASIS_CONFIG> m_vecTalkPad;
//typedef std::map<uint32, EpitasisConfig::STC_EPITASIS_CONFIG> MAP_EPITASIS;

CcbPetBattleLoading::~CcbPetBattleLoading()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTips);
    CC_SAFE_RELEASE_NULL(m_pSpritePaint);
    CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetname);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFPetDes);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetBattleLoading( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetBattleLoading( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetBattleLoading", CcbPetBattleLoadingLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/loding.ccb]", [ccb/loding.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/pet_battle_loading.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CCScene* CcbPetBattleLoading::scene()
{
    CCScene* scene = CCScene::create();
    CCNode* layer = CcbManager::sharedManager()->LoadCcbPetBattleLoading(scene);
    scene->addChild(layer);
    return scene;
}

bool CcbPetBattleLoading::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbPetBattleLoading::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbPetBattleLoading::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
//    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_MAP) {
//        uint8 _bNewStage = StageCtrl::Get()->selectedStage().byStatus;
//        if (_bNewStage) {
//            loadTalkPad();
//        } else {
//            m_vecTalkPad.clear();
//        }
//    }
    
    loadBattleImg();
    schedule(schedule_selector(CcbPetBattleLoading::updateForWait));
}

void CcbPetBattleLoading::onExit()
{
	CCLayer::onExit();
}

void CcbPetBattleLoading::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetBattleLoading::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTips", CCLabelTTF*, this->m_pLabelTTFTips);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePaint", CCSprite*, this->m_pSpritePaint);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetname", CCLabelTTF*, this->m_pLabelTTFPetname);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetDes", CCLabelTTF*, this->m_pLabelTTFPetDes);
	return false;
}

bool CcbPetBattleLoading::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetBattleLoading::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetBattleLoading::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetBattleLoading::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetBattleLoading::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    frameCnt = 0;
    waitFrame = 120;
    std::map<uint16, TipsConfig::STC_CONFIG_TIPS> mapTips = GET_CONFIG_MAP(TipsConfig);
    if (mapTips.size() > 0) {
        uint16 r = rand() % mapTips.size();
        TipsConfig::STC_CONFIG_TIPS* tips = GET_CONFIG_STC(TipsConfig, r);
        if (tips) {
            m_pLabelTTFTips->setString(tips->strText.c_str());
        }
    }
    
    
    std::map<uint16, PetConfig::STC_PET_CONFIG> mapPets = GET_CONFIG_MAP(PetConfig);
    
    while (true) {
        uint16 petId = rand() % mapPets.size() + 1;
        PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, petId);
        if (petCfg && petCfg->byStarLv > 4 && petCfg->byIsTujian) {
            m_pLabelTTFPetname->setString(petCfg->strName.c_str());
            m_pLabelTTFPetDes->setString(petCfg->strDes.c_str());
            
            //原画
            m_pSpritePaint->initWithTexture(CPetCtrl::Get()->GetPetBodyTexture(petId));
            m_pSpritePaint->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.5, 0.95),
                                                                                 CCScaleTo::create(1.5, 1.0),
                                                                                 NULL)));
            //星级
            m_pSpriteLvStar->removeAllChildren();
            m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
            for (int i = 1; i < petCfg->byStarLv; i++) {
                CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());
                m_pSpriteLvStar->setContentSize(star->getContentSize());
                star->setAnchorPoint(ccp(0, 0));
                star->setPosition(ccp(i*(getWidth(star) + 1), 0));
                m_pSpriteLvStar->addChild(star);
            }
            m_pSpriteLvStar->setContentSize(CCSizeMake((getWidth(m_pSpriteLvStar)+1)*petCfg->byStarLv, getHeight(m_pSpriteLvStar)));
            break;
        }
    }
}

void CcbPetBattleLoading::loadBattleImg()
{
    std::vector<std::string> arrPath;
    arrPetPath.clear();
    frameCnt = 0;
    //icon中的原画}
    for (int i = 1; i <= 6; i++) {
        FightPet* pet = FightAI::Get()->getFightPetByBIndex(i);
        if (pet) {
            arrPath.push_back(CPetCtrl::Get()->GetPetBodyPicName(pet->getPetInfo().wPetIndexId));
            arrPath.push_back(CPetCtrl::Get()->GetPetBattleHeadName(pet->getPetInfo().wPetIndexId));
            //动画}
            arrPetPath.push_back(CCString::createWithFormat(PET_SEQUENCE_TEXTURE, pet->getPetInfo().wPetIndexId, SEQ_ACT_STAND)->getCString());
            arrPetPath.push_back(CCString::createWithFormat(PET_SEQUENCE_TEXTURE, pet->getPetInfo().wPetIndexId, SEQ_ACT_ATTACK)->getCString());
            
            
            UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wNormalAttId);
            if (ultCfg) {
                EffectGroupConfig::STC_EFFECT_GROUP_CONFIG* effGroup = GET_CONFIG_STC(EffectGroupConfig, ultCfg->wShowEffectId);
                if (effGroup) {
                    CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
                    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(str->getCString());
                }
            }
            
            ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
            if (ultCfg) {
                EffectGroupConfig::STC_EFFECT_GROUP_CONFIG* effGroup = GET_CONFIG_STC(EffectGroupConfig, ultCfg->wShowEffectId);
                if (effGroup) {
                    CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
                    CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(str->getCString());
                }
            }
            
        }
        
        
    }

    for (int i = 1; i < FightAI::Get()->getAllEnemyTeam().size(); i++) {
        
        FightTeam* team = FightAI::Get()->getAllEnemyTeam()[i];
        FightTeam::MapFightTeam::iterator it = team->GetTeam().begin();
        for (; it != team->GetTeam().end(); it++) {
            FightPet *pet = it->second;
            if (pet) {
                
                //动画}
                arrPetPath.push_back(CCString::createWithFormat(PET_SEQUENCE_TEXTURE, pet->getPetInfo().wPetIndexId, SEQ_ACT_STAND)->getCString());
                arrPetPath.push_back(CCString::createWithFormat(PET_SEQUENCE_TEXTURE, pet->getPetInfo().wPetIndexId, SEQ_ACT_ATTACK)->getCString());
                
                
                UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG* ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wNormalAttId);
                if (ultCfg) {
                    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG* effGroup = GET_CONFIG_STC(EffectGroupConfig, ultCfg->wShowEffectId);
                    if (effGroup) {
                        CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
                        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(str->getCString());
                    }
                }
                
                ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pet->getPetInfo().wSkillId);
                if (ultCfg) {
                    EffectGroupConfig::STC_EFFECT_GROUP_CONFIG* effGroup = GET_CONFIG_STC(EffectGroupConfig, ultCfg->wShowEffectId);
                    if (effGroup) {
                        CCString* str = CCString::createWithFormat(ALT_ARMATURE_PATH, effGroup->strArmEff.c_str(), effGroup->strArmEff.c_str());
                        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(str->getCString());
                    }
                }
            }
        }
        
    }
    
    frameCnt = arrPath.size();
    
    if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS
        || FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_FIGHT
        || FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_RANK
        || FightAI::Get()->getFightType() == E_BATTLE_TYPE_FRIEND) {
        for (int i = 0; i < arrPath.size(); i++) {
            CCLog("%s", arrPath[i].c_str());
            CCTextureCache::sharedTextureCache()->addImageAsync(arrPath[i].c_str(), this, callfuncO_selector(CcbPetBattleLoading::callBack));
        }
        
        return;
    }
    
    std::string fliePath = "ccbresources/12monthdate/battle/battle.plist";
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fliePath.c_str());
    CCDictionary *dict = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
    
    CCDictionary *framesDict = (CCDictionary*)dict->objectForKey("frames");
    CCDictElement* pElement = NULL;
    
    frameCnt += framesDict->count();
    
    CCDICT_FOREACH(framesDict, pElement)
    {
        std::string spriteFrameName =  pElement->getStrKey();
        spriteFrameName = "ccbresources/12monthdate/battle/" + spriteFrameName;
        CCLog("%s", spriteFrameName.c_str());
        CCTextureCache::sharedTextureCache()->addImageAsync(spriteFrameName.c_str(), this, callfuncO_selector(CcbPetBattleLoading::callBack));
    }
    
    for (int i = 0; i < arrPath.size(); i++) {
        CCLog("%s", arrPath[i].c_str());
        CCTextureCache::sharedTextureCache()->addImageAsync(arrPath[i].c_str(), this, callfuncO_selector(CcbPetBattleLoading::callBack));
    }
    
    
}

void CcbPetBattleLoading::callBack(cocos2d::CCObject *object)
{
    frameCnt--;
    if (frameCnt <= 0) {
        schedule(schedule_selector(CcbPetBattleLoading::updateForLoadImg));
        frameCnt = arrPetPath.size();
    }
}

void CcbPetBattleLoading::updateForLoadImg(float time)
{
    
    frameCnt--;
    if (frameCnt <= 0) {
        loadedAll = true;
    }
    
    if (loadedAll) {
//        loadedAll = false;
        unschedule(schedule_selector(CcbPetBattleLoading::updateForLoadImg));
        if (waitFrame < 0) {
            if (CGameSession::GetRole()->GetwGuideTrigger() == 200) {
                CCScene* pScene = PetBattleScene::scene();
                CCDirector::sharedDirector()->replaceScene(pScene);
            }
            else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_FIGHT
                     || FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_RANK
                     || FightAI::Get()->getFightType() == E_BATTLE_TYPE_FRIEND) {
                BackCtrl::ReplaceCurScene(kArenaFightScene);
            }
            else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS){
                BackCtrl::ReplaceCurScene(kWorldBossFightScene);
            }
            else {
                BackCtrl::ReplaceCurScene(kPveBattleScene, kNormalTrans);
            }
        }
        
        return;
    }
    
    CCTextureCache::sharedTextureCache()->addImage(arrPetPath[frameCnt].c_str());
    CCLog("add      %s", arrPetPath[frameCnt].c_str());
}

void CcbPetBattleLoading::updateForWait(float time)
{
    waitFrame--;
    if (waitFrame < 0) {
        unschedule(schedule_selector(CcbPetBattleLoading::updateForWait));
        if (loadedAll) {
            if (CGameSession::GetRole()->GetwGuideTrigger() == 200) {
                CCScene* pScene = PetBattleScene::scene();
                CCDirector::sharedDirector()->replaceScene(pScene);
            }
            else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_FIGHT
                     || FightAI::Get()->getFightType() == E_BATTLE_TYPE_ARENA_RANK
                     || FightAI::Get()->getFightType() == E_BATTLE_TYPE_FRIEND) {
                BackCtrl::ReplaceCurScene(kArenaFightScene);
            }
            else if (FightAI::Get()->getFightType() == E_BATTLE_TYPE_BOSS){
                BackCtrl::ReplaceCurScene(kWorldBossFightScene);
            }
            else{
                BackCtrl::ReplaceCurScene(kPveBattleScene);
            }
        }
        
    }
}

//#pragma mark Static Method
//bool CcbPetBattleLoading::needShowPad()
//{
//    return m_vecTalkPad.size() > 0 ? true : false;
//}
//
//void CcbPetBattleLoading::loadTalkPad()
//{
//    m_vecTalkPad.clear();
//    MAP_EPITASIS m_mapEpit = GET_CONFIG_MAP(EpitasisConfig);
//    MAP_EPITASIS::iterator m_pIter;
//    
//    uint16 _wStageId = StageCtrl::Get()->selectedStage().wStageId;
//    for (m_pIter = m_mapEpit.begin(); m_pIter != m_mapEpit.end(); m_pIter++) {
//        EpitasisConfig::STC_EPITASIS_CONFIG pCfg = m_pIter->second;
//        if (pCfg.wStageId == _wStageId) {
//            m_vecTalkPad.push_back(pCfg);
//        } else if (pCfg.wStageId > _wStageId) {
//            return;
//        }
//    }
//}
//
//EpitasisConfig::STC_EPITASIS_CONFIG CcbPetBattleLoading::talkData(int nIdx)
//{
//    EpitasisConfig::STC_EPITASIS_CONFIG tmp;
//    if (nIdx < m_vecTalkPad.size()) {
//        tmp = m_vecTalkPad[nIdx];
//    }
//    return tmp;
//}
//
//int CcbPetBattleLoading::talkDataCnt() {
//    return m_vecTalkPad.size();
//}

