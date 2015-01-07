#include "CcbChallengeNode2Layer.h"
#include "UISupport.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
#include "ConfigData.h"
#include "CcbActivityTipLayer.h"
#include "ChallengeCtrl.h"
#include "CcbManager.h"
#include "StageScene.h"
#include "GameSession.h"
#include "Role.h"
#include "FlyTextLayer.h"
#include "ResourceStringClient.h"
#include "MapScene.h"
#include "GuideData.h"
#include "PetLoadingLayer.h"
#include "ResourcePic.h"
#include "BackCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark - Constructor -
CcbChallengeNode2Layer::CcbChallengeNode2Layer()
: m_pSpriteBg(NULL)
, m_pLayerDrops(NULL)
, m_pSpriteLock(NULL)

, m_wMapId(0)
, m_wRoleLvLimit(0)
, m_strMapName("")
, m_pScrollButtonNode(NULL)
, m_pTableView(NULL)
{

}

CcbChallengeNode2Layer::~CcbChallengeNode2Layer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteBg);
	CC_SAFE_RELEASE_NULL(m_pLayerDrops);
	CC_SAFE_RELEASE_NULL(m_pSpriteLock);

}

#pragma mark - Initialication -
bool CcbChallengeNode2Layer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChallengeNode2Layer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteBg", CCSprite*, this->m_pSpriteBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerDrops", CCLayer*, this->m_pLayerDrops);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLock", CCSprite*, this->m_pSpriteLock);

	return false;
}

bool CcbChallengeNode2Layer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChallengeNode2Layer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChallengeNode2Layer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChallengeNode2Layer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

#pragma mark - NodeLoaded -
void CcbChallengeNode2Layer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    m_pScrollButtonNode = CCScrollButton::create();
    m_pScrollButtonNode->setZoomOnTouchDown(false);
    m_pScrollButtonNode->setPreferredSize(m_pSpriteLock->getContentSize());
    //    m_pScrollButtonNode->setClipRect(CCRectMake(0, 0, 320, 440));
    m_pScrollButtonNode->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbChallengeNode2Layer::onPressControlButtonNode), CCControlEventTouchUpInside);
    m_pScrollButtonNode->setPosition(ccp(getWidth(m_pSpriteLock)*0.5, getHeight(m_pSpriteLock)*0.5));
    addChild(m_pScrollButtonNode);
    m_pScrollButtonNode->setTouchPriority(kCCMenuHandlerPriority - 1);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ccbresources/12monthdate/active/active_challenge.plist");
    
    m_pTableView = CCTableView::create(this, m_pLayerDrops->getContentSize());
    m_pTableView->setDirection(kCCScrollViewDirectionHorizontal);
    m_pLayerDrops->addChild(m_pTableView);
}

#pragma mark - onEnter & onExit -
void CcbChallengeNode2Layer::onEnter()
{
    CCLayer::onEnter();
    m_pTableView->reloadData();
}

void CcbChallengeNode2Layer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

void CcbChallengeNode2Layer::onExit()
{
    CCLayer::onExit();
}

void CcbChallengeNode2Layer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functinos -
void CcbChallengeNode2Layer::onPressControlButtonNode(cocos2d::CCObject *pObject, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_next));
    //增加锁定提示框}
    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, m_wMapId);
    if (m_pSpriteLock->isVisible()) {
        if (pConfig) {
            std::string strTip;
            StageCtrl::STC_SPE_MAP *stcMap = StageCtrl::Get()->getActivityMapByMapId(m_wMapId);
            if (stcMap->byIsOpen == 0) {
                strTip = pConfig->wLimitDes;
                CcbActivityTipLayer* tip = dynamic_cast<CcbActivityTipLayer*>(CcbManager::sharedManager()->LoadCcbActivityTipLayer());
                tip->loadData(strTip);
                tip->setPosition(ccp(0,0));
                CCDirector::sharedDirector()->getRunningScene()->addChild(tip, 999);
            }
            else
            {
                strTip = CCString::createWithFormat(GET_STR(Str_ji_lv_open), pConfig->wLimitLv)->getCString();
                FlyTextLayer::showTips(strTip);
            }
        }
        return;
    }
    
    MapCtrl::nSelectedMapId = m_wMapId;
    CCScrollButton* pBtn = dynamic_cast<CCScrollButton*>(pObject);
    if (!pBtn ) {
        return;
        
    }
    StageCtrl::Get()->setSelectedActivityMapIdx(pBtn->getTag());
    StageCtrl::Get()->setCurMapPointName(m_strMapName);
    
    ChallengeCtrl::Get()->setCellIndex(-1);
    ChallengeCtrl::Get()->setChallengeType(pBtn->getTag());
    CGameSession::SendSpecialStageInfo(pBtn->getTag());
    
}

#pragma mark - TableView Functions -
CCTableViewCell* CcbChallengeNode2Layer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell;
        pCell->autorelease();
        
    }
    return pCell;
}

unsigned int CcbChallengeNode2Layer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 0;
}

CCSize CcbChallengeNode2Layer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(0, 0);
}


#pragma mark - Self Functions -
void CcbChallengeNode2Layer::setChallengeNodeInfoByIndex(uint16 wIndex)
{
    StageCtrl::STC_SPE_MAP* stcMap = StageCtrl::Get()->getActivityMapByMapId(wIndex);
    if (!stcMap) {
        return;
    }
    
    m_pScrollButtonNode->setTag(stcMap->wMapId);
    m_wMapId = stcMap->wMapId;
    SpecialMapConfig::STC_SPECIAL_MAP_CONFIG *pConfig = GET_CONFIG_STC(SpecialMapConfig, m_wMapId);
    if (!pConfig) {
        CCLog("Cannot get Special Map config.");
        return;
    }
    
    m_strMapName = pConfig->strMapName;
    m_wRoleLvLimit = pConfig->wLimitLv;
    
    if (stcMap->byIsOpen && m_wRoleLvLimit <= CGameSession::GetRole()->GetwRoleLv()) {
        m_pSpriteLock->setVisible(false);
    } else {
        m_pSpriteLock->setVisible(true);
    }
    // 换图}
    CCString* picPath = CCString::createWithFormat(GET_PIC(Pic_activity_map), pConfig->wPicId);
    CCSpriteFrame *pSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(picPath->getCString());
    if (pSpriteFrame) {
        m_pSpriteBg->setDisplayFrame(pSpriteFrame);
        
    } else {
//        CCMessageBox(CCString::createWithFormat("%s Not Find!",picPath->getCString())->getCString(), "Error");
    }
    
}

void CcbChallengeNode2Layer::setClipRect(CCRect rect)
{
    m_pScrollButtonNode->setClipRect(rect);
}


