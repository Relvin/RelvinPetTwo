#include "CcbChoosePetLayer.h"
#include "CcbManager.h"
#include "GlobalData.h"
#include "ResourcePic.h"
#include "ConfigGet.h"
#include "MusicCtrl.h"
#include "ResourceStringClient.h"
#include "SystemMessage.h"
#include "ReRichText.h"
#include "UISupport.h"
#include "HexagonLayer.h"
#include "PetLoadingLayer.h"
#include "GameSession.h"
#include "GuideData.h"
#include "ResourceDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define ANIMATIONTIME 0.08f

#define MAX_LENGTH 7
#define CHOOSEPETSCNT   4

static int _calcCharCountUTF(const char * pszText)
{
    int n = 0;
    char ch = 0;
    while ((ch = *pszText))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++pszText;
    }
    return n;
}

CCScene* ChoosePetScene::scene()
{
    CCScene* pScene = CCScene::create();
    ChoosePetScene* pLayer = ChoosePetScene::create();
    pScene->addChild(pLayer);
    return pScene;
}

bool ChoosePetScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    GlobalData::bFromPetChoose = true;
    addChild(CcbManager::sharedManager()->LoadCcbChoosePetLayer(this));
    return true;
}

void ChoosePetScene::onEnter()
{
    CCLayer::onEnter();
}

void ChoosePetScene::onExit()
{
    CCLayer::onExit();
}


#pragma mark CcbChoosePetLayer
CcbChoosePetLayer::CcbChoosePetLayer()
: m_pScale9SpriteName (NULL)
, m_pControlButtonRandom (NULL)
, m_pControlButtonConfirm (NULL)
, m_pLabelTTFNormal_AtkName (NULL)
, m_pLabelTTFNormal_AtkLv (NULL)
, m_pLabelTTFNor_SkillDes (NULL)
, m_pLabelTTFAltSkillLv (NULL)
, m_pLabelTTFAltSkillDes (NULL)
, m_pLabelTTFAltSkillName (NULL)
, m_pSprite6Wei (NULL)
, m_pLabelTTFPetName (NULL)
, m_pLabelTTFPetIntro (NULL)
, m_pControlButtonLeft (NULL)
, m_pControlButtonRight (NULL)
, m_pNodeChoosePet (NULL)
, m_pInputBox(NULL)
, m_BeginPoint(0,0)
, m_bTouchMoved(false)
, m_pLayerTouchArea(NULL)
, m_pParticle(NULL)
, m_pCurRunNode(NULL)
, m_nCurIndex(0)
, m_pEditBoxPos(0,0)
{
    
    
}

CcbChoosePetLayer::~CcbChoosePetLayer()
{
	CC_SAFE_RELEASE_NULL(m_pScale9SpriteName);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRandom);
	CC_SAFE_RELEASE_NULL(m_pControlButtonConfirm);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNormal_AtkName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNormal_AtkLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFNor_SkillDes);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillLv);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillDes);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFAltSkillName);
	CC_SAFE_RELEASE_NULL(m_pSprite6Wei);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFPetIntro);
	CC_SAFE_RELEASE_NULL(m_pControlButtonLeft);
	CC_SAFE_RELEASE_NULL(m_pControlButtonRight);
    CC_SAFE_RELEASE_NULL(m_pNodeChoosePet);
    CC_SAFE_RELEASE_NULL(m_pLayerTouchArea);
    CC_SAFE_RELEASE_NULL(m_pParticle);

}

bool CcbChoosePetLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    m_dwPetIndex[0] = 1;
    m_dwPetIndex[1] = 5;
    m_dwPetIndex[2] = 9;
    m_dwPetIndex[3] = 13;
    this->setTouchEnabled(true);
	return true;
}

