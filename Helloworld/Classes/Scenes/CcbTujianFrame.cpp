#include "CcbTujianFrame.h"
#include "CcbManager.h"
#include "PetCtrl.h"
#include "ConfigGet.h"
#include "UISupport.h"
#include "CcbPetIcon.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbTujianFrame::~CcbTujianFrame()
{
	CC_SAFE_RELEASE_NULL(m_pSpriteLvStar);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFGetCnt);
	CC_SAFE_RELEASE_NULL(m_pLayerBg);
    CC_SAFE_RELEASE_NULL(m_pScale9SpriteBg);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbTujianFrame( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbTujianFrame( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbTujianFrame", CcbTujianFrameLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/tujian_frame.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbTujianFrame::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbTujianFrame::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等
}

void CcbTujianFrame::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbTujianFrame::onExit()
{
	CCLayer::onExit();
}

void CcbTujianFrame::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbTujianFrame::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteLvStar", CCSprite*, this->m_pSpriteLvStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFGetCnt", CCLabelTTF*, this->m_pLabelTTFGetCnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerBg", CCLayer*, this->m_pLayerBg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteBg", CCScale9Sprite*, this->m_pScale9SpriteBg);

	return false;
}

bool CcbTujianFrame::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbTujianFrame::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbTujianFrame::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbTujianFrame::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbTujianFrame::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制
	// 可以删除，如果不需要
}

uint16 CcbTujianFrame::loadData(std::vector<uint16> arrPetId)
{
    //已开启
    std::set<uint16> setPet =  CPetCtrl::Get()->getPetTujian();
    if(arrPetId.size() == 0)
    {
        return 0;
    }
    
    uint8 starLv = 0;
    uint8 clCnt = 5;
    uint8 rowCnt = arrPetId.size() / clCnt;
    uint16 getCnt = 0;
    if (arrPetId.size() % clCnt > 0) {
        rowCnt++;
    }
    
    float allH = getHeight(this);
    allH += (rowCnt - 1)*65;
    //调整大小和位置
    CCSize sizeA = CCSizeMake(getWidth(this), allH);
    this->setContentSize(sizeA);
    m_pScale9SpriteBg->setPreferredSize(sizeA - CCSizeMake(0, 10));
    m_pScale9SpriteBg->setPositionY(0);
    
    m_pLabelTTFGetCnt->getParent()->setPositionY(allH);
    
    allH = getHeight(m_pLayerBg) + (rowCnt - 1)*65;
    
    m_pLayerBg->setContentSize(CCSizeMake(getWidth(m_pLayerBg), allH));
    m_pLayerBg->setPositionY(0);
    
    for (int i = 0; i < arrPetId.size(); i++) {
        PetConfig::STC_PET_CONFIG* petCfg = GET_CONFIG_STC(PetConfig, arrPetId[i]);
        if (!petCfg) {
            continue;
        }
        
        if (i == 0) {
            starLv = petCfg->byStarLv;
        }
        
        CcbPetIcon *petIcon = dynamic_cast<CcbPetIcon*>(CcbManager::sharedManager()->LoadCcbPetIcon(this));
        petIcon->setPetId(arrPetId[i]);
        petIcon->showName();
        petIcon->setBtnEnable(true);
        petIcon->setAnchorPoint(ccp(0, 1));
        petIcon->setPosition(ccp((i % clCnt) * 60 + 5, allH - (i / clCnt)*65));
        petIcon->setRect(m_clipRect);
        m_pLayerBg->addChild(petIcon);
        
        if (!setPet.count(arrPetId[i])) {
            CCLayerColor *cLayer = CCLayerColor::create(ccc4(0, 0, 0, 255));
            cLayer->setContentSize(petIcon->getContentSize());
            cLayer->setOpacity(150);
            cLayer->setPosition(ccp(getWidth(petIcon)*0.5, getHeight(petIcon)*0.5));
            cLayer->setAnchorPoint(ccp(0.5, 0.5));
            cLayer->ignoreAnchorPointForPosition(false);
            petIcon->addChild(cLayer, 4, 112);
        }
        else{
            getCnt++;
        }
    }
    
    //星级
    m_pSpriteLvStar->removeAllChildren();
    m_pSpriteLvStar->setContentSize(CCSizeMake(m_pSpriteLvStar->getTexture()->getContentSize().width, getHeight(m_pSpriteLvStar)));
    for (int i = 1; i < starLv; i++) {
        CCSprite *star = CCSprite::createWithTexture(m_pSpriteLvStar->getTexture());
        m_pSpriteLvStar->setContentSize(star->getContentSize());
        star->setAnchorPoint(ccp(0, 0));
        star->setPosition(ccp(i*(getWidth(star)), 0));
        m_pSpriteLvStar->addChild(star);
    }
    //进度
    m_pLabelTTFGetCnt->setString(CCString::createWithFormat("%d/%lu", getCnt, arrPetId.size())->getCString());
    
    return getCnt;
}







