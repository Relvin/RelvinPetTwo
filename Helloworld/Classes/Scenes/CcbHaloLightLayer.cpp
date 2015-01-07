/**
 * halo_light.cpp
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-09-10 16:55:02
 */


#include "CcbHaloLightLayer.h"
#include "PetCtrl.h"
#include "Pet.h"


USING_NS_CC;
USING_NS_CC_EXT;

CcbHaloLightLayer::CcbHaloLightLayer()
: m_pLayerbg (NULL)
{
    
}

CcbHaloLightLayer::~CcbHaloLightLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerbg);

}

#pragma mark - Initialize -
bool CcbHaloLightLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
	return true;
}

// Inhert MemberVariableAssigner
bool CcbHaloLightLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerbg", CCLayer*, this->m_pLayerbg);

	return false;
}

bool CcbHaloLightLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbHaloLightLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbHaloLightLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbHaloLightLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbHaloLightLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

#pragma mark - onEnter -
void CcbHaloLightLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void CcbHaloLightLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

#pragma mark - onExit -
void CcbHaloLightLayer::onExit()
{
    CCLayer::onExit();
}

void CcbHaloLightLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Self Function -
void CcbHaloLightLayer::setShowInfoByIndex(uint16 wIndex)
{
    CCSprite *pSprite = (CCSprite *)m_pLayerbg->getChildByTag(0);
    
    pSprite->setDisplayFrame(CPetCtrl::Get()->GetHaloLightTextureByPet(wIndex));
    
    ccColor3B color = CPetCtrl::Get()->GetHaloLightColrByPetIdx(wIndex);
    for (int i = 0; i < 3; i++) {
        pSprite = (CCSprite *)m_pLayerbg->getChildByTag( i + 1);
        pSprite->setColor(color);
    }
}