// Inhert MemberVariableAssigner
bool CcbChoosePetLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pScale9SpriteName", CCScale9Sprite*, this->m_pScale9SpriteName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRandom", CCControlButton*, this->m_pControlButtonRandom);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonConfirm", CCControlButton*, this->m_pControlButtonConfirm);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNormal_AtkName", CCLabelTTF*, this->m_pLabelTTFNormal_AtkName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNormal_AtkLv", CCLabelTTF*, this->m_pLabelTTFNormal_AtkLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFNor_SkillDes", CCLabelTTF*, this->m_pLabelTTFNor_SkillDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillLv", CCLabelTTF*, this->m_pLabelTTFAltSkillLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillDes", CCLabelTTF*, this->m_pLabelTTFAltSkillDes);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFAltSkillName", CCLabelTTF*, this->m_pLabelTTFAltSkillName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSprite6Wei", CCSprite*, this->m_pSprite6Wei);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetName", CCLabelTTF*, this->m_pLabelTTFPetName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFPetIntro", CCLabelTTF*, this->m_pLabelTTFPetIntro);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLeft", CCControlButton*, this->m_pControlButtonLeft);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRight", CCControlButton*, this->m_pControlButtonRight);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pNodeChoosePet", CCNode*, this->m_pNodeChoosePet);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerTouchArea", CCLayer*, this->m_pLayerTouchArea);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pParticle", CCNode*, this->m_pParticle);

	return false;
}

bool CcbChoosePetLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

