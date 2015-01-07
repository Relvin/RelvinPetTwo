#include "CcbCaptureLayer.h"
#include "CcbManager.h"
#include "BackCtrl.h"
#include "CaptureScene.h"
#include "CcbCaptureMasterLayer.h"
#include "CcbCaptureFrameLayer.h"
#include "GameSession.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbCaptureLayer* CcbCaptureLayer::m_shared = NULL;

CcbCaptureLayer::~CcbCaptureLayer()
{

	CC_SAFE_RELEASE_NULL(m_pControlButtonSave);
	CC_SAFE_RELEASE_NULL(m_pLayerBottom);
	CC_SAFE_RELEASE_NULL(m_pLayerMsg);
    CC_SAFE_RELEASE_NULL(m_pLayerMaster);

    m_shared = NULL;
}

//-- copy this to CcbManager
/*
//CcbManager.h


//CcbManager.cpp

*/


bool CcbCaptureLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_shared = this;
	return true;
}

CcbCaptureLayer* CcbCaptureLayer::GetCurLayer()
{
    return m_shared;
}

void CcbCaptureLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbCaptureLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    m_pTableMsg->reloadData();
}

void CcbCaptureLayer::onExit()
{
    if (m_pLayerSlave) {
        m_pLayerSlave->removeFromParent();
    }
	CCLayer::onExit();
}

void CcbCaptureLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbCaptureLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBack", CCControlButton*, this->m_pControlButtonBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSave", CCControlButton*, this->m_pControlButtonSave);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBottom", CCLayer*, this->m_pLayerBottom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMsg", CCLayer*, this->m_pLayerMsg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerMaster", CCLayer*, this->m_pLayerMaster);

	return false;
}

bool CcbCaptureLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbCaptureLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbCaptureLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbCaptureLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
//	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonBack", CcbCaptureLayer::onPressControlButtonBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSave", CcbCaptureLayer::onPressControlButtonSave);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbCaptureLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    CCPoint position = m_pLayerMsg->getPosition();
    CCSize size = m_pLayerMsg->getContentSize();
    
    // 初始化消息列表}
    m_pTableMsg = CCTableView::create(this, size);
    m_pTableMsg->setPosition(position);
    m_pTableMsg->setDelegate(this);
    m_pTableMsg->setDirection(kCCScrollViewDirectionVertical);
    m_pTableMsg->setVerticalFillOrder(kCCTableViewFillTopDown);
    this->addChild(m_pTableMsg);
    
    m_pLayerMsg->removeFromParent();
    
    // 判断加载主人界面还是奴隶界面}
    if (CaptureCtrl::masterInfo.dwMasterId != 0) {
        CCPoint masterPos = m_pLayerMaster->getPosition();
        m_pLayerMaster->removeFromParent();
        m_pLayerSlave = dynamic_cast<CcbCaptureMasterLayer*>(CcbManager::sharedManager()->LoadCcbCaptureMasterLayer(this));
        m_pLayerSlave->setPosition(masterPos);
        this->addChild(m_pLayerSlave);
//        m_pLayerMaster->removeFromParent();
    }
    else {
        m_pLayerFrameMaster = dynamic_cast<CcbCaptureFrameLayer*>(m_pLayerMaster);
    }

}

//void CcbCaptureLayer::onPressControlButtonBack(CCObject* pSender, CCControlEvent event)
//{
//	// TODO:
//    BackCtrl::BacktoUpperScene();
//}

void CcbCaptureLayer::onPressControlButtonSave(CCObject* pSender, CCControlEvent event)
{
	// SendResure Request, insert next scene in clientpacket
//    BackCtrl::InsertNextScene(kFriendScene);
    CGameSession::SendRescueFriendReq();
}

#pragma mark CCTableView Delegate
void CcbCaptureLayer::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    return;
}

CCTableViewCell* CcbCaptureLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell* pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCLabelTTF* lblCapture = CCLabelTTF::create(CaptureCtrl::m_vecMsg[idx].c_str(), M_Font, 12);
//        lblCapture->setStrokeForLabelTTF(ccBLACK, 1.0);
        lblCapture->setAnchorPoint(ccp(0, 0));
        lblCapture->setPosition(ccp(2, 2));
        pCell->addChild(lblCapture);
        lblCapture->setTag(123);
    }
    else {
        CCLabelTTF* lblCapture = dynamic_cast<CCLabelTTF*>(pCell->getChildByTag(123));
        lblCapture->setString(CaptureCtrl::m_vecMsg[idx].c_str());
    }
    return pCell;
}

unsigned int CcbCaptureLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return CaptureCtrl::m_vecMsg.size();
}

CCSize CcbCaptureLayer::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(300, 40);
}

#pragma mark Public Method
void CcbCaptureLayer::setCaptureInfo()
{
    m_pTableMsg->reloadData();
    
    // 判断加载主人界面还是奴隶界面}
    if (CaptureCtrl::masterInfo.dwMasterId != 0) {
        // 奴隶界面}
        if (m_pLayerFrameMaster) {
            // 原先为主人，现在被抓住了,需要把主人界面给remove，然后加入奴隶界面}
            CCPoint masterPos = m_pLayerFrameMaster->getPosition();
            m_pLayerFrameMaster->removeFromParent();
            m_pLayerSlave = dynamic_cast<CcbCaptureMasterLayer*>(CcbManager::sharedManager()->LoadCcbCaptureMasterLayer(this));
            m_pLayerSlave->setPosition(masterPos);
            this->addChild(m_pLayerSlave);
        } else {
            // 原先即为奴隶界面，直接更新信息}
            m_pLayerSlave->setMasterInfo();
        }
        
    } else {
        // 主人界面}
        if (m_pLayerSlave) {
            // 原先为奴隶，时间到了，被释放了~哇哈哈，我胡汉三又肥来啦}
            CCPoint slavePos = m_pLayerSlave->getPosition();
            m_pLayerSlave->removeFromParent();
            m_pLayerFrameMaster = dynamic_cast<CcbCaptureFrameLayer*>(CcbManager::sharedManager()->LoadCcbCaptureFrameLayer(this));
            m_pLayerFrameMaster->setPosition(slavePos);
            this->addChild(m_pLayerFrameMaster);
        } else {
            // 原先即为主人，直接更新信息}
            m_pLayerFrameMaster->SetSlaveInfo();
        }
    }
}

#pragma mark Observer Delegate
// 不需要ObserverMsg，因为CaptureFrame使用了Observer方法，在收税时候接受更新消息来更新自身的剩余时间和按钮点击。此处如果也使用Observer，那么也会更新到CaptureFrame的收税更新，有点重复，不需要？此处我有点晕，今天加班太晚了，最近太累了。}


