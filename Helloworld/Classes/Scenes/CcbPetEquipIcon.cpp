#include "CcbPetEquipIcon.h"
//#include "CcbManager.h"
#include "EquipDataMgr.h"
#include "PacketDataMgr.h"
#include "ConfigGet.h"
#include "BackCtrl.h"
#include "PetCtrl.h"
#include "CFuseDadaMgr.h"
#include "MusicCtrl.h"
#include "GuideData.h"
#include "FlyTextLayer.h"
#include "UISupport.h"
USING_NS_CC;
USING_NS_CC_EXT;

CcbPetEquipIcon::~CcbPetEquipIcon()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteBg);
	CC_SAFE_RELEASE_NULL(m_pSpriteIcon);
	CC_SAFE_RELEASE_NULL(m_pControlButtonEquip);
	CC_SAFE_RELEASE_NULL(m_pSpriteIconFrame);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFItemEvoLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLv);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
    CC_SAFE_RELEASE_NULL(m_pSpriteNumBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNum);
    CC_SAFE_RELEASE_NULL(m_pLayerColorUnEnable);
    CC_SAFE_RELEASE_NULL(m_pSpriteHas);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbPetEquipIcon( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbPetEquipIcon( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbPetEquipIcon", CcbPetEquipIconLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/petshow_equip_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbPetEquipIcon::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbPetEquipIcon::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
//    loadData();
}

void CcbPetEquipIcon::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbPetEquipIcon::onExit()
{
	CCLayer::onExit();
}

void CcbPetEquipIcon::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbPetEquipIcon::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIcon", CCSprite*, this->m_pSpriteIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonEquip", CCScrollButton*, this->m_pControlButtonEquip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteIconFrame", CCSprite*, this->m_pSpriteIconFrame);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemName", CCLabelTTF*, this->m_pLabelTTFItemName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFItemEvoLv", CCLabelTTF*, this->m_pLabelTTFItemEvoLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLv", CCLabelTTF*, this->m_pLabelTTFLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNum", CCLabelTTF*, this->m_pLabelTTFNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteNumBg", CCSprite*, this->m_pSpriteNumBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerColorUnEnable", CCLayerColor*, this->m_pLayerColorUnEnable);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteHas", CCSprite*, this->m_pSpriteHas);

	return false;
}

bool CcbPetEquipIcon::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbPetEquipIcon::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbPetEquipIcon::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbPetEquipIcon::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonEquip", CcbPetEquipIcon::onPressControlButtonEquip);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbPetEquipIcon::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwEquipObjId = 0;
    m_isEnable = true;
    
    m_pLabelTTFNum->getParent()->setVisible(false);
    m_pLayerColorUnEnable->setVisible(false);
    m_pSpriteHas->setVisible(false);
    
}



void CcbPetEquipIcon::onPressControlButtonEquip(CCObject* pSender, CCControlEvent event)
{
    if (CGameSession::GetRole()->GetwGuideTrigger() < GuideData::E_GUIDE_END_TRIGGER) {
        FlyTextLayer::showTips("引导未完成");
        return;
    }
    
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_open_pack));
    
    uint16 syslockId = GuideData::GetInstance()->checkBtnLock(GuideData::E_GUIDE_UNLOCK_BTN_UNIT_EQUIP);
    SystemDebLockingConfig::STC_SYSTEM_DEB_LOCKING_CONFIHG* cfg = GET_CONFIG_STC(SystemDebLockingConfig, syslockId);
    if (cfg) {
        FlyTextLayer::showTips(cfg->strDescShow.c_str());
        return;
    }
    
    if (BackCtrl::GetCurSceneIdx() == kPetFuse) {
        g_FuseDada->setFuseTab(E_FUSE_TAB_EQUIP);
        BackCtrl::InsertNextScene(kFuseList);   // 融合}
        return;
    }
    else if (BackCtrl::GetCurSceneIdx() == kFuseList){
        //显示选号}
        if (m_pLabelTTFNum->getParent()->isVisible()) {
            m_pLabelTTFNum->getParent()->setVisible(false);
            g_FuseDada->delSelected(m_dwEquipObjId);
        }
        else
        {
            g_FuseDada->addSelected(m_dwEquipObjId);
        }
        return;
    }
    
    g_EquipData->SetDressEquipPart(m_byEquipType);
    g_EquipData->SetDressEquipKeyID(m_dwEquipObjId);