// Inhert CCBSelectorResolver
SEL_CallFuncN CcbChoosePetLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbChoosePetLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbChoosePetLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRandom", CcbChoosePetLayer::onPressControlButtonRandom);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonConfirm", CcbChoosePetLayer::onPressControlButtonConfirm);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonLeft", CcbChoosePetLayer::onPressControlButtonLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonRight", CcbChoosePetLayer::onPressControlButtonRight);

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbChoosePetLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
    GuideData::GetInstance()->setStepId(GuideData::E_GUIDE_TRIGGER_NAME);
    GuideData::GetInstance()->connectToServer();

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(GET_PIC(Pic_StartLayer_Pet_Choose));
    CCSprite* pPetSprite = NULL;
    CCSprite* pPetSpriteMask = NULL;
    CCNode *pPetNode = NULL;
    m_pParticle->setZOrder(-1);
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        m_ArrPot[i] = pPetNode->getPosition();
        m_fScale[i] = pPetNode->getScale();
        
        pPetSprite = CCSprite::createWithSpriteFrameName(CCString::createWithFormat(GET_PIC(Pic_StartLayer_Pet),i)->getCString());
        pPetNode->addChild(pPetSprite);
        pPetSprite->setTag(0);
        pPetSprite->setZOrder(0);
        pPetNode->setZOrder(0 - i);
        
        pPetSpriteMask = (CCSprite *)pPetNode->getChildByTag(1);
        pPetSpriteMask->setZOrder(1);
        if (i == 0) {
            pPetSpriteMask->setVisible(false);
        }
    }

    m_Distance[0] = CCSizeMake(fabs(m_ArrPot[1].x  - m_ArrPot[0].x), fabs(m_ArrPot[1].y  - m_ArrPot[0].y));
    m_Distance[1] = CCSizeMake(fabs(m_ArrPot[1].x  - m_ArrPot[2].x), fabs(m_ArrPot[1].y  - m_ArrPot[2].y));

    m_pControlButtonLeft->setZOrder(2);
    m_pControlButtonConfirm->setZOrder(2);
    m_pLabelTTFPetName->setZOrder(2);
    
    CCSize inputSize;
    CCPoint inputPos;
    
    inputSize = m_pScale9SpriteName->getPreferredSize();
    inputPos = m_pScale9SpriteName->getPosition();
    CCNode* pParentNode = m_pScale9SpriteName->getParent();
    m_pScale9SpriteName->removeFromParent();
    
    m_pInputBox = CCEditBox::create(inputSize, m_pScale9SpriteName);
    m_pInputBox->setAnchorPoint(ccp(0.5, 0.5));
    m_pInputBox->setPosition(inputPos);
    
    m_pInputBox->setFontName(FONT_FZCQJW);
    m_pInputBox->setFontColor(ccc3(50, 30, 0));
    m_pInputBox->setFontSize(16);
    m_pInputBox->setPlaceHolder(GET_STR(Str_input_name));
    m_pInputBox->setMaxLength(MAX_LENGTH + 6);
    m_pInputBox->setInputMode(kEditBoxInputModeAny);
    m_pInputBox->setReturnType(kKeyboardReturnTypeDone);
    m_pInputBox->setDelegate(this);
    m_pInputBox->setHorizontalAlignment(kCCTextAlignmentCenter);
    m_pInputBox->getEditBoxImplLabel()->noStroke();
    m_pInputBox->setLabelPosition(ccp(0, inputSize.height / 2 - 8));
    m_pEditBoxPos = m_pInputBox->getEditBoxImplLabel()->getPosition();
    
    pParentNode->addChild(m_pInputBox);
    
    m_pRichNorDes = ReRichText::create("",m_pLabelTTFNor_SkillDes->getFontName(), m_pLabelTTFNor_SkillDes->getFontSize(),CCSizeMake(m_pLabelTTFNor_SkillDes->getDimensions().width, 0));
    m_pRichNorDes->ignoreAnchorPointForPosition(false);
    m_pRichNorDes->setAnchorPoint(m_pLabelTTFNor_SkillDes->getAnchorPoint());
    m_pRichNorDes->setColor(m_pLabelTTFNor_SkillDes->getColor());
    m_pRichNorDes->setPosition(m_pLabelTTFNor_SkillDes->getPosition());
    m_pLabelTTFNor_SkillDes->getParent()->addChild(m_pRichNorDes);
    m_pLabelTTFNor_SkillDes->setVisible(false);
    
    m_pRichSkillDes = ReRichText::create("",m_pLabelTTFAltSkillDes->getFontName(), m_pLabelTTFAltSkillDes->getFontSize(),CCSizeMake(m_pLabelTTFAltSkillDes->getDimensions().width, 0));
    m_pRichSkillDes->setFontName(m_pLabelTTFAltSkillDes->getFontName());
    m_pRichSkillDes->setFontSize(m_pLabelTTFAltSkillDes->getFontSize());
    m_pRichSkillDes->setColor(m_pLabelTTFAltSkillDes->getColor());
    m_pRichSkillDes->ignoreAnchorPointForPosition(false);
    m_pRichSkillDes->setAnchorPoint(m_pLabelTTFAltSkillDes->getAnchorPoint());
    m_pRichSkillDes->setPosition(m_pLabelTTFAltSkillDes->getPosition());
    m_pLabelTTFAltSkillDes->getParent()->addChild(m_pRichSkillDes);
    m_pLabelTTFAltSkillDes->setVisible(false);
    
    arrPoint[0] = ccp(0, 15);
    arrPoint[1] = ccp(13, 7.5);
    arrPoint[2] = ccp(13, -7.5);
    arrPoint[3] = ccp(0, -15);
    arrPoint[4] = ccp(-13, -7.5);
    arrPoint[5] = ccp(-13, 7.5);
    
//    m_StartColor4F[0] = ccc4f(207, 85, 40, 0);
//    m_StartColor4F[1] = ccc4f(44, 74, 207, 0);
//    m_StartColor4F[2] = ccc4f(10, 255, 0, 0);
//    m_StartColor4F[3] = ccc4f(255, 245, 1, 0);
//    
//    m_EndColor4f[0] = ccc4f(0, 0, 0, 255);
//    m_EndColor4f[1] = ccc4f(33, 105, 201, 255);
//    m_EndColor4f[2] = ccc4f(0, 255, 17, 255);
//    m_EndColor4f[3] = ccc4f(233, 255, 46, 255);
    
    srand(unsigned(time(0)));
    int nDir = rand() % CHOOSEPETSCNT;
    CCNode* pPetNodeTmp[4] ;
    
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNodeTmp[i] = m_pNodeChoosePet->getChildByTag(i);
    }
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNodeTmp[i]->setTag((i + nDir) % CHOOSEPETSCNT);
    }
    
    m_nCurIndex = (m_nCurIndex - nDir + CHOOSEPETSCNT) % CHOOSEPETSCNT;
    this->autoAdjustNodePos();
}

