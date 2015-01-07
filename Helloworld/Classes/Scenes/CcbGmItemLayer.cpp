#include "CcbGmItemLayer.h"
//#include "CcbManager.h"
#include "CCScrollViewWithBar.h"
#include "UISupport.h"
#include "CCScrollButton.h"
#include "PetCtrl.h"
#include "ItemDataMgr.h"
#include "EnumDefines.h"
#include "EquipDataMgr.h"
#include "EmblemDataMgr.h"
#include "CCScrollButton.h"
#include "PacketDataMgr.h"
#include "ResourceDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbGmItemLayer::~CcbGmItemLayer()
{
	CC_SAFE_RELEASE_NULL(m_pLayerItemBg);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFName);
	CC_SAFE_RELEASE_NULL(m_pLabelTTFId);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Cnt);
	CC_SAFE_RELEASE_NULL(m_pLayerInsert_Lv);

}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbGmItemLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbGmItemLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbGmItemLayer", CcbGmItemLayerLoader::loader() );
	pLoaderLib->registerCCNodeLoader( "[ccb/gm_insert.ccb]", [ccb/gm_insert.ccb]Loader::loader() );

    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/gm_item.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/


bool CcbGmItemLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
	return true;
}

void CcbGmItemLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
}

void CcbGmItemLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbGmItemLayer::onExit()
{
	CCLayer::onExit();
}

void CcbGmItemLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

// Inhert MemberVariableAssigner
bool CcbGmItemLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerItemBg", CCLayer*, this->m_pLayerItemBg);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFName", CCLabelTTF*, this->m_pLabelTTFName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFId", CCLabelTTF*, this->m_pLabelTTFId);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Cnt", CcbGmInsertLayer*, this->m_pLayerInsert_Cnt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLayerInsert_Lv", CcbGmInsertLayer*, this->m_pLayerInsert_Lv);

	return false;
}

bool CcbGmItemLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbGmItemLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbGmItemLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbGmItemLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

// Inhert CCNodeLoaderListener
void CcbGmItemLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    m_type = 0;
    m_table = CCTableView::create(this, m_pLayerItemBg->getContentSize());
    m_table->setDirection(kCCScrollViewDirectionVertical);
    m_table->setVerticalFillOrder(kCCTableViewFillTopDown);
    m_table->setBounceable(true);
    CCTableViewWithBar *layerWithBar = CCTableViewWithBar::create(m_table);
    layerWithBar->setPosition(CCPointZero);
    layerWithBar->setAnchorPoint(CCPointZero);
    layerWithBar->setTag(111);
    m_pLayerItemBg->addChild(layerWithBar);
    
    m_pLayerInsert_Cnt->setNum(1);
    m_pLayerInsert_Lv->setNum(1);
}

void CcbGmItemLayer::setType(uint8 type)
{
    if (m_type == type) {
        return;
    }
    m_type = type;
    
    loadData();
}

void CcbGmItemLayer::loadData()
{
    mapPet.clear();
    mapItem.clear();
    mapRune.clear();
    mapEquip.clear();
    mapEmblem.clear();
    switch (m_type) {
        case E_GM_ITEM_PET:
            mapPet = GET_CONFIG_MAP(PetConfig);
            break;
        case E_GM_ITEM_ITEM:
            mapItem = GET_CONFIG_MAP(ItemConfig);
            break;
        case E_GM_ITEM_RUNE:
            mapRune = GET_CONFIG_MAP(RuneConfig);
            break;
        case E_GM_ITEM_EQUIP:
            mapEquip = GET_CONFIG_MAP(EquipNewConfig);
            break;
        case E_GM_ITEM_EMBLEM:
            mapEmblem = GET_CONFIG_MAP(EmblemConfig);
            break;
            
        default:
            break;
    }
    vctPet.clear();
    std::map<uint16, PetConfig::STC_PET_CONFIG>::iterator itPet = mapPet.begin();
    for (; itPet != mapPet.end(); itPet++) {
        if (itPet->first == 0) {
            continue;
        }
        vctPet.push_back(itPet->first);
    }
    
    vcttem.clear();
     std::map<uint32, ItemConfig::STC_ITEM_CONFIG>::iterator itItem = mapItem.begin();
    for (; itItem != mapItem.end(); itItem++) {
        if (itItem->first == 0) {
            continue;
        }
        vcttem.push_back(itItem->first);
    }
    
    vctRune.clear();
     std::map<uint32, RuneConfig::STC_RUNE_CONFIG>::iterator itRune = mapRune.begin();
    for (; itRune != mapRune.end(); itRune++) {
        if (itRune->first == 0) {
            continue;
        }
        vctRune.push_back(itRune->first);
    }
    
    vctEquip.clear();
    std::map<uint32, EquipNewConfig::STC_EQUIP_CONFIG>::iterator itEquip = mapEquip.begin();
    for (; itEquip != mapEquip.end(); itEquip++) {
        if (itEquip->first == 0) {
            continue;
        }
        vctEquip.push_back(itEquip->first);
    }
    
    vctEmblem.clear();
    std::map<uint32, EmblemConfig::STC_EMBLEM_CONFIG>::iterator itEmblem = mapEmblem.begin();
    for (; itEmblem != mapEmblem.end(); itEmblem++) {
        if (itEmblem->first == 0) {
            continue;
        }
        vctEmblem.push_back(itEmblem->first);
    }
    
    m_table->reloadData();
    m_pLabelTTFId->setString("");
    m_pLabelTTFName->setString("");
    dynamic_cast<CCTableViewWithBar*>(m_pLayerItemBg->getChildByTag(111))->checkIsShow(numberOfCellsInTableView(m_table) ,cellSizeForTable(m_table));
}