//    g_EquipData->SetEquipListShowMode(E_SHOW_LIST_PET);
    BackCtrl::InsertNextScene(kEquipIntegrationScene);     // 装备一览}
}

void CcbPetEquipIcon::setEquipObjId(uint32 dwObjId)
{
    m_dwEquipObjId = dwObjId;
    
    loadData();
}

void CcbPetEquipIcon::loadData()
{
    m_pSpriteHas->setVisible(false);
    m_pLabelTTFItemName->setVisible(false);
//    m_pLabelTTFLv->setVisible(false);
    hideLv();
    m_pSpriteStar->setVisible(false);
//    m_pLabelTTFItemEvoLv->setVisible(false);
    hideEvoLv();
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/universal/quality.plist");
    
    if (m_dwEquipObjId == 0)
    {
        string str = "";
        switch (m_byEquipType) {
            case E_EQUIP_PART_WEAPON:
                str = "ccbresources/12monthdate/petshow/pic_equipleft1_back.png";
                break;
            case E_EQUIP_PART_CLOTHES:
                str = "ccbresources/12monthdate/petshow/pic_equipright1_back.png";
                break;
            case E_EQUIP_PART_HELMET:
                str = "ccbresources/12monthdate/petshow/pic_equipleft2_back.png";
                break;
            case E_EQUIP_PART_NECKLACE:
                str = "ccbresources/12monthdate/petshow/pic_equipright2_back.png";
                break;
                
            default:
                break;
        }
        
        m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(str.c_str()));
        m_pSpriteIconFrame->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("quality_0.png"));
        return;
    }
    
    const CEquip* equip = g_PacketDataMgr->GetEquipInfoByKeyID(m_dwEquipObjId);
    if (!equip)
    {
        return;
    }
    
    m_pSpriteIcon->setVisible(true);
    
    if (BackCtrl::GetCurSceneIdx() == kPetFuse) {
        
    }
    else{
//        m_pLabelTTFLv->setVisible(true);
        showStarLv(equip->GetConfigData().byStar);
        setLv(equip->GetLevel());
        if (equip->getEvoLv() == 0) {
            hideEvoLv();
        }
        else{
            m_pLabelTTFItemEvoLv->setVisible(true);
            m_pLabelTTFItemEvoLv->setString(CCString::createWithFormat("+%d", equip->getEvoLv())->getCString());
        }
    }
    
    m_pControlButtonEquip->setVisible(m_isEnable);
//    m_pLabelTTFItemName->setVisible(m_isEnable);
    showName(true);
    
    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(equip->GetIndex()).c_str()));
    
    m_pLabelTTFItemName->setString(equip->GetConfigData().strName.c_str());
    
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(equip->GetIndex());
    
    m_pLabelTTFItemName->setColor(g_PacketDataMgr->getQualityColor(quality));

    m_pSpriteIconFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    
    m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
    
    
    //融合用}
    setNum(0);
    if (BackCtrl::GetCurSceneIdx() == kFuseList) {
        std::vector<uint32> arrSelectedPet = g_FuseDada->getSelected();
        if (arrSelectedPet.size() > 0) {
            bool unEnable = g_FuseDada->isSelectedFull();
            
            int size = arrSelectedPet.size();
            for (int i = 0; i < size; i++) {
                uint32 objId = arrSelectedPet[i];
                if (objId != m_dwEquipObjId) {
                    continue;
                }
                setNum(i+1);
                break;
            }
            setEnable(!unEnable);
        }
    }
}
void CcbPetEquipIcon::setEnable(bool enable)
{
//    if (m_isEnable != enable) {
        m_isEnable = enable;
        if (BackCtrl::GetCurSceneIdx() != kFuseList) {
            m_pControlButtonEquip->setVisible(m_isEnable);
            return;
        }
        else{
        //有编号显示的不置灰}
            if (m_pLabelTTFNum->getParent()->isVisible()) {
                m_pLayerColorUnEnable->setVisible(false);
                return;
            }
            m_pLayerColorUnEnable->setVisible(!m_isEnable);
        }
//    }
}

void CcbPetEquipIcon::showName(bool isShow)
{
    m_pLabelTTFItemName->setVisible(isShow);
}

