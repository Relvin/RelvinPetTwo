//
//  CCScrollViewWithBar.h
//  HelloWorld
//
//  Created by long on 13-11-25.
//
//

#ifndef __HelloWorld__CCScrollViewWithBar__
#define __HelloWorld__CCScrollViewWithBar__
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCScrollViewWithBar : public CCLayer
{
public:
    CCScrollViewWithBar();
    ~CCScrollViewWithBar();
    
    //把要加滚动条的scrollView传入，scrollview需设置好contantSize（暂时只支持竖向）}
    static CCScrollViewWithBar* create(CCScrollView *scrollview);

//    static CCScrollViewWithBar* create();
//    bool init();
    bool init(CCScrollView *scrollview);
    
    /*
     设置滚动条}
     barBgFile : 滚动条背景图}
     barFile：滚动条图}
     top ：滚动条上边缘余白}
     bottom：滚动条下边缘余白}
     */
    void setScrollBar(std::string barBgFile, std::string barFile, float top, float bottom);
    void checkIsShow();
    virtual void onEnter();
    
private:
    CCSprite *m_barBg;
    CCSprite *m_bar;
    CCScrollView *m_scrollview;
    float m_top;
    float m_bottom;
private:
    void scrollBar(CCScrollView* view);
    void update(float tiem);
};

#pragma mark TableView  With  Bar
class CCTableViewWithBar : public CCLayer
{
public:
    CCTableViewWithBar();
    ~CCTableViewWithBar();
    
    //把要加滚动条的scrollView传入，scrollview需设置好contantSize（暂时只支持竖向）}
    static CCTableViewWithBar* create(CCTableView *tableview);
    
    //    static CCScrollViewWithBar* create();
    //    bool init();
    bool init(CCTableView *tableview);
    
    /*
     设置滚动条}
     barBgFile : 滚动条背景图}
     barFile：滚动条图}
     top ：滚动条上边缘余白}
     bottom：滚动条下边缘余白}
     */
    void setScrollBar(std::string barBgFile, std::string barFile, float top, float bottom);
    
//    virtual void scrollViewDidScroll(CCScrollView* view) ;}
//    virtual void scrollViewDidZoom(CCScrollView* view) {};
//    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell) {};
    virtual void onEnter();
    
    void checkIsShow(int num, CCSize cellSize);
private:
    CCSprite *m_barBg;
    CCSprite *m_bar;
    CCTableView *m_tableview;
    float m_top;
    float m_bottom;
private:
    void scrollBar(CCTableView* view);
    void update(float tiem);
};

#endif /* defined(__HelloWorld__CCScrollViewWithBar__) */
