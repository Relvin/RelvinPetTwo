#include "CcbEvoInfoListLayer.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "Pet.h"
#include "ConfigGet.h"
#include "CcbEvoInfoFrameLayer.h"
#include "MusicCtrl.h"
#include "UISupport.h"
USING_NS_CC;
USING_NS_CC_EXT;

CcbEvoInfoListLayer::~CcbEvoInfoListLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerList);
	CC_SAFE_RELEASE_NULL(m_pControlButtonBack);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFEvoLv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbEvoInfoListLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbEvoInfoListLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbEvoInfoListLayer", CcbEvoInfoListLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/evo_list.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbEvoInfoListLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
	return true;
}

void CcbEvoInfoListLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    loadData();
}

void CcbEvoInfoListLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbEvoInfoListLayer::onExit()
{
	CCLayer::onExit();
}

void CcbEvoInfoListLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbEvoInfoListLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerList", CCLayer*, this->m_pLayerList);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFEvoLv", CCLabelTTF*, this->m_pLabelTTFEvoLv);

	return false;
}

bool CcbEvoInfoListLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbEvoInfoListLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbEvoInfoListLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbEvoInfoListLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbEvoInfoListLayer::onPressControlButtonBack);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbEvoInfoListLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_pControlButtonBack->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pTableView = CCTableView::create(this, m_pLayerList->getContentSize());
    m_pTableView->setPosition(CCPointZero);
    m_pTableView->setAnchorPoint(CCPointZero);
    m_pTableView->setTouchPriority(kCCMenuHandlerPriority - 22);
    m_pTableView->setDirection(kCCScrollViewDirectionVertical);
    m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_pTableView->setBounceable(true);
    m_pLayerList->addChild(m_pTableView);
}



void CcbEvoInfoListLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->setVisible(false);
}

void CcbEvoInfoListLayer::loadData()
{
    CPet* pet = CPetCtrl::Get()->GetPetByObjId(CPetCtrl::Get()->GetEvolvePet());
    //当前进阶等级}
    m_pLabelTTFEvoLv->setString(CCString::createWithFormat("%d", pet->GetbyEvolveLv())->getCString());
    //进阶信息}
    arrEvolveId.clear();
    
    uint32 nextId = GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv());
    
    std::vector<uint16> arrId;
    
    while (true) {
        if (nextId % 100 == 0) {
            break;
        }
        nextId --;
        EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, nextId);
        if (cfg) {
            arrId.push_back(nextId);
        }
        else
        {
            nextId = nextId - 100;
            EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, nextId);
            if (cfg) {
                arrId.push_back(nextId);
            }
            else
            {
                break;
            }
        }
    }
    
    for (int i = 0; i < arrId.size(); i++) {
        arrEvolveId.push_back(arrId[arrId.size() - i - 1]);
    }
    
    nextId = GET_EVOLVE_ID(pet->GetwIndex(), pet->GetbyEvolveLv());
    int index = -1;
    while (true) {
        EvolveConfig::STC_EVOLVE_CONFIG* cfg = GET_CONFIG_STC(EvolveConfig, nextId);
        if (cfg) {
            arrEvolveId.push_back(nextId);
            nextId = cfg->wNextId;
            if (cfg->byLv == pet->GetbyEvolveLv() + 1) {
                index = arrEvolveId.size() - 1;
            }
        }
        else
        {
            break;
        }
    }
    if (index == -1) {
        index = arrEvolveId.size() - 1;
    }
    
    
    m_pTableView->reloadData();
    
    m_pTableView->scrollToIndex(index - 1);
}

//tableView相关}
CCTableViewCell* CcbEvoInfoListLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell* cell = table->dequeueCell();
    if (!cell) {
        cell = cell = new CCTableViewCell();
        cell->autorelease();
        CCNode* node = CcbManager::sharedManager()->LoadCcbEvoInfoFrameLayer();
        node->setAnchorPoint(ccp(0.5, 0));
        node->setPosition(getWidth(m_pLayerList)*0.5, 0);
        node->ignoreAnchorPointForPosition(false);
        node->setTag(1);
        cell->addChild(node);
    }
    CcbEvoInfoFrameLayer* node = dynamic_cast<CcbEvoInfoFrameLayer*>(cell->getChildByTag(1));
    node->loadData(arrEvolveId[idx + 1]);
    
    
    return cell;
}
unsigned int CcbEvoInfoListLayer::numberOfCellsInTableView(CCTableView *table)
{
    return arrEvolveId.size() - 1;
}
CCSize CcbEvoInfoListLayer::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(getWidth(m_pLayerList), 65);
}


bool CcbEvoInfoListLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return isVisible();
}

void CcbEvoInfoListLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 21, true);
}