#pragma mark - onEnter & onExit -
void CcbChoosePetLayer::onEnter()
{
    CCLayer::onEnter();
    CCPoint layerPos = m_pLayerTouchArea->convertToWorldSpace(CCPointZero);
    m_LayerRect = CCRectMake(layerPos.x, layerPos.y, m_pLayerTouchArea->getContentSize().width * this->getScale(), m_pLayerTouchArea->getContentSize().height * this->getScale());
    
    
}

void CcbChoosePetLayer::onEnterTransitionDidFinish()
{
    CCLayer::onEnterTransitionDidFinish();
    
    m_vecFirstName.clear();
    m_vecSecondName.clear();
    m_vecThirdName.clear();
    std::map<uint32, RandomNameConfig::STC_RANDOM_NAME> ranNameMap = GET_CONFIG_MAP(RandomNameConfig);
    std::map<uint32, RandomNameConfig::STC_RANDOM_NAME>::iterator pIter;
    for (pIter = ranNameMap.begin(); pIter != ranNameMap.end(); pIter++) {
        RandomNameConfig::STC_RANDOM_NAME cfg;
        cfg = pIter->second;
        m_vecFirstName.push_back(cfg.strFistName);
        m_vecSecondName.push_back(cfg.strSecondName);
        m_vecThirdName.push_back(cfg.strThirdName);
    }
    onPressControlButtonRandom(NULL, CCControlStateSelected);
    
}

void CcbChoosePetLayer::onExit()
{
    CCLayer::onExit();
    if (m_pCurRunNode) {
        m_pCurRunNode->stopAllActions();
    }
}

void CcbChoosePetLayer::onExitTransitionDidStart()
{
    CCLayer::onExitTransitionDidStart();
}

#pragma mark - Button Functions -
void CcbChoosePetLayer::onPressControlButtonRandom(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    std::string strName;
    int nFirst = rand() % m_vecFirstName.size();
    int nSecond = rand() % m_vecSecondName.size();
    int nThird = rand() % m_vecThirdName.size();
    
    strName = m_vecFirstName[nFirst] + m_vecSecondName[nSecond] + m_vecThirdName[nThird];
    m_pInputBox->setText(strName.c_str());
}

void CcbChoosePetLayer::onPressControlButtonConfirm(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    if (this->checkNameLegal()) {
        PetLoadingLayer::sharedLayer()->WaitForPacket(true);
        CGameSession::SendChoosePet(m_dwPetIndex[m_nCurIndex]);
        CGameSession::SendChooseName(m_pInputBox->getText());
    }
    else
    {
        
    }
}

void CcbChoosePetLayer::onPressControlButtonLeft(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CCNode* pPetNode = NULL;
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        pPetNode->stopAllActions();
        pPetNode->setPosition(m_ArrPot[i]);
        pPetNode->setScale(m_fScale[i]);
    }
    this->changeNodeTagByDir(1);
}

void CcbChoosePetLayer::onPressControlButtonRight(CCObject* pSender, CCControlEvent event)
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    CCNode* pPetNode = NULL;
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        pPetNode->stopAllActions();
        pPetNode->setPosition(m_ArrPot[i]);
        pPetNode->setScale(m_fScale[i]);
    }
	this->changeNodeTagByDir(-1);
}

#pragma mark - Touch Functions -
bool CcbChoosePetLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_BeginPoint = pTouch->getLocation();
    m_bTouchMoved = false;
    if (m_LayerRect.containsPoint(m_BeginPoint)) {
        return true;
    }
    return false;
}

void CcbChoosePetLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPoint = pTouch->getLocation();
    float fOffset = curPoint.x - m_BeginPoint.x;
    if (fabs(fOffset) > 10) {
        m_bTouchMoved = true;
        if (fOffset > 0) {
            m_pNodeChoosePet->getChildByTag(3)->setZOrder(0);
            m_pNodeChoosePet->getChildByTag(3)->getChildByTag(1)->setVisible(false);
            for (int i = 0; i < 3; i++) {
                m_pNodeChoosePet->getChildByTag(i)->setZOrder(-2 - i);
                m_pNodeChoosePet->getChildByTag(i)->getChildByTag(1)->setVisible(true);
            }
            
        }
        else
        {
            for (int i = 0; i < CHOOSEPETSCNT; i++) {
                m_pNodeChoosePet->getChildByTag(i)->setZOrder(-2 - i);
                m_pNodeChoosePet->getChildByTag(i)->getChildByTag(1)->setVisible(true);
            }
            m_pNodeChoosePet->getChildByTag(1)->setZOrder(0);
            m_pNodeChoosePet->getChildByTag(1)->getChildByTag(1)->setVisible(false);
        }
    }
    else
    {
        this->autoAdjustNodeZorder();
    }
    
    if (fabs(fOffset) > m_Distance[0].width) {
        fOffset = fOffset > 0 ? m_Distance[0].width : - m_Distance[0].width;
    }
    
    this->updateNodePosByOffset(fOffset);
}

void CcbChoosePetLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint curPoint = pTouch->getLocation();
    float fOffset = curPoint.x - m_BeginPoint.x;
    if (fabs(fOffset) > 10) {
        m_bTouchMoved = true;
        this->changeNodeTagByDir(fOffset > 0 ? 1 : -1);
    }
    else
    {
        this->autoAdjustNodePos();
        m_bTouchMoved = false;
    }
    
}

void CcbChoosePetLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void CcbChoosePetLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}


#pragma mark - Self Functions -
void CcbChoosePetLayer::updateNodePosByOffset(float offset)
{
    CCNode* pPetNode = NULL;
    float fScale = 0.0f;
    
    
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        if (!pPetNode) {
            continue;
        }
        switch (i) {
            case 0:
            {
                float y = 0;
                float fScale = 0.0f;
            
                y = (fabs(offset) / m_Distance[0].width) * m_Distance[0].height;
                pPetNode->setPosition( ccpAdd(m_ArrPot[i],ccp(offset, y) * 1));
                
                fScale = m_fScale[i] - fabs(offset) / m_Distance[0].width * fabs(m_fScale[0] - m_fScale[1]);
                pPetNode->setScale(fScale);
                break;
            }
            case 1:
            {
                float y = 0.0f;
                float fScale = 0.0f;
                if (offset > 0) {
                    y = - (fabs(offset) / m_Distance[0].width) * m_Distance[1].height;
                    fScale = m_fScale[i] - fabs(offset) / m_Distance[0].width * fabs(m_fScale[2] - m_fScale[1]);
                }
                else
                {
                    y = - (fabs(offset) / m_Distance[0].width) * m_Distance[0].height;
                    fScale = m_fScale[i] + fabs(offset) / m_Distance[0].width * fabs(m_fScale[0] - m_fScale[1]);
                }
                pPetNode->setPosition( ccpAdd(m_ArrPot[i], ccp(offset, y) * (offset > 0 ? -1 : 1)));
                pPetNode->setScale(fScale);
                break;
            }
            case 2:
            {
                float y = (fabs(offset) / m_Distance[0].width) * m_Distance[1].height;
                pPetNode->setPosition( ccpAdd(m_ArrPot[i], ccp(offset, y) * -1));
                
                fScale = m_fScale[i] + fabs(offset) / m_Distance[0].width * fabs(m_fScale[2] - m_fScale[1]);
                pPetNode->setScale(fScale);
                break;
            }
            case 3:
            {
                float y =  0.0f;
                if (offset > 0) {
                    y = - (fabs(offset) / m_Distance[0].width) * m_Distance[0].height;
                    fScale = m_fScale[i] + fabs(offset) / m_Distance[0].width * fabs(m_fScale[0] - m_fScale[1]);
                }
                else
                {
                    y = - (fabs(offset) / m_Distance[0].width) * m_Distance[1].height;
                    fScale = m_fScale[i] - fabs(offset) / m_Distance[0].width * fabs(m_fScale[2] - m_fScale[1]);
                }
                pPetNode->setPosition( ccpAdd(m_ArrPot[i], ccp(offset, y) * (offset > 0 ? 1 : -1)));
                
                pPetNode->setScale(fScale);
                break;
            }
            default:
                break;
        }
    }
}

