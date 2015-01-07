#include "CcbMapPointLayer.h"
//#include "CcbManager.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "CCScrollButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbMapPointLayer::~CcbMapPointLayer()
{
	CC_SAFE_RELEASE_NULL(m_pControlButtonStage);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar1);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar2);
    CC_SAFE_RELEASE_NULL(m_pSpriteStar3);
    CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
    
    CC_SAFE_RELEASE_NULL(m_pLayerNew);
    CC_SAFE_RELEASE_NULL(m_pLayerClear);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbMapPointLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbMapPointLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbMapPointLayer", CcbMapPointLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/map_point.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbMapPointLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbMapPointLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbMapPointLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbMapPointLayer::onExit()
{
	CCLayer::onExit();
}

void CcbMapPointLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbMapPointLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStage", CCScrollButton*, this->m_pControlButtonStage);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar1", CCSprite*, this->m_pSpriteStar1);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar2", CCSprite*, this->m_pSpriteStar2);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteStar3", CCSprite*, this->m_pSpriteStar3);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerNew", CCLayer*, this->m_pLayerNew);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerClear", CCLayer*, this->m_pLayerClear);
	return false;
}

bool CcbMapPointLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	// 可以删除这个方法，如果删除后没有问题的话。
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
SEL_CallFuncN CcbMapPointLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbMapPointLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbMapPointLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbMapPointLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
    m_pSpriteStars[0] = m_pSpriteStar1;
    m_pSpriteStars[1] = m_pSpriteStar2;
    m_pSpriteStars[2] = m_pSpriteStar3;
    
    m_pLayerClear->setVisible(false);
    m_pLayerNew->setVisible(false);
}


void CcbMapPointLayer::setMapPoint(uint8 byStatus, std::string strName, std::string strDes, std::string strTm, int nTag) {
    m_byStatus = byStatus;
    m_strName = strName;
    m_strDes = strDes;
    m_strTm = strTm;
    m_nTag = nTag;
    
    m_pLabelTTFName->setString(strName.c_str());
    m_pControlButtonStage->setTag(nTag);
//    m_pControlButtonStage->setTouchPriority(-1);
}

void CcbMapPointLayer::setMapNotOpen() {
    for (int i = 0; i < 3; i++) {
        m_pSpriteStars[i]->setVisible(false);
    }
    CCParticleSystemQuad* pEff = CCParticleSystemQuad::create("ccbresources/12monthdate/mission/unlockmap.plist");
    pEff->setPosition(m_pControlButtonStage->getPosition());
    m_pLayerNew->setVisible(true);
    addChild(pEff);
}

void CcbMapPointLayer::setMapStarCnt(int _cnt) {
    for (int i = _cnt; i < 3; i++) {
        CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(GET_PIC(Pic_small_empty_star));
        m_pSpriteStars[i]->setTexture(pTex);
    }
}

void CcbMapPointLayer::setMapClear() {
    m_pLayerNew->setVisible(false);
    m_pLayerClear->setVisible(true);
}

void CcbMapPointLayer::setMapNew() {
    m_pLayerClear->setVisible(false);
    m_pLayerNew->setVisible(true);
}


