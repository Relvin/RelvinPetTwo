#include "CcbTeamPositionLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbTeamPositionLayer::~CcbTeamPositionLayer()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteOn);
	CC_SAFE_RELEASE_NULL(m_pSpriteOff);
    m_pSprites->removeAllObjects();
    CC_SAFE_RELEASE_NULL(m_pSprites);
}

bool CcbTeamPositionLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_pSprites = new CCArray();
    m_pSprites->init();
	return true;
}

void CcbTeamPositionLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbTeamPositionLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
    
    m_curPos = 0;
    
    texLight = m_pSpriteOn->getTexture();
    texDark  = m_pSpriteOff->getTexture();
    
    m_pSpriteOn->removeFromParent();
    m_pSpriteOff->removeFromParent();
}

void CcbTeamPositionLayer::onExit()
{
	CCLayer::onExit();
}

void CcbTeamPositionLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTeamPositionLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteOn", CCSprite*, this->m_pSpriteOn);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteOff", CCSprite*, this->m_pSpriteOff);

	return false;
}

bool CcbTeamPositionLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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

//// Inhert CCNodeLoaderListener
//void CcbTeamPositionLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
//{
//	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
//	// 可以删除，如果不需要}
//    
//}

#pragma mark Public Method
void CcbTeamPositionLayer::SetCnt(int num)
{
    if (num < 0) {
        CCMessageBox("Num Init Error", "Error");
    }
    
    m_pMaxSize = num;
    bool bOdd = num & 1;
    float fInitPos;
    if (!bOdd) {
        // 偶数}
        fInitPos = 10.0 - (num >> 1) * 10;
    } else {
        // 奇数}
        fInitPos = 5.0 - (num >> 1) * 10;
    }
    
    CCLog("init position:%f", fInitPos);
    
    for (int i = 0; i < num; ++i) {
        CCSprite* pSprite;
        if (i == m_curPos) {
            pSprite = CCSprite::createWithTexture(texLight);
        } else {
            pSprite = CCSprite::createWithTexture(texDark);
        }
        pSprite->setAnchorPoint(ccp(0, 0));
        pSprite->setPosition(ccp(fInitPos+10*i, 0));
        addChild(pSprite);
        m_pSprites->addObject(pSprite);
    }
}

void CcbTeamPositionLayer::LightUpPos(int idx)
{

    if (idx >= m_pMaxSize) {
        CCLog("\n\n\n\n\nWaring!!!!!, idx exceeds the max size");
        return;
    }
    
    CCSprite* tmp1 = dynamic_cast<CCSprite*>(m_pSprites->objectAtIndex(m_curPos));
    tmp1->setTexture(texDark);

    CCSprite* tmp2 = dynamic_cast<CCSprite*>(m_pSprites->objectAtIndex(idx));
    tmp2->setTexture(texLight);
    m_curPos = idx;
}