CCSize CcbGmItemLayer::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
    return CCSize(220,40);
}

CCTableViewCell* CcbGmItemLayer::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell  = table->dequeueCell();
    int cnt = 0;
    switch (m_type) {
        case E_GM_ITEM_PET:
            cnt = vctPet.size() - idx * 5;
            break;
        case E_GM_ITEM_ITEM:
            cnt = vcttem.size() - idx * 5;
            break;
        case E_GM_ITEM_RUNE:
            cnt = vctRune.size() - idx * 5;
            break;
        case E_GM_ITEM_EQUIP:
            cnt = vctEquip.size() - idx * 5;
            break;
        case E_GM_ITEM_EMBLEM:
            cnt = vctEmblem.size() - idx * 5;
            break;
            
        default:
            break;
    }
    
    if (cnt > 5) {
        cnt  = 5;
    }
    CCPoint pos = getWorldPos(this);
    CCRect rect = CCRectMake(pos.x + m_pLayerItemBg->getPositionX(), pos.y + m_pLayerItemBg->getPositionY(), m_pLayerItemBg->getContentSize().width, m_pLayerItemBg->getContentSize().height);
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
    }
    else
    {
        cell->removeAllChildren();
    }
    
    CCNode *node = CCNode::create();
    node->setContentSize(CCSizeMake(table->getContentSize().width, 60));
    
    for (int i = 0; i < cnt; i++) {
        uint32 petId = 0;//idx * 5 + i + 1;
//        cocos2d::extension::CCScale9Sprite *sprite = NULL;

        std::string path = "";
        switch (m_type) {
            case E_GM_ITEM_PET:
                petId = vctPet[idx * 5 + i];
                path = CPetCtrl::Get()->GetPetHeadPicName(petId);
                break;
            case E_GM_ITEM_ITEM:
                petId = vcttem[idx * 5 + i];
//                g_ItemData
                path = g_PacketDataMgr->GetItemIconByIndex(petId);
                break;
            case E_GM_ITEM_RUNE:
                petId = vctRune[idx * 5 + i];
                path = g_PacketDataMgr->GetRuneIconByIndex(petId);
                break;
            case E_GM_ITEM_EQUIP:
                petId = vctEquip[idx * 5 + i];
                path = g_PacketDataMgr->GetEquipIconByIndex(petId);
                break;
            case E_GM_ITEM_EMBLEM:
                petId = vctEmblem[idx * 5 + i];
                path = g_EmblemData->getIconPath(petId);
                break;
                
            default:
                break;
        }
        
        CCSprite *img = CCSprite::create(path.c_str());
        img->setPosition(ccp(i * 38 + 12, 0));
        img->setAnchorPoint(ccp(0, 0));
        node->addChild(img);
//        CCRect fullRect = CCRectMake(0, 0, getWidth(img), getHeight(img));
//        sprite = cocos2d::extension::CCScale9Sprite::create(path.c_str(), fullRect, fullRect);
        
        CCScrollButton *btn = CCScrollButton::createTransWithHightLight();// (sprite);
        btn->setZoomOnTouchDown(false);
        
        btn->setPreferredSize(img->getContentSize());
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(CcbGmItemLayer::onSelected), CCControlEventTouchUpInside);
        btn->setTag(petId);
        btn->setPosition(ccp(i * 38 + 12, 0));
        btn->setAnchorPoint(ccp(0, 0));
        btn->setClipRect(rect);
        node->addChild(btn);
        
        CCString *str = CCString::createWithFormat("No.%d", petId);
        std::string name = "";
        switch (m_type) {
            case E_GM_ITEM_PET:
//                name = mapPet[petId].strName;
                //            m_pLayerInsert_Lv->setVisible(true);
                break;
            case E_GM_ITEM_ITEM:
                //            petId = E_UNITE_TYPE_ITEM* E_UINTE_BASE_FABIO + petId;
                str->initWithFormat("%s", mapItem[petId].strName.c_str());
                //            m_pLayerInsert_Lv->setVisible(false);
                break;
            case E_GM_ITEM_RUNE:
                //            mapPet = GET_CONFIG_MAP();
                //            petId = E_UNITE_TYPE_Rune * E_UINTE_BASE_FABIO + petId;
                str->initWithFormat("%s", mapRune[petId].strName.c_str());
                //            m_pLayerInsert_Lv->setVisible(false);
                break;
            case E_GM_ITEM_EQUIP:
                str->initWithFormat("%s", mapEquip[petId].strName.c_str());
                break;
            case E_GM_ITEM_EMBLEM:
                str->initWithFormat("%s", mapEmblem[petId].strName.c_str());
                break;
                
            default:
                break;
        }
        CCLabelTTF *lblNo = CCLabelTTF::create(str->getCString(), FONT_HEL, 12, CCSizeMake(getWidth(btn), 0), kCCTextAlignmentCenter);// (str->getCString(), "", 12);
        
        lblNo->setPosition(ccp(getWidth(btn)* 0.5, -5));
        lblNo->setAnchorPoint(ccp(0.5, 0));
            
        btn->addChild(lblNo);
        img->setScale(0.65);
        btn->setScale(0.65);
    }
    node->setPosition(ccp(0, 3));
    node->setAnchorPoint(CCPointZero);
    cell->addChild(node, 1);
    
    return cell;
}
unsigned int CcbGmItemLayer::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    int n = 0;
    uint32 cnt = 0;
    switch (m_type) {
        case E_GM_ITEM_PET:
            cnt = vctPet.size();
            
            break;
        case E_GM_ITEM_ITEM:
            cnt = vcttem.size();
            
            break;
        case E_GM_ITEM_RUNE:
            cnt = vctRune.size();
           
            break;
        case E_GM_ITEM_EQUIP:
            cnt = vctEquip.size();
          
            break;
        case E_GM_ITEM_EMBLEM:
            cnt = vctEmblem.size();
            
            break;
            
        default:
            break;
    }
    
    if (cnt % 5 > 0) {
        n = cnt / 5 + 1;
    }
    else
    {
        n =  cnt / 5;
    }
    return n;
}

