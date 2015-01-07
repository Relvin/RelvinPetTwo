#include "CcbEmblemEnhanceLayer.h"
#include "CcbManager.h"
#include "CcbEmblemIconLayer.h"
#include "UISupport.h"
#include "EmblemDataMgr.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "EffectLayer.h"
#include "BackCtrl.h"
#include "FlyTextLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;




EmblemEnhanceScene::~EmblemEnhanceScene()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
}

CCScene* EmblemEnhanceScene::scene()
{
    CCScene* pScene = CCScene::create();
    EmblemEnhanceScene* pLayer = EmblemEnhanceScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool EmblemEnhanceScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addChild(CcbManager::sharedManager()->LoadCcbEmblemEnhanceLayer(this));
    return true;
}

void EmblemEnhanceScene::onEnter()
{
    CCLayer::onEnter();
    //    m_pLabelTTFName->setStrokeForLabelTTF(ccBLACK, 1.0);
    m_pLabelTTFName->setString(GET_STR(Str_emblem_enhance));
}

void EmblemEnhanceScene::onExit()
{
    CCLayer::onExit();
}

void EmblemEnhanceScene::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void EmblemEnhanceScene::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

bool EmblemEnhanceScene::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName );
	return false;
}

bool EmblemEnhanceScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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




CcbEmblemEnhanceLayer::~CcbEmblemEnhanceLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    CC_SAFE_RELEASE_NULL(m_pSpriteBar);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextLevel);
    CC_SAFE_RELEASE_NULL(m_pSpriteArrow1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurLevel);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri1);
    CC_SAFE_RELEASE_NULL(m_pSpriteArrow2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri2);
    CC_SAFE_RELEASE_NULL(m_pSpriteArrow3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFCurAttri3);
    CC_SAFE_RELEASE_NULL(m_pSpriteArrow4);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNextAttri3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_3);
    CC_SAFE_RELEASE_NULL(m_pSpriteEmBg);
    CC_SAFE_RELEASE_NULL(m_pLayerElem5);
    CC_SAFE_RELEASE_NULL(m_pControlButtonElem5);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_5);
    CC_SAFE_RELEASE_NULL(m_pLayerElem4);
    CC_SAFE_RELEASE_NULL(m_pControlButtonElem4);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_4);
    CC_SAFE_RELEASE_NULL(m_pLayerElem3);
    CC_SAFE_RELEASE_NULL(m_pControlButtonElem3);
//    CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv3);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_3);
    CC_SAFE_RELEASE_NULL(m_pLayerElem2);
    CC_SAFE_RELEASE_NULL(m_pControlButtonElem2);
//    CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv2);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_2);
    CC_SAFE_RELEASE_NULL(m_pLayerElem1);
    CC_SAFE_RELEASE_NULL(m_pControlButtonElem1);
//    CC_SAFE_RELEASE_NULL(m_pLabelTTFElemLv1);
    CC_SAFE_RELEASE_NULL(m_pSprite_plus_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFGetExp);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFNeedExp);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAutoAdd);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStrengthen);
    
    m_curScene = NULL;

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemEnhanceLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemEnhanceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemEnhanceLayer", CcbEmblemEnhanceLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/bottombtn.ccb]", [ccb/bottombtn.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/header_back2.ccb]", [ccb/header_back2.ccb]Loader::loader() );
pLoaderLib->registerCCNodeLoader( "[ccb/mainhead.ccb]", [ccb/mainhead.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_strengthen.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

CcbEmblemEnhanceLayer* CcbEmblemEnhanceLayer::m_curScene = NULL;

bool CcbEmblemEnhanceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_curScene = this;
	return true;
}

void CcbEmblemEnhanceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbEmblemEnhanceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
        
}

void CcbEmblemEnhanceLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemEnhanceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemEnhanceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBar", CCSprite*, this->m_pSpriteBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextLevel", CCLabelTTF*, this->m_pLabelTTFNextLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrow1", CCSprite*, this->m_pSpriteArrow1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurLevel", CCLabelTTF*, this->m_pLabelTTFCurLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri1", CCLabelTTF*, this->m_pLabelTTFCurAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrow2", CCSprite*, this->m_pSpriteArrow2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri1", CCLabelTTF*, this->m_pLabelTTFNextAttri1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri2", CCLabelTTF*, this->m_pLabelTTFCurAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrow3", CCSprite*, this->m_pSpriteArrow3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri2", CCLabelTTF*, this->m_pLabelTTFNextAttri2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFCurAttri3", CCLabelTTF*, this->m_pLabelTTFCurAttri3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrow4", CCSprite*, this->m_pSpriteArrow4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNextAttri3", CCLabelTTF*, this->m_pLabelTTFNextAttri3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_1", CCLabelTTF*, this->m_pLabelTTFAttr_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_2", CCLabelTTF*, this->m_pLabelTTFAttr_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_3", CCLabelTTF*, this->m_pLabelTTFAttr_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteEmBg", CCSprite*, this->m_pSpriteEmBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem5", CcbItemIconLayer*, this->m_pLayerElem5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem5", CCControlButton*, this->m_pControlButtonElem5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_5", CCSprite*, this->m_pSprite_plus_5);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem4", CcbItemIconLayer*, this->m_pLayerElem4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem4", CCControlButton*, this->m_pControlButtonElem4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_4", CCSprite*, this->m_pSprite_plus_4);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem3", CcbItemIconLayer*, this->m_pLayerElem3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem3", CCControlButton*, this->m_pControlButtonElem3);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv3", CCLabelTTF*, this->m_pLabelTTFElemLv3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_3", CCSprite*, this->m_pSprite_plus_3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem2", CcbItemIconLayer*, this->m_pLayerElem2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem2", CCControlButton*, this->m_pControlButtonElem2);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv2", CCLabelTTF*, this->m_pLabelTTFElemLv2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_2", CCSprite*, this->m_pSprite_plus_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerElem1", CcbItemIconLayer*, this->m_pLayerElem1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonElem1", CCControlButton*, this->m_pControlButtonElem1);
//    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFElemLv1", CCLabelTTF*, this->m_pLabelTTFElemLv1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite_plus_1", CCSprite*, this->m_pSprite_plus_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetExp", CCLabelTTF*, this->m_pLabelTTFGetExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNeedExp", CCLabelTTF*, this->m_pLabelTTFNeedExp);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAutoAdd", CCControlButton*, this->m_pControlButtonAutoAdd);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrengthen", CCControlButton*, this->m_pControlButtonStrengthen);
	return false;
}

bool CcbEmblemEnhanceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemEnhanceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemEnhanceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemEnhanceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonElem", CcbEmblemEnhanceLayer::onPressControlButtonElem);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonAutoAdd", CcbEmblemEnhanceLayer::onPressControlButtonAutoAdd);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrengthen", CcbEmblemEnhanceLayer::onPressControlButtonStrengthen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemEnhanceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    expBarWidth = getWidth(m_pSpriteBar);

    fEmStarW = getWidth(m_pSpriteStar)+1;
    
    
    CEmblem* emb = g_EmblemData->getEmblemByObjId(g_EmblemData->getEnhEmbObjId());
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
    m_pLayerIcon->setBtnEnable(false);
    //徽章名}
    m_pLabelTTFName->setString(embCfg->strName.c_str());
    //徽章星级}
    m_pSpriteStar->removeAllChildren();
    CCTexture2D *td = m_pSpriteStar->getTexture();
    for (int i = 1; i < embCfg->byStarLv; i++) {
        CCSprite *star = CCSprite::createWithTexture(td);
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*fEmStarW, 0));
        m_pSpriteStar->addChild(star);
    }
    m_pSpriteStar->setContentSize(CCSizeMake(embCfg->byStarLv*fEmStarW, getHeight(m_pSpriteStar)));
    

    m_pLabelTTFNextLevel->noStroke();
}



void CcbEmblemEnhanceLayer::onPressControlButtonStrengthen(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CGameSession::SendEmblemEat(g_EmblemData->getEnhEmbObjId(), g_EmblemData->getSelected());
    PetLoadingLayer::sharedLayer()->WaitForPacket();
}


void CcbEmblemEnhanceLayer::onPressControlButtonElem(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    BackCtrl::InsertNextScene(kEmblemChooseScene);
}

void CcbEmblemEnhanceLayer::onPressControlButtonAutoAdd(CCObject* pSender, CCControlEvent event)
{
    // TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    g_EmblemData->selectElemAuto();
    if (g_EmblemData->getSelected().size() == 0) {
        FlyTextLayer::showTips("当前没有低级徽章");
        return;
    }
    loadElem();
}