void CcbPetEquipIcon::setIndex(uint32 index)
{
    m_pSpriteHas->setVisible(false);
    m_pLabelTTFItemName->setVisible(false);
//    m_pLabelTTFLv->setVisible(false);
    hideLv();
    m_pSpriteStar->setVisible(false);
//    m_pLabelTTFItemEvoLv->setVisible(false);
    hideEvoLv();
    
    EquipNewConfig::STC_EQUIP_CONFIG* cfg = GET_CONFIG_STC(EquipNewConfig, index);
    if (!cfg) {
        m_pSpriteIcon->setVisible(false);
        showName(false);
        return;
    }
    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(index).c_str()));
    
    m_pLabelTTFItemName->setString(cfg->strName.c_str());
    showName(true);
    
    
//    m_pLabelTTFLv->setVisible(true);
    showStarLv(cfg->byStar);
//    setLv(equip->GetLevel());
//    m_pLabelTTFItemEvoLv->setVisible(false);
    hideEvoLv();
    uint8 evolv = (index / 100) % 10;
    if (evolv > 0) {
        m_pLabelTTFItemEvoLv->getParent()->setVisible(true);
        m_pLabelTTFItemEvoLv->setString(CCString::createWithFormat("+%d", evolv)->getCString());
    }
    

    m_pSpriteIcon->setTexture(CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetObjectIconByIndex(index).c_str()));
        
    uint8 quality = g_PacketDataMgr->getObjectQualityByIndex(index);
    m_pLabelTTFItemName->setColor(g_PacketDataMgr->getQualityColor(quality));
    m_pSpriteIconFrame->setDisplayFrame(g_PacketDataMgr->getQualityFrameSF(quality));
    
    m_pSpriteBg->setDisplayFrame(g_PacketDataMgr->getQualityBgSF(quality));
}
void CcbPetEquipIcon::setLv(uint8 lv)
{
    if (lv == 0) {
        m_pLabelTTFLv->getParent()->setVisible(false);
        return;
    }
    m_pLabelTTFLv->getParent()->setVisible(true);
    m_pLabelTTFLv->setString(CCString::createWithFormat("%s%d",SB_Lv, lv)->getCString());
}

void CcbPetEquipIcon::hideEvoLv()
{
    if (m_pLabelTTFItemEvoLv) {
        m_pLabelTTFItemEvoLv->getParent()->setVisible(false);
    }
}

void CcbPetEquipIcon::hideLv()
{
    if (m_pLabelTTFLv) {
        m_pLabelTTFLv->getParent()->setVisible(false);
    }
}

//显示星级}
void CcbPetEquipIcon::showStarLv(uint8 lv)
{
    if (lv == 0) {
        hideStarLv();
        return;
    }
    if (m_pSpriteStar) {
        
        //星级
//        m_pSpriteStar->setScale(1.0);
        m_pSpriteStar->removeAllChildren();
        m_pSpriteStar->setContentSize(CCSizeMake(m_pSpriteStar->getTexture()->getContentSize().width, getHeight(m_pSpriteStar)));
        for (int i = 1; i < lv; i++) {
            CCSprite *star = CCSprite::createWithTexture(m_pSpriteStar->getTexture());// ("ccbresources/12monthdate/pet/pic_lvstar.png");
            m_pSpriteStar->setContentSize(star->getContentSize());
            star->setAnchorPoint(ccp(0, 0));
            star->setPosition(ccp(i*getWidth(star)*0.65, 0));
            m_pSpriteStar->addChild(star);
        }
        m_pSpriteStar->setContentSize(CCSizeMake((getWidth(m_pSpriteStar)*0.65)*(lv-1)+ getWidth(m_pSpriteStar), getHeight(m_pSpriteStar)));
//        m_pSpriteStar->setScale(0.75);
        
        m_pSpriteStar->setVisible(true);
//        m_pSpriteStar->setDisplayFrame(g_PacketDataMgr->getStarSF(lv));
    }
}
//隐藏星级}
void CcbPetEquipIcon::hideStarLv()
{
    if (m_pSpriteStar) {
        m_pSpriteStar->setVisible(false);
    }
}

void CcbPetEquipIcon::setNum(uint8 byNum)
{
    if (byNum == 0) {
        m_pLabelTTFNum->getParent()->setVisible(false);
        return;
    }
    CCString *str = CCString::createWithFormat("%d", byNum);
    m_pLabelTTFNum->setString(str->getCString());
    m_pLabelTTFNum->getParent()->setVisible(true);
}

void CcbPetEquipIcon::setClipRect(CCRect rect)
{
    m_pControlButtonEquip->setClipRect(rect);
}


void CcbPetEquipIcon::checkHasCanUse(uint8 pos)
{
    m_pSpriteHas->setVisible(g_PacketDataMgr->checkHasCanUseEquip(pos, m_dwEquipObjId));
}