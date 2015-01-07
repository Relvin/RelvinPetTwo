/**
 * CcbVipFrameLayer.cpp
 * Create by GenerateCppCodeFromCCBFile.lua
 * All right received
 * Author: Relvin
 * Date: 2014-10-23 16:16:11
 */


#include "CcbVipFrameLayer.h"
#include "ConfigGet.h"
#include "Role.h"
#include "GameSession.h"
#include "PetLoadingLayer.h"
#include "ShopDataMgr.h"
#include "MusicCtrl.h"
#include "UISupport.h"
#include "ResourceStringConverter.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbVipFrameLayer::CcbVipFrameLayer()
: m_pSpritePermission (NULL)
, m_pLabelTTFText (NULL)
, m_pLabelTTFRecharge (NULL)
{
    
}

CcbVipFrameLayer::~CcbVipFrameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpritePermission);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFText);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFRecharge);

}

#pragma mark -Initialize-

bool CcbVipFrameLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    
	return true;
}

// Inhert MemberVariableAssigner
bool CcbVipFrameLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpritePermission", CCSprite*, this->m_pSpritePermission);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFText", CCLabelTTF*, this->m_pLabelTTFText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFRecharge", CCLabelTTF*, this->m_pLabelTTFRecharge);

	return false;
}

bool CcbVipFrameLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
	return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbVipFrameLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbVipFrameLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbVipFrameLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbVipFrameLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    
}

#pragma mark -onEnter-
void CcbVipFrameLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void CcbVipFrameLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
}

#pragma mark -onExit-
void CcbVipFrameLayer::onExit()
{
    CCLayer::onExit();
}

void CcbVipFrameLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Self Functions -
void CcbVipFrameLayer::setFrameInfoByIndex(int index)
{
    char szTemp[256] = "";
    VipShowConfig::STC_VIP_SHOW_CONFIG* pConfig = GET_CONFIG_STC(VipShowConfig, index);
    
    if (pConfig)
    {
        sprintf(szTemp, "%d", pConfig->dwRechargeVal);
        this->m_pLabelTTFRecharge->setString(szTemp);
        
        char szText[1024] = "";
        std::vector<std::string> vecDes;
        ResourceStringConverter::StrSplit(pConfig->strDes, "_", vecDes);
        for (std::vector<std::string>::iterator pIter = vecDes.begin(); pIter != vecDes.end(); pIter++) {
            snprintf(szTemp, 256, "%s\n", (*pIter).c_str());
            strcat(szText, szTemp);
        }
        this->m_pLabelTTFText->setString(szText);
    }
    
    CRole* pRole = CGameSession::GetRole();
    if (pRole)
    {
        if (pRole->GetbyVipLv() == index)
        {
            this->m_pSpritePermission->setVisible(true);
        }
        else
        {
            this->m_pSpritePermission->setVisible(false);
        }
    }
}





