#include "CcbSortLayer.h"
//#include "CcbManager.h"
#include "PetCtrl.h"
#include "ResourceStringConverter.h"
#include "PropertyList.h"
#include "Observer.h"
#include "CcbPetBagLayer.h"
#include "ResourceStringClient.h"
#include "MusicCtrl.h"
#include "ConfigGet.h"
USING_NS_CC;
USING_NS_CC_EXT;

#define Up        GET_STR(Str_sort_up)
#define Down      GET_STR(Str_sort_down)
#define Lv        GET_STR(Str_lv)
#define Nature    GET_STR(Str_nature)
#define Birthday  GET_STR(Str_birthday)
#define Attack    GET_STR(Str_atk)
#define Defense   GET_STR(Str_def)
#define Recover   GET_STR(Str_rev)
#define Star      GET_STR(Str_star)
#define Hp        GET_STR(Str_hp)
#define SDef      GET_STR(Str_SDef)

CcbSortLayer::~CcbSortLayer()
{
//	this->m_pControlButtonLv->release();
//	this->m_pControlButtonAttack->release();
//	this->m_pControlButtonStar->release();
//	this->m_pControlButtonNature->release();
//	this->m_pControlButtonBirthday->release();
//	this->m_pControlButtonDefense->release();
//	this->m_pControlButtonRecover->release();
    CC_SAFE_RELEASE_NULL(m_pControlButtonLv);
    CC_SAFE_RELEASE_NULL(m_pControlButtonAttack);
    CC_SAFE_RELEASE_NULL(m_pControlButtonStar);
    CC_SAFE_RELEASE_NULL(m_pControlButtonNature);
    CC_SAFE_RELEASE_NULL(m_pControlButtonBirthday);
    CC_SAFE_RELEASE_NULL(m_pControlButtonDefense);
    CC_SAFE_RELEASE_NULL(m_pControlButtonRecover);
    CC_SAFE_RELEASE_NULL(m_pControlButtonClose);
    CC_SAFE_RELEASE_NULL(m_pControlButtonSpeDefense);
    m_delegate = NULL;
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbSortLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbSortLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader("CcbSortLayer", CcbSortLayerLoader::loader());
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/sort.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

bool CcbSortLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (this->isVisible()) {
        return true;
    }
    return false;
}
void CcbSortLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 5, true);
}

//CCScene* CcbSortLayer::scene()
//{
//	// scene() was called after init()
//	CCScene* scene = CCScene::create();
//	//CCNode* pNode = CcbManager::sharedManager()->LoadCcbSortLayer(scene);
//    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//	pLoaderLib->registerCCNodeLoader( "CcbSortLayer", CcbSortLayerLoader::loader() );
//	
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile( "ccb/sort.ccbi", scene );
//	
//	if (pNode != NULL)
//	{
//        pNode->setTag(1);
//		scene->addChild(pNode);
//	}
//	pCCBReader->release();
//	return scene;
//}

bool CcbSortLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
    this->setTouchEnabled(true);
//    this->setTouchPriority(kCCMenuHandlerPriority - 5);
    m_delegate = NULL;
//	// code here
//    CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//	pLoaderLib->registerCCNodeLoader( "CcbSortLayer", CcbSortLayerLoader::loader() );
//	
//    
//	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
//	CCNode* pNode = pCCBReader->readNodeGraphFromFile( "ccb/sort.ccbi", this );
//	
//	if (pNode != NULL)
//	{
//		addChild(pNode);
//	}
//	pCCBReader->release();
	return true;
}

void CcbSortLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    arrSortButton.push_back(m_pControlButtonLv);
    arrSortButton.push_back(m_pControlButtonNature);
    arrSortButton.push_back(m_pControlButtonBirthday);
    arrSortButton.push_back(m_pControlButtonAttack);
    arrSortButton.push_back(m_pControlButtonDefense);
    arrSortButton.push_back(m_pControlButtonSpeDefense);
    arrSortButton.push_back(m_pControlButtonRecover);
    arrSortButton.push_back(m_pControlButtonStar);
    arrSortButton.push_back(m_pControlButtonHP);
    
    
    for (int i = 0; i < arrSortButton.size(); i++) {
        arrSortButton[i]->setTag(i+1);
        arrSortButton[i]->setTouchPriority(kCCMenuHandlerPriority - 5);
    }
    m_pControlButtonClose->setTouchPriority(kCCMenuHandlerPriority - 5);
    arrBtnName.push_back(Lv);
    arrBtnName.push_back(Nature);
    arrBtnName.push_back(Birthday);
    arrBtnName.push_back(Attack);
    arrBtnName.push_back(Defense);
    arrBtnName.push_back(SDef);
    arrBtnName.push_back(Recover);
    arrBtnName.push_back(Star);
    arrBtnName.push_back(Hp);
    

    bFlag = false;
//    m_pControlButtonLv->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonAttack->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonStar->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonNature->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonBirthday->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonDefense->setTouchPriority(kCCMenuHandlerPriority - 5);
//    m_pControlButtonRecover->setTouchPriority(kCCMenuHandlerPriority - 5);
    
    
    
    loadData();
}

void CcbSortLayer::onExit()
{
	CCLayer::onExit();
}

SEL_CallFuncN CcbSortLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbSortLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

bool CcbSortLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonLv", CCControlButton*, this->m_pControlButtonLv);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonAttack", CCControlButton*, this->m_pControlButtonAttack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonStar", CCControlButton*, this->m_pControlButtonStar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonNature", CCControlButton*, this->m_pControlButtonNature);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonBirthday", CCControlButton*, this->m_pControlButtonBirthday);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonDefense", CCControlButton*, this->m_pControlButtonDefense);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonRecover", CCControlButton*, this->m_pControlButtonRecover);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonClose", CCControlButton*, this->m_pControlButtonClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonHP", CCControlButton*, this->m_pControlButtonHP);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pControlButtonSpeDefense", CCControlButton*, this->m_pControlButtonSpeDefense);

	return false;
}

bool CcbSortLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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


SEL_CCControlHandler CcbSortLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonSort", CcbSortLayer::onPressControlButtonSort);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressControlButtonClose", CcbSortLayer::onPressControlButtonClose);
	return NULL;
}

void CcbSortLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
}

void CcbSortLayer::onPressControlButtonSort(CCObject* pSender, CCControlEvent event)
{
	// TODO:
    if (bFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_confirm));
    uint8 tag = dynamic_cast<CCControlButton*>(pSender)->getTag();
    uint8 old = CPetCtrl::Get()->GetSortType();
    if (old == tag) {
        CPetCtrl::Get()->SetSortUp(!CPetCtrl::Get()->GetSortUp());
    }
    else
    {
        CPetCtrl::Get()->SetSortType(tag);
        CPetCtrl::Get()->SetSortUp(false);
    }
    changeButton(old, tag);
}

void CcbSortLayer::onPressControlButtonClose(CCObject* pSender, CCControlEvent event)
{
	// TODO:
//    onHide();
    if (bFlag) {
        return;
    }
    CMusicCtrl::PlayEffect(GET_MUSIC(Eff_return));
    this->setVisible(false);
}