void CcbGmItemLayer::onSelected(cocos2d::CCObject* pSender, cocos2d::extension::CCControlEvent event)
{
    uint32 petId = ((CCScrollButton*)pSender)->getTag();
    std::string name = "";
    switch (m_type) {
        case E_GM_ITEM_PET:
            name = mapPet[petId].strName;
//            m_pLayerInsert_Lv->setVisible(true);
            break;
        case E_GM_ITEM_ITEM:
//            petId = E_UNITE_TYPE_ITEM* E_UINTE_BASE_FABIO + petId;
            name = mapItem[petId].strName;
//            m_pLayerInsert_Lv->setVisible(false);
            break;
        case E_GM_ITEM_RUNE:
            //            mapPet = GET_CONFIG_MAP();
//            petId = E_UNITE_TYPE_Rune * E_UINTE_BASE_FABIO + petId;
            name = mapRune[petId].strName;
//            m_pLayerInsert_Lv->setVisible(false);
            break;
        case E_GM_ITEM_EQUIP:
            name = mapEquip[petId].strName;
            break;
        case E_GM_ITEM_EMBLEM:
            name = mapEmblem[petId].strName;
            break;
            
        default:
            break;
    }
    CCString *str = CCString::createWithFormat("%u", petId);
    m_pLabelTTFId->setString(str->getCString());
    m_pLabelTTFName->setString(name.c_str());
    
}


CCString*  CcbGmItemLayer::getGmString()
{
    CCString*  str = CCString::create("");
    uint8 lv = m_pLayerInsert_Lv->getNum();
    if (lv == 0) {
        lv = 1;
    }
    std::string id = m_pLabelTTFId->getString();
    uint32 cnt = m_pLayerInsert_Cnt->getNum();
    switch (m_type) {
        case E_GM_ITEM_PET:
            str->initWithFormat("addpet %s %d %u", id.c_str(), lv, cnt);
            break;
        case E_GM_ITEM_ITEM:
            str->initWithFormat("additem %s %u", id.c_str(), cnt);
            break;
        case E_GM_ITEM_RUNE:
            str->initWithFormat("addrunes %s %u", id.c_str(), cnt);
            break;
        case E_GM_ITEM_EQUIP:
            str->initWithFormat("addequip %s %u", id.c_str(), cnt);
            break;
        case E_GM_ITEM_EMBLEM:
            str->initWithFormat("addemblem %s %u", id.c_str(), cnt);
            break;
            
        default:
            break;
    }
    return str;
}

