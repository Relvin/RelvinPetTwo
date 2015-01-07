#include "CcbRuneIconLayer.h"
//#include "CcbManager.h"
#include "UISupport.h"
#include "Equip.h"
#include "Rune.h"
#include "EquipDataMgr.h"
#include "GameSession.h"
#include "BackCtrl.h"
#include "PetLoadingLayer.h"
#include "SystemMessage.h"
#include "GuideData.h"
#include "PacketDataMgr.h"
#include "ResourceDefine.h"
#include "Rune.h"
#include "ResourceStringClient.h"
#include "FlyTextLayer.h"


CcbRuneIconLayer::~CcbRuneIconLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteRuneIcon);
	CC_SAFE_RELEASE_NULL(m_pSpriteRuneFrame);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbRuneIconLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbRuneIconLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbRuneIconLayer", CcbRuneIconLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/equip_rune_icon.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbRuneIconLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbRuneIconLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbRuneIconLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbRuneIconLayer::onExit()
{
	CCLayer::onExit();
}

void CcbRuneIconLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbRuneIconLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRuneIcon", CCSprite*, this->m_pSpriteRuneIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteRuneFrame", CCSprite*, this->m_pSpriteRuneFrame);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	return false;
}

bool CcbRuneIconLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbRuneIconLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbRuneIconLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbRuneIconLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbRuneIconLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    //CCScale9Sprite *sSprite = CCScale9Sprite::create("ccbresources/12monthdate/button/button_icon_1.png");
    //CCScale9Sprite *sSpriteSelected = CCScale9Sprite::create("ccbresources/12monthdate/button/button_icon_2.png");
    CCSize size = m_pSpriteRuneIcon->getContentSize();
    size.width *= m_pSpriteRuneIcon->getScaleX();
    size.height *= m_pSpriteRuneIcon->getScaleY();
    m_pScrollButtonSelect = CCScrollButton::createTransWithHightLight();//(sSprite);
    //m_pControlButtonSelect->setContentSize(size);
    //m_pScrollButtonSelect->setBackgroundSpriteForState(sSpriteSelected, CCControlStateSelected);
    m_pScrollButtonSelect->setPreferredSize(size);
    m_pScrollButtonSelect->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbRuneIconLayer::onPressScrollButtonSelect), CCControlEventTouchUpInside);
    
    m_pScrollButtonSelect->setPosition(ccp(getWidth(m_pSpriteRuneFrame) * 0.5, getHeight(m_pSpriteRuneFrame)*0.5));
    //m_pScrollButtonSelect->setAnchorPoint(ccp(0.5, 0.5));
    //m_pScrollButtonSelect->setClipRect(CCRectMake(0, 0, getWidth(m_pSpriteIcon), getHeight(m_pSpriteIcon)));
    
    m_pSpriteRuneFrame->addChild(m_pScrollButtonSelect, 1, 99);
    
    
    CreateRuneData();
}

void CcbRuneIconLayer::CreateRuneData()
{

    const CRune* pRune = g_PacketDataMgr->GetRuneInfoByKeyID(m_localTag);
    if (pRune)
    {
        CCTexture2D* pTexture = CCTextureCache::sharedTextureCache()->addImage(g_PacketDataMgr->GetRuneIconByIndex(pRune->GetIndex()).c_str());
        if (pTexture)
        {
            m_pSpriteRuneIcon->setTexture(pTexture);
        } 
        m_pLabelTTFName->setString(pRune->GetConfigData().strName.c_str());
    }
}

void CcbRuneIconLayer::onPressScrollButtonSelect(CCObject* pSender, CCControlEvent event)
{
//    GuideData::GetInstance()->addGuideofEnum(GuideData::E_SYS_GUIDE_HERO_9, NULL);
//    GuideData::GetInstance()->connectToServer();
    //CCLOG("%d", getLocalTag());
    const CEquip* pEquip = g_PacketDataMgr->GetEquipInfoByKeyID(g_EquipData->GetChosenEquipKeyID());
    if (pEquip)
    {
        uint32 dwEquipID = g_EquipData->GetChosenEquipKeyID();
        uint32 dwRuneID = getLocalTag();
        if (pEquip->GetRune1() == 0)
        {
            //镶嵌符文1}
            if (pEquip->GetRune2() != 0)
            {
                uint8 byRuneType1 = g_PacketDataMgr->GetRuneInfoByKeyID(dwRuneID)->GetConfigData().byEffectType1;
                uint8 byRuneType2 = g_PacketDataMgr->GetRuneInfoByKeyID(pEquip->GetRune2())->GetConfigData().byEffectType1;
                if (byRuneType1 == byRuneType2)
                {
                    FlyTextLayer::showTips( GET_STR(Str_the_same_rune));
                    CCLOG("已经镶嵌过同种类型的符文");
                    return;
                }
            }
            
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendRuneToEquip(dwEquipID, 0, dwRuneID);
        }
        else if (pEquip->GetRunesCnt() == 2 && pEquip->GetRune2() == 0)
        {
            //镶嵌符文2}
            if (pEquip->GetRune1() != 0)
            {
                uint8 byRuneType1 = g_PacketDataMgr->GetRuneInfoByKeyID(pEquip->GetRune1())->GetConfigData().byEffectType1;
                uint8 byRuneType2 = g_PacketDataMgr->GetRuneInfoByKeyID(dwRuneID)->GetConfigData().byEffectType1;
                if (byRuneType1 == byRuneType2)
                {
                    FlyTextLayer::showTips(GET_STR(Str_the_same_rune));
                    CCLOG("已经镶嵌过同种类型的符文");
                    return;                    
                }
            }
            
            PetLoadingLayer::sharedLayer()->WaitForPacket();
            CGameSession::SendRuneToEquip(dwEquipID, 1, dwRuneID);
        }
        else if (pEquip->GetRunesCnt() == 1)
        {
//            CCLOG("2号位未解锁");
        }
        else
        {
//            CCLOG("不能再镶嵌了");
        }
    }
}