void CcbEmblemEnhanceLayer::loadData()
{
    CEmblem* emb = g_EmblemData->getEmblemByObjId(g_EmblemData->getEnhEmbObjId());
    if (!emb) {
        return;
    }
    
    EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
    if (!embCfg) {
        return;
    }
    //徽章等级}
    CCString* str = CCString::createWithFormat("%s%d", SB_Lv, emb->getbyLv());
    m_pLabelTTFCurLevel->setString(str->getCString());
    m_pLabelTTFCurLevel->noStroke();
    //徽章属性}
    std::vector<CCLabelTTF* >arrLblAttr;
    arrLblAttr.push_back(m_pLabelTTFCurAttri1);
    arrLblAttr.push_back(m_pLabelTTFCurAttri2);
    arrLblAttr.push_back(m_pLabelTTFCurAttri3);
    
    std::vector<CCLabelTTF* >arrTextAttr;
    arrTextAttr.push_back(m_pLabelTTFAttr_1);
    arrTextAttr.push_back(m_pLabelTTFAttr_2);
    arrTextAttr.push_back(m_pLabelTTFAttr_3);
    
    for (int i = 0; i < 3; i ++) {
        if (embCfg->byAttribute[i] == 0) {
            arrLblAttr[i]->setVisible(false);
            arrTextAttr[i]->setVisible(false);
            continue;
        }
        
        float attvalue = embCfg->dwAttrValue[i] + (emb->getbyLv() - 1)*embCfg->dwAttrChg[i];
        if (embCfg->byAttrType[i] == 2) { //万分率}
            attvalue /= 100;
            str->initWithFormat("+%.1f%%", attvalue);
        }
        else
        {
            str->initWithFormat("+%d", (uint32)attvalue);
        }
        arrLblAttr[i]->setVisible(true);
        arrLblAttr[i]->setString(str->getCString());
        arrTextAttr[i]->setVisible(true);
        arrTextAttr[i]->setString(g_PacketDataMgr->getAttrText(embCfg->byAttribute[i]).c_str());
    }
    
    //经验}
    float expFatio = (float)embCfg->dwExpFatio / 100;
    
    uint16 curLv = emb->getbyLv();
    ExpConfig::STC_EXP_CONFIG* expCfg = GET_CONFIG_STC(ExpConfig, curLv);
    str->initWithFormat("%d", (int)(expCfg->dwEmblemExp * expFatio) - emb->getdwExp());
    m_pLabelTTFNeedExp->setString(str->getCString());
    loadElem();
}

