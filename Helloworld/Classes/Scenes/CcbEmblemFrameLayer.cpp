#include "CcbEmblemFrameLayer.h"
//#include "CcbManager.h"
#include "EmblemDataMgr.h"
#include "UISupport.h"
#include "ConfigGet.h"
#include "EnumDefines.h"
#include "Pet.h"
#include "PetCtrl.h"
#include "CcbEmblemInfoLayer.h"
#include "BackCtrl.h"
#include "PetCtrl.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"
#include "ResourceStringClient.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "GuideBtnPos.h"
#include "GuideData.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbEmblemFrameLayer::~CcbEmblemFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
	CC_SAFE_RELEASE_NULL(m_pSpriteArrow1);
	CC_SAFE_RELEASE_NULL(m_pLayerPet);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName);
	CC_SAFE_RELEASE_NULL(m_pSpritePetStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLevel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri3);
	CC_SAFE_RELEASE_NULL(m_pControlButtonStrengthen);
    CC_SAFE_RELEASE_NULL(m_pLayerIcon);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_3);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemFrameLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemFrameLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemFrameLayer", CcbEmblemFrameLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbEmblemFrameLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEmblemFrameLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    if (CGameSession::GetRole()->GetwRoleLv() < GUIDE_LV) {
        GuideBtnPos::Get()->addNodeWorldPos(m_pControlButtonStrengthen, GuideBtnPos::E_BADGE_ON, true);
    }
}

void CcbEmblemFrameLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemFrameLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteArrow1", CCSprite*, this->m_pSpriteArrow1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerPet", CcbPetIcon*, this->m_pLayerPet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName", CCLabelTTF*, this->m_pLabelTTFPetName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePetStar", CCSprite*, this->m_pSpritePetStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLevel", CCLabelTTF*, this->m_pLabelTTFLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri1", CCLabelTTF*, this->m_pLabelTTFAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri2", CCLabelTTF*, this->m_pLabelTTFAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri3", CCLabelTTF*, this->m_pLabelTTFAttri3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStrengthen", CCScrollButton*, this->m_pControlButtonStrengthen);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_1", CCLabelTTF*, this->m_pLabelTTFAttr_1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_2", CCLabelTTF*, this->m_pLabelTTFAttr_2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_3", CCLabelTTF*, this->m_pLabelTTFAttr_3);

	return false;
}

bool CcbEmblemFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonStrengthen", CcbEmblemFrameLayer::onPressControlButtonStrengthen);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwEmblemObjId = 0;
    fEmStarW = getWidth(m_pSpriteStar)+1;
    fPetStarW = getWidth(m_pSpritePetStar)+1;
    
}

void CcbEmblemFrameLayer::onPressControlButtonStrengthen(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if(g_EmblemData->getEmbInType() == E_EMB_IN_TYPE_WEAR){
        
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetShowPetObjId());
        if (pet &&
            (pet->GetdwEmblemId1() == m_dwEmblemObjId || pet->GetdwEmblemId2() == m_dwEmblemObjId)) {
            //卸下
            CGameSession::SendEmblemTakeOff(m_dwEmblemObjId);
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            return;
        }
        //装备
        CGameSession::SendEmblemWear(CPetCtrl::Get()->GetShowPetObjId(), m_dwEmblemObjId);
        PetLoadingLayer::sharedLayer()->WaitForPacket();
        return;
    }
    
    g_EmblemData->setEnhEmbObjId(m_dwEmblemObjId);
    g_EmblemData->clearSelected();
    BackCtrl::InsertNextScene(kEmblemEnhSenec);
}

void CcbEmblemFrameLayer::onPressControlButtonEmbInfo(CCObject* pSender, CCControlEvent event)
{
    CcbEmblemInfoLayer::showEmblemInfo(m_dwEmblemObjId);
}


void CcbEmblemFrameLayer::setEmblemObjId(uint32 dwEmbObjId)
{
    m_dwEmblemObjId = dwEmbObjId;
    loadData();
}

void CcbEmblemFrameLayer::loadData()
{
    CEmblem* emb = g_EmblemData->getEmblemByObjId(m_dwEmblemObjId);
    if (!emb) {
        return;
    }
    
    EmblemConfig::STC_EMBLEM_CONFIG* embCfg = GET_CONFIG_STC(EmblemConfig, emb->getdwIndexId());
    if (!embCfg) {
        return;
    }
    
    if(g_EmblemData->getEmbInType() == E_EMB_IN_TYPE_WEAR){
        CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetShowPetObjId());
        if (pet){
            if(pet->GetdwEmblemId1() == m_dwEmblemObjId || pet->GetdwEmblemId2() == m_dwEmblemObjId) {
                //卸下
                m_pControlButtonStrengthen->setTitleForState(CCString::create(GET_STR(Str_Discharge)), CCControlStateNormal);
            }
            else{
                //装备
                m_pControlButtonStrengthen->setTitleForState(CCString::create(GET_STR(Str_equip)), CCControlStateNormal);
            }
            
        }
        
    }
    
    //徽章Icon}
    m_pLayerIcon->loadObjData(emb->getdwEmlemObjId(), E_UNITE_TYPE_EMBLEM);
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
        star->setPosition(ccp(i * fEmStarW, 0));
        m_pSpriteStar->addChild(star);
    }
    m_pSpriteStar->setContentSize(CCSizeMake(embCfg->byStarLv*fEmStarW, getHeight(m_pSpriteStar)));
    //徽章等级}
    CCString* str = CCString::createWithFormat("%s%d", SB_Lv, emb->getbyLv());
    m_pLabelTTFLevel->setString(str->getCString());
    //徽章属性}
    std::vector<CCLabelTTF* >arrLblAttr;
    arrLblAttr.push_back(m_pLabelTTFAttri1);
    arrLblAttr.push_back(m_pLabelTTFAttri2);
    arrLblAttr.push_back(m_pLabelTTFAttri3);
    
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
    
    //宠物}
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(emb->getdwPetObjId());
    m_pLayerPet->setdwEmlemObjId(m_dwEmblemObjId);
    if (!pet) {
        m_pLayerPet->getParent()->setVisible(false);
    }
    else
    {
        m_pLayerPet->getParent()->setVisible(true);

        m_pLabelTTFPetName->setVisible(true);
        m_pSpritePetStar->setVisible(true);
        //宠物icon}
        m_pLayerPet->setPetObjId(pet->GetObjId());
        //宠物名}
        PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, pet->GetwIndex());
        m_pLabelTTFPetName->setString(petCfg->strName.c_str());
        //宠物星级}
        m_pSpritePetStar->removeAllChildren();
        CCTexture2D *td = m_pSpritePetStar->getTexture();
        for (int i = 1; i < pet->GetbyStarLv(); i++) {
            CCSprite *star = CCSprite::createWithTexture(td);
            star->setAnchorPoint(ccp(0, 0));
            star->setPosition(ccp(i * fPetStarW, 0));
            m_pSpritePetStar->addChild(star);
        }
        m_pSpritePetStar->setContentSize(CCSizeMake(pet->GetbyStarLv() * fPetStarW, getHeight(m_pSpritePetStar)));
        //专属标志显示}
        m_pSpriteArrow1->setVisible(g_EmblemData->checkExcPet(emb->getdwIndexId(), pet->GetObjId()));
    }
    m_pLayerPet->setBtnEnable(false);
}

void CcbEmblemFrameLayer::setRect(CCRect rect)
{
    m_pLayerIcon->setClipRect(rect);
    m_pControlButtonStrengthen->setClipRect(rect);
}



