//
//  CCScrollViewWithBar.cpp
//  HelloWorld
//
//  Created by long on 13-11-25.
//
//

#include "CCScrollViewWithBar.h"
#include "UISupport.h"

#define defaultBarBg    "ccbresources/12monthdate/universal/scrollbar_bg.png"
#define defaultBar  "ccbresources/12monthdate/universal/scrollbar_btn.png"

CCScrollViewWithBar::CCScrollViewWithBar()
{
    
}
CCScrollViewWithBar::~CCScrollViewWithBar()
{
    
}


//CCScrollViewWithBar* CCScrollViewWithBar::create()
//{
//    CCScrollViewWithBar* pRet = new CCScrollViewWithBar();
//    if (pRet && pRet->init())
//    {
//        pRet->autorelease();
//    }
//    else
//    {
//        CC_SAFE_DELETE(pRet);
//    }
//    return pRet;
//}

CCScrollViewWithBar* CCScrollViewWithBar::create(CCScrollView *scrollview)
{
    CCScrollViewWithBar* pRet = new CCScrollViewWithBar();
    if (pRet && pRet->init(scrollview))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

//bool CCScrollViewWithBar::init()
//{
//    return this->init(NULL);
//}
bool CCScrollViewWithBar::init(CCScrollView *scrollview)
{
//    setTouchEnabled(true);
    if (!CCLayer::init()) {
        return false;
    }
    if (!scrollview) {
        return false;
    }
    
    m_scrollview = scrollview;
    setContentSize(CCSizeMake(320, 480));
    this->setContentSize(scrollview->getViewSize());
    
    addChild(m_scrollview);
    
//    if (m_scrollview->getViewSize().height >= m_scrollview->getContentSize().height) {
//        return true;
//    }
    
    setScrollBar(defaultBarBg, defaultBar, 2, 2);
    m_barBg->setPosition(ccp(getContentSize().width - 2, getContentSize().height * 0.5));
    m_barBg->setAnchorPoint(ccp(1, 0.5));
    addChild(m_barBg, 10);
    
    m_bar->setPosition(ccp(getWidth(this) - 2,  getHeight(this) - getHeight(m_bar) - m_top));
    m_bar->setAnchorPoint(ccp(1, 0));
    addChild(m_bar, 11);
    
    schedule(schedule_selector(CCScrollViewWithBar::update));
    
    return true;
}
void CCScrollViewWithBar::checkIsShow()
{
    if (m_scrollview->getViewSize().height >= m_scrollview->getContentSize().height) {
        m_barBg->setVisible(false);
        m_bar->setVisible(false);
        unschedule(schedule_selector(CCScrollViewWithBar::update));
        return;
    }
    float h = (m_scrollview->getViewSize().height / m_scrollview->getContentSize().height) * getHeight(m_barBg);
    m_bar->setScaleY(1);
    if (h > getHeight(m_bar)) {
        m_bar->setScaleY(h / getHeight(m_bar));
    }
}
void CCScrollViewWithBar::onEnter()
{
    CCLayer::onEnter();
//    scrollBar(m_scrollview);
    
}

void CCScrollViewWithBar::setScrollBar(std::string barBgFile, std::string barFile, float top, float bottom)
{
    m_top = top;
    m_bottom = bottom;
    
    m_barBg = CCSprite::create(barBgFile.c_str());
    if (!m_barBg) {
        m_barBg = CCSprite::create(defaultBarBg);
        m_top =  2.0f;
        m_bottom = 2.0f;
    }
    
    m_bar = CCSprite::create(barFile.c_str());
    if (!m_bar) {
        m_bar = CCSprite::create(defaultBar);
    }
    m_barBg->setScaleY((getHeight(this) - top - bottom) / getHeight(m_barBg));
//    float h = (m_scrollview->getViewSize().height / m_scrollview->getContentSize().height) * getHeight(m_barBg)*m_barBg->getScaleY();
//    if (h > getHeight(m_bar)) {
//        m_bar->setScaleY(h / getHeight(m_bar));
//    }
}

void CCScrollViewWithBar::update(float tiem)
{
    scrollBar(m_scrollview);
}


void CCScrollViewWithBar::scrollBar(CCScrollView* view)
{
    if (!m_scrollview) {
        return;
    }
    // tableSize.height == cell个数*cell的height}
    CCSize tableSize = view->getContentSize();
    // CCTableView
    CCSize tableViewSize = view->getViewSize();
    // 每次拖动的偏移量？(负值)}
    CCPoint contOffsetPos = view->getContentOffset();
    
    // 总的偏移量}
    float maxOff = tableViewSize.height - tableSize.height;
    // 每次拖动的偏移量}
    float curOff = contOffsetPos.y - maxOff;
    // 计算百分比}
    float percentage =  curOff / fabs(maxOff);//fabs(curOff)/fabs(maxOff);
    
//    printf("curOff:%f, maxOff:%f, per:%f\n", curOff, maxOff, percentage);
    
    // 拖拉到最顶端或最低端后继续拖动(弹回)会出现percentage值小于0.1和大于1.0的情况，我们分别把percentage重置为0和1.0f}
    if(percentage < 0.01f)
    {
        percentage = 0;
    }
    if(percentage > 1.0f)
    {
        percentage = 1.0f;
    }
    
    // bar移动到最顶端的position.y}
    float barTopPosY = getHeight(m_barBg) - getHeight(m_bar) - m_top;
    // bar移动到最低端的position.y}
    float barLowPosY = m_bottom;
    // ....
    float h = barTopPosY - percentage*(barTopPosY- barLowPosY);;
    
    m_bar->setPositionY(h);
}






CCTableViewWithBar::CCTableViewWithBar()
{
    
}
CCTableViewWithBar::~CCTableViewWithBar()
{
    
}


CCTableViewWithBar* CCTableViewWithBar::create(CCTableView *tableview)
{
    CCTableViewWithBar* pRet = new CCTableViewWithBar();
    if (pRet && pRet->init(tableview))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CCTableViewWithBar::init(CCTableView *tableview)
{

    if (!CCLayer::init()) {
        return false;
    }
    if (!tableview) {
        return false;
    }
    
    m_tableview = tableview;
    setContentSize(CCSizeMake(320, 480));
    m_tableview->setBounceable(true);
    m_tableview->setPosition(CCPointZero);
    m_tableview->setAnchorPoint(CCPointZero);
    this->setContentSize(m_tableview->getViewSize());
    
    addChild(m_tableview);
    
    setScrollBar(defaultBarBg, defaultBar, 0, 0);
    m_barBg->setPosition(ccp(getWidth(this) - 2, getContentSize().height * 0.5));
    m_barBg->setAnchorPoint(ccp(1, 0.5));
    addChild(m_barBg, 10);
    
    m_bar->setPosition(ccp(getWidth(this) - 2,  getHeight(this) - getHeight(m_bar) - m_top));
    m_bar->setAnchorPoint(ccp(1, 0));
    addChild(m_bar);
    
    schedule(schedule_selector(CCTableViewWithBar::update));
    
    return true;
}
void CCTableViewWithBar::checkIsShow(int num, CCSize cellSize)
{
    if (m_tableview->getViewSize().height >= num * cellSize.height) {
        m_barBg->setVisible(false);
        m_bar->setVisible(false);
        m_tableview->setBounceable(false);
        unschedule(schedule_selector(CCTableViewWithBar::update));
        return;
    }
    m_tableview->setBounceable(true);
    float h = (m_tableview->getViewSize().height / (num * cellSize.height)) * getHeight(m_barBg);
    m_bar->setScaleY(1);
    if (h > getHeight(m_bar)) {
        m_bar->setScaleY(h / getHeight(m_bar));
    }
}
void CCTableViewWithBar::onEnter()
{
    CCLayer::onEnter();
    //    scrollBar(m_scrollview);
    
}

void CCTableViewWithBar::setScrollBar(std::string barBgFile, std::string barFile, float top, float bottom)
{
    m_top = top;
    m_bottom = bottom;
    
    m_barBg = CCSprite::create(barBgFile.c_str());
    if (!m_barBg) {
        m_barBg = CCSprite::create(defaultBarBg);
        m_top = 0.0f;
        m_bottom = 0.0f;
    }
    
    m_bar = CCSprite::create(barFile.c_str());
    if (!m_bar) {
        m_bar = CCSprite::create(defaultBar);
    }
    m_barBg->setScaleY((getHeight(this)-top-bottom) / getHeight(m_barBg));
}


void CCTableViewWithBar::scrollBar(CCTableView* view)
{
    if (!m_tableview) {
        return;
    }
    // tableSize.height == cell个数*cell的height}
    CCSize tableSize = view->getContentSize();
    // CCTableView
    CCSize tableViewSize = view->getViewSize();
    // 每次拖动的偏移量？(负值)}
    CCPoint contOffsetPos = view->getContentOffset();
    
    // 总的偏移量}
    float maxOff = tableViewSize.height - tableSize.height;
    // 每次拖动的偏移量}
    float curOff = contOffsetPos.y - maxOff;
    // 计算百分比}
    float percentage = curOff/fabs(maxOff);
    
    //    printf("curOff:%f, maxOff:%f, per:%f\n", curOff, maxOff, percentage);
    
    // 拖拉到最顶端或最低端后继续拖动(弹回)会出现percentage值小于0.1和大于1.0的情况，我们分别把percentage重置为0和1.0f}
    if(percentage < 0.01f)
    {
        percentage = 0;
    }
    if(percentage > 1.0f)
    {
        percentage = 1.0f;
    }
    
    // bar移动到最顶端的position.y}
    float barTopPosY = getHeight(m_barBg) - getHeight(m_bar);
    // bar移动到最低端的position.y}
    float barLowPosY = m_bottom;
    // ....
    float h = barTopPosY - percentage*(barTopPosY- barLowPosY);;
    
    m_bar->setPositionY(h);
}

void CCTableViewWithBar::update(float tiem) {
        scrollBar(m_tableview);
};

