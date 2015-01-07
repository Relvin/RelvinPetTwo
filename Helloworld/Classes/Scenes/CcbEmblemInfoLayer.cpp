#include "CcbEmblemInfoLayer.h"
#include "CcbManager.h"
#include "Emblem.h"
#include "CcbExcPetFrameLayer.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "PacketDataMgr.h"
#include "MusicCtrl.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbEmblemInfoLayer::~CcbEmblemInfoLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerBadgeBg);
	CC_SAFE_RELEASE_NULL(m_pLayerIcon);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pSpriteStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFLevel);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri1);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri2);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAttri3);
	CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_1);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_2);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFAttr_3);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEmblemInfoLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEmblemInfoLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEmblemInfoLayer", CcbEmblemInfoLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/badge_wear.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEmblemInfoLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbEmblemInfoLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbEmblemInfoLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_pTableView->reloadData();
}

void CcbEmblemInfoLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEmblemInfoLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEmblemInfoLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBadgeBg", CCLayer*, this->m_pLayerBadgeBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerIcon", CcbItemIconLayer*, this->m_pLayerIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar", CCSprite*, this->m_pSpriteStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFLevel", CCLabelTTF*, this->m_pLabelTTFLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri1", CCLabelTTF*, this->m_pLabelTTFAttri1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri2", CCLabelTTF*, this->m_pLabelTTFAttri2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttri3", CCLabelTTF*, this->m_pLabelTTFAttri3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_1", CCLabelTTF*, this->m_pLabelTTFAttr_1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_2", CCLabelTTF*, this->m_pLabelTTFAttr_2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAttr_3", CCLabelTTF*, this->m_pLabelTTFAttr_3);
	return false;
}

bool CcbEmblemInfoLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEmblemInfoLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEmblemInfoLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEmblemInfoLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbEmblemInfoLayer::onPressControlButtonClose);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEmblemInfoLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_dwEmbObjId = 0;
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 6);
    
    m_pTableView = CCTableView::create(this, m_pLayerBadgeBg->getContentSize());
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 10);
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    //    table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setBounceable(true);
    m_pLayerBadgeBg->addChild(m_pTableView);
}



void CcbEmblemInfoLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
	// TODO:
    removeFromParent();
}

void CcbEmblemInfoLayer::showEmblemInfo(uint32 dwEmbObjId)
{
    CcbEmblemInfoLayer* node = dynamic_cast<CcbEmblemInfoLayer*>(CcbManager::sharedManager()->LoadCcbEmblemInfoLayer());
    if (node) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        node->setPosition(winSize.width*0.5, winSize.height* 0.5);
        node->setAnchorPoint(ccp(0.5, 0.5));
        node->ignoreAnchorPointForPosition(false);
        CCDirector::sharedDirector()->getRunningScene()->addChild(node, 100);
        node->setEmblemObjId(dwEmbObjId);
    }
}

void CcbEmblemInfoLayer::setEmblemObjId(uint32 dwEmbObjId)
{
    m_dwEmbObjId = dwEmbObjId;
    loadData();
}

void CcbEmblemInfoLayer::loadData()
{    
    CEmblem* emb = g_EmblemData->getEmblemByObjId(m_dwEmbObjId);
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
        star->setPosition(ccp(i*(getWidth(m_pSpriteStar)+1), 0));
        m_pSpriteStar->addChild(star);
    }
    m_pSpriteStar->setContentSize(CCSizeMake(embCfg->byStarLv*(getWidth(m_pSpriteStar)+1), getHeight(m_pSpriteStar)));
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
    
    //专属宠}
    arrPet.clear();
    int len = 0;
    
    GET_ARRAY_LEN(embCfg->wExcPetIndex, len);
    for (int i = 0; i < len; i++) {
        if (embCfg->wExcPetIndex[i] == 0) {
            continue;
        }
        STC_EXC_PET excPet;
        excPet.petIndex = embCfg->wExcPetIndex[i];
        excPet.byEmbType = embCfg->byExcAttr[i];
        excPet.dwEmbValue = embCfg->dwExcAttrValue[i];
        arrPet.push_back(excPet);
    }
    
    m_pTableView->reloadData();
}

//tableView相关}
CCTableViewCell* CcbEmblemInfoLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = cell = new CCTableViewCell();
        cell->autorelease();
        CCNode* node = CcbManager::sharedManager()->LoadCcbExcPetFrameLayer();
        node->setPosition(getWidth(m_pLayerBadgeBg)*0.5, 0);
        node->setAnchorPoint(ccp(0.5, 0));
        node->ignoreAnchorPointForPosition(false);
        node->setTag(11);
        cell->addChild(node);
    }
    CcbExcPetFrameLayer* node = dynamic_cast<CcbExcPetFrameLayer*>(cell->getChildByTag(11));
    node->loadData(arrPet[idx]);
    
    return cell;
}
unsigned int CcbEmblemInfoLayer::numberOfCellsInTableView(CCTableView *table)
{
    return arrPet.size();
}
CCSize CcbEmblemInfoLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerBadgeBg), 65);
}

bool CcbEmblemInfoLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CcbEmblemInfoLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);
}