void CcbSortLayer::loadData()
{
    //    m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(Lv, "", 17));
    m_pControlButtonLv->setTitleForState(CCString::create(Lv), CCControlStateNormal);
    m_pControlButtonAttack->setTitleForState(CCString::create(Attack), CCControlStateNormal);
    m_pControlButtonStar->setTitleForState(CCString::create(Star), CCControlStateNormal);
    m_pControlButtonNature->setTitleForState(CCString::create(Nature), CCControlStateNormal);
    m_pControlButtonBirthday->setTitleForState(CCString::create(Birthday), CCControlStateNormal);
    m_pControlButtonDefense->setTitleForState(CCString::create(Defense), CCControlStateNormal);
    m_pControlButtonRecover->setTitleForState(CCString::create(Recover), CCControlStateNormal);
    m_pControlButtonHP->setTitleForState(CCString::create(Hp), CCControlStateNormal);
    m_pControlButtonSpeDefense->setTitleForState(CCString::create(SDef), CCControlStateNormal);
    
    std::string p = Down;
    if (CPetCtrl::Get()->GetSortUp()) {
        p = Up;
        //        p = 2;
    }
    //    std::string name = "";
    switch (CPetCtrl::Get()->GetSortType()) {
        case CPetCtrl::E_PET_SORT_TYPE_LV:
            //            name = Lv;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0##:##1##",Lv,p), "", 17));
            m_pControlButtonLv->setTitleForState(CCString::createWithFormat("%s%s", Lv, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_NATURE:
            //            name = Nature;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Nature,p), "", 17));
            m_pControlButtonNature->setTitleForState(CCString::createWithFormat("%s%s", Nature, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_BIRTHDAY:
            //            name = Birthday;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Birthday,p), "", 17));
            m_pControlButtonBirthday->setTitleForState(CCString::createWithFormat("%s%s", Birthday, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_ATTACK:
            //            name = Attack;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Attack,p), "", 17));
            m_pControlButtonAttack->setTitleForState(CCString::createWithFormat("%s%s", Attack, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_DEFENSE:
            //            name = Defense;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Defense,p), "", 17));
            m_pControlButtonDefense->setTitleForState(CCString::createWithFormat("%s%s", Defense, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_SDEF:    //防御}
            //            name = Defense;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Defense,p), "", 17));
            m_pControlButtonSpeDefense->setTitleForState(CCString::createWithFormat("%s%s", SDef, p.c_str()), CCControlStateNormal);
            break;
            
        case CPetCtrl::E_PET_SORT_TYPE_RECOVER:
            //            name = Recover;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Recover,p), "", 17));
            m_pControlButtonRecover->setTitleForState(CCString::createWithFormat("%s%s", Recover, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_STAR:
            //            name = Star;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Star,p), "", 17));
            m_pControlButtonStar->setTitleForState(CCString::createWithFormat("%s%s", Star, p.c_str()), CCControlStateNormal);
            break;
        case CPetCtrl::E_PET_SORT_TYPE_HP:
            //            name = Star;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Star,p), "", 17));
            m_pControlButtonHP->setTitleForState(CCString::createWithFormat("%s%s", Hp, p.c_str()), CCControlStateNormal);
            break;
        default:
            //            name = Lv;
            //            m_pControlButtonLv->setTitleLabel(CCLabelTTF::create(PARSE_STRING2("##0####1##",Lv,p), "", 17));
            m_pControlButtonBirthday->setTitleForState(CCString::createWithFormat("%s%s", Birthday, p.c_str()), CCControlStateNormal);
            break;
    }
}

void CcbSortLayer::changeButton(uint8 old, uint8 sortType)
{
    bFlag = true;
    this->setVisible(false);
    std::string p = Down;
    if (CPetCtrl::Get()->GetSortUp()) {
        p = Up;
    }
    if (old != sortType) {
        CCControlButton * btnOld = arrSortButton[old - 1];
        CCControlButton * btnNew = arrSortButton[sortType - 1];

        btnOld->setTitleForState(CCString::create(arrBtnName[old - 1]), CCControlStateNormal);
        btnNew->setTitleForState(CCString::createWithFormat("%s%s", arrBtnName[sortType - 1].c_str(), p.c_str()), CCControlStateNormal);
    }
    else
    {
        CCControlButton * btnOld = arrSortButton[old - 1];
        btnOld->setTitleForState(CCString::createWithFormat("%s%s", arrBtnName[old - 1].c_str(), p.c_str()), CCControlStateNormal);
    }
    if (m_delegate) {
        m_delegate->RefeashLayer();
    }
    bFlag = false;
    CPetCtrl::Get()->ReflashPetBag();
    
//    removeFromParentAndCleanup(true);
}