void CcbEmblemEnhanceLayer::loadElem()
{
    if (g_EmblemData->getSelected().size() == 0) {
        m_pControlButtonStrengthen->setEnabled(false);
    }
    else{
        m_pControlButtonStrengthen->setEnabled(true);
    }
    uint32 allExp = 0;
    int cnt = 0;
    std::vector<CcbItemIconLayer*> arrElemIcon;
    arrElemIcon.push_back(m_pLayerElem1);
    arrElemIcon.push_back(m_pLayerElem2);
    arrElemIcon.push_back(m_pLayerElem3);
    arrElemIcon.push_back(m_pLayerElem4);
    arrElemIcon.push_back(m_pLayerElem5);
    std::vector<CCSprite*> arrPlus;
    arrPlus.push_back(m_pSprite_plus_1);
    arrPlus.push_back(m_pSprite_plus_2);
    arrPlus.push_back(m_pSprite_plus_3);
    arrPlus.push_back(m_pSprite_plus_4);
    arrPlus.push_back(m_pSprite_plus_5);
    
    for (int i = 0 ; i < g_EmblemData->getSelected().size(); i++) {
        uint32 embId = g_EmblemData->getSelected()[i];
        CEmblem *emb = g_EmblemData->getEmblemByObjId(embId);
        if (!emb) {
            continue;
        }
        EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
        if (!embCfg) {
            continue;
        }
        
        //计算可获得经验}
        allExp += embCfg->dwEatExp * emb->getbyLv();
        
        //强化素材
        arrElemIcon[cnt]->loadIndexData(emb->getdwIndexId());
        arrElemIcon[cnt]->setBtnEnable(false);
        arrElemIcon[cnt]->showName();
        arrElemIcon[cnt]->showLv(emb->getbyLv());
        arrPlus[cnt]->setVisible(false);
        cnt++;
    }
    
    for (; cnt < arrPlus.size(); cnt++) {
        arrElemIcon[cnt]->loadIndexData(0);
        arrElemIcon[cnt]->setBtnEnable(false);
        arrPlus[cnt]->setVisible(true);
        arrPlus[cnt]->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.5),
                                                                           CCFadeIn::create(1.5),
                                                                           NULL)));
    }
    
    CCString* str = CCString::createWithFormat("%d", allExp);
    m_pLabelTTFGetExp->setString(str->getCString());
    
    CEmblem* emb = g_EmblemData->getEmblemByObjId(g_EmblemData->getEnhEmbObjId());
    EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
    
    float expFatio = (float)embCfg->dwExpFatio / 100;
    
    uint16 curLv = emb->getbyLv();
    ExpConfig::STC_EXP_CONFIG* expCfg = GET_CONFIG_STC(ExpConfig, curLv);
    if (!expCfg || allExp + emb->getdwExp() < expCfg->dwEmblemExp*expFatio) {
        //如果没升级 不显示升级后属性}
        //经验}
        m_pSpriteBar->setTextureRect(CCRectMake(0, 0, (float)(emb->getdwExp() + allExp) / (expCfg->dwEmblemExp * expFatio) * expBarWidth, getHeight(m_pSpriteBar)));
        
        m_pLabelTTFNextLevel->setVisible(false);
        m_pLabelTTFNextAttri1->setVisible(false);
        m_pLabelTTFNextAttri2->setVisible(false);
        m_pLabelTTFNextAttri3->setVisible(false);
        m_pSpriteArrow1->setVisible(false);
        m_pSpriteArrow2->setVisible(false);
        m_pSpriteArrow3->setVisible(false);
        m_pSpriteArrow4->setVisible(false);
        
        return;
    }
    
    //计算可以升到的级数}
    ExpConfig::STC_EXP_CONFIG* lvMax = GET_CONFIG_STC(ExpConfig, 0);
    uint32 maxLv = 0;
    if (lvMax) {
        maxLv = lvMax->dwEmblemExp;
    }
    allExp -= expCfg->dwEmblemExp * expFatio - emb->getdwExp();
    while (true) {
        curLv++;
        if (curLv >= maxLv) {
            //升到满级}
            curLv = maxLv;
            break;
        }
        
        expCfg = GET_CONFIG_STC(ExpConfig, curLv);
        if (!expCfg) {
            CCLOG("expconfig lv = %d not found~~~~~~~", curLv);
            break;
        }
        
        if (allExp < expCfg->dwEmblemExp * expFatio) {
            break;
        }
        allExp -= expCfg->dwEmblemExp * expFatio;
    }
    
    //显示升级强化后属性}
    
    //徽章等级}
    str->initWithFormat("%s%d", SB_Lv, curLv);
    m_pLabelTTFNextLevel->setVisible(true);
    m_pLabelTTFNextLevel->setString(str->getCString());
    //徽章属性}
    std::vector<CCLabelTTF* >arrLblAttr;
    arrLblAttr.push_back(m_pLabelTTFNextAttri1);
    arrLblAttr.push_back(m_pLabelTTFNextAttri2);
    arrLblAttr.push_back(m_pLabelTTFNextAttri3);
    
    std::vector<CCSprite* >arrSpAttr;
    m_pSpriteArrow1->setVisible(true);
    arrSpAttr.push_back(m_pSpriteArrow2);
    arrSpAttr.push_back(m_pSpriteArrow3);
    arrSpAttr.push_back(m_pSpriteArrow4);
    
    std::vector<uint32 >arrPerValue;
    arrPerValue.push_back(embCfg->dwAttrValue[0] + (emb->getbyLv() - 1)*embCfg->dwAttrChg[0]);
    arrPerValue.push_back(embCfg->dwAttrValue[1] + (emb->getbyLv() - 1)*embCfg->dwAttrChg[1]);
    arrPerValue.push_back(embCfg->dwAttrValue[2] + (emb->getbyLv() - 1)*embCfg->dwAttrChg[2]);
    
    for (int i = 0; i < 3; i ++) {
        if (embCfg->byAttribute[i] == 0) {
            arrLblAttr[i]->setVisible(false);
            arrSpAttr[i]->setVisible(false);
            continue;
        }
        
        float attvalue = embCfg->dwAttrValue[i] + (curLv - 1)*embCfg->dwAttrChg[i];
        if (attvalue == arrPerValue[i]) {
            continue;
        }
        
        if (embCfg->byAttrType[i] == 2) { //万分率}
            attvalue /= 100;
            str->initWithFormat("+%.1f%%", attvalue);
        }
        else
        {
            str->initWithFormat("+%d", (int)attvalue);
        }
        arrLblAttr[i]->setVisible(true);
        arrSpAttr[i]->setVisible(true);
        arrLblAttr[i]->setString(str->getCString());
        
    }
    
    //经验}
    float bar = (float)allExp / (expCfg->dwEmblemExp * expFatio);
    if (curLv == maxLv) {
        bar = 1;
    }
    m_pSpriteBar->setTextureRect(CCRectMake(0, 0, bar * expBarWidth, getHeight(m_pSpriteBar)));
    
    
}

//    /** 徽章升级结果}
//     [uint16] wError
//     [uint32] dwAddExp
//     */
//
void CcbEmblemEnhanceLayer::handlerEnhanceResult(WorldPacket& packet)
{
    if (m_pLayerIcon->getParent()->getChildByTag(1212)) {
        m_pLayerIcon->getParent()->removeChildByTag(1212);
    }
    
    EffectLayer* upEff = EffectLayer::create(E_ANI_EFFECT_EQUIP_EFF, 1, 0.06);
    upEff->setPosition(getCenter(m_pLayerIcon) + ccp(6, -8));
    upEff->setScale(0.6);
    upEff->setAnchorPoint(ccp(0.5, 0.5));
    upEff->ignoreAnchorPointForPosition(false);
    
    upEff->setTag(1212);
//    upEff->setDelegate(this);
    m_pLayerIcon->getParent()->addChild(upEff, 3);
    upEff->onRun();
    
    g_EmblemData->clearSelected();
    loadData();
}