void CcbChoosePetLayer::changeNodeTagByDir(int dir)
{
    CCNode* pPetNode = NULL;
    if (dir > 0 ){
        CCNode* pPetNodeTmp = m_pNodeChoosePet->getChildByTag(3);
        for (int i = 2; i >= 0; i--) {
            pPetNode = m_pNodeChoosePet->getChildByTag(i);
            pPetNode->setTag(i + 1 );
        }
        pPetNodeTmp->setTag(0);
    }
    else if(dir < 0)
    {
        CCNode* pPetNodeTmp = m_pNodeChoosePet->getChildByTag(0);
        for (int i = 1; i < CHOOSEPETSCNT; i++) {
            pPetNode = m_pNodeChoosePet->getChildByTag(i);
            pPetNode->setTag( i - 1);
        }
        pPetNodeTmp->setTag(3);
        
    }
    m_nCurIndex = (m_nCurIndex - dir + CHOOSEPETSCNT) % CHOOSEPETSCNT;
    this->autoAdjustNodePos();
}

void CcbChoosePetLayer::autoAdjustNodePos()
{
    CCNode* pPetNode = NULL;
    for (int i = 0; i < 4; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        pPetNode->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(ANIMATIONTIME, m_ArrPot[i]),CCScaleTo::create(ANIMATIONTIME, m_fScale[i]) ,NULL),CCCallFunc::create(this, callfunc_selector(CcbChoosePetLayer::afterAnimationFinishCallBack)),NULL));
    }
    for (int i = 0; i < CHOOSEPETSCNT; i++) {
        if (i == m_nCurIndex) {
            m_pParticle->getChildByTag(i)->setVisible(true);
        }
        else
        {
            m_pParticle->getChildByTag(i)->setVisible(false);
        }
        
    }
    this->autoAdjustNodeZorder();
}

void CcbChoosePetLayer::autoAdjustNodeZorder()
{
    CCNode* pPetNode = m_pNodeChoosePet->getChildByTag(3);
    pPetNode->setZOrder( - 2);
    pPetNode->getChildByTag(1)->setVisible(true);
    for (int i = 0; i < 3; i++) {
        pPetNode = m_pNodeChoosePet->getChildByTag(i);
        pPetNode->setZOrder(0 - i);
        if (i == 0) {
            pPetNode->getChildByTag(1)->setVisible(false);
            pPetNode->setZOrder(0);
        }
        else
        {
            pPetNode->getChildByTag(1)->setVisible(true);
            pPetNode->setZOrder( - 2);
        }
       
    }
    
}

void CcbChoosePetLayer::afterAnimationFinishCallBack()
{
    this->runBreathAnimation(m_pNodeChoosePet->getChildByTag(0)->getChildByTag(0));
    this->setShowInfo();
}

void CcbChoosePetLayer::setShowInfo()
{
    
    
    PetConfig::STC_PET_CONFIG *pConfig = GET_CONFIG_STC(PetConfig, m_dwPetIndex[m_nCurIndex]);
    if (!pConfig) {
        return;
    }
    m_pLabelTTFPetName->setString(pConfig->strName.c_str());
    m_pLabelTTFPetIntro->setString(pConfig->strDes.c_str());
    
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *norCfg = GET_CONFIG_STC(UltimateSkillConfig, pConfig->dwNomaleAttId);
    if (!norCfg) {
        return;
    }
    m_pLabelTTFNormal_AtkName->setString(norCfg->strName.c_str());
    const char* des = PARSE_STRING1(norCfg->strDes, norCfg->dwSkillAbi / 100);
    m_pRichNorDes->setString(des);
    UltimateSkillConfig::STC_ULIMATE_SKILL_CONFIG *ultCfg = GET_CONFIG_STC(UltimateSkillConfig, pConfig->wInitialSkillId);
    if (!ultCfg) {
        return;
    }
    m_pLabelTTFAltSkillName->setString(ultCfg->strName.c_str());
    m_pLabelTTFAltSkillLv->setString(CCString::createWithFormat("%s%d", SB_Lv,1)->getCString());
    m_pLabelTTFAltSkillLv->setPositionX(getRight(m_pLabelTTFAltSkillName) + 10);
    const char* ultDes = PARSE_STRING1(ultCfg->strDes, ultCfg->dwSkillAbi / 100);
    m_pRichSkillDes->setString(ultDes);
    
    this->removeChildByTag(101);
    //六维图
    PetLiuWeiConfig::STC_CONFIG_PET_LIUWEI* liuweiCfg = GET_CONFIG_STC(PetLiuWeiConfig, m_dwPetIndex[m_nCurIndex]);
    if (liuweiCfg) {
        float base = 100.0f;
        float offX = 30.0f * 0.8;
        float offY = 35.0f * 0.8;
        CCPoint pos = m_pSprite6Wei->convertToWorldSpace(m_pSprite6Wei->getContentSize() / 2);
        
        CCPoint points[] = { arrPoint[0] + ccp(0, offY) * (liuweiCfg->wAtk / base) + pos,
            arrPoint[1] + ccp(offX, 0.5*offY) * (liuweiCfg->wHp / base) + pos,
            arrPoint[2] + ccp(offX, -0.5*offY) * (liuweiCfg->wSDef / base) + pos,
            arrPoint[3] + ccp(0, -offY) * (liuweiCfg->wControl / base) + pos,
            arrPoint[4] + ccp(-offX, -0.5*offY) * (liuweiCfg->wSupp / base) + pos,
            arrPoint[5] + ccp(-offX, 0.5*offY) * liuweiCfg->wCDef / base + pos
            
        };
        
        HexagonLayer* pHexago = HexagonLayer::create();
        this->addChild(pHexago,5,101);
        pHexago->setEachPoints(points);
        pHexago->setColor(ccc4f(253, 163, 0, 0.5f));
        pHexago->setNumberOfPoints(6);
    }
    
}

void CcbChoosePetLayer::runBreathAnimation(CCNode *pNode)
{
    if (m_pCurRunNode) {
        m_pCurRunNode->stopAllActions();
    }
    m_pCurRunNode = pNode;
    pNode->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1.5, 0.95),CCScaleTo::create(1.5, 1.0),NULL)));
}

bool CcbChoosePetLayer::checkNameLegal()
{
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    
    if (m_pInputBox->getText() == NULL) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_not_null));
        return false;
    } else if (strlen(m_pInputBox->getText()) < 4) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_min_len));
        return false;
    } else if ( _calcCharCountUTF(m_pInputBox->getText()) > MAX_LENGTH ) {
        SystemMessage::showSystemMessage(0, this, GET_STR(Str_name_too_long));
        return false;
    }
    return true;
}


#pragma mark EditBox Delegate
void CcbChoosePetLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox)
{
    editBox->getEditBoxImplLabel()->setPosition(m_pEditBoxPos);
}

void CcbChoosePetLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox)
{
    editBox->getEditBoxImplLabel()->setPosition(m_pEditBoxPos);
}

void CcbChoosePetLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, const std::string &text)
{
    editBox->getEditBoxImplLabel()->setPosition(m_pEditBoxPos);
}

void CcbChoosePetLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox)
{
    editBox->getEditBoxImplLabel()->setPosition(m_pEditBoxPos);
    this->checkNameLegal();
}

