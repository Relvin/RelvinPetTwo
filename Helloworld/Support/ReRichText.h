//
//  ReRichText.h
//  HelloWorld
//
//  Created by Relvin on 14-5-14.
//
//

#ifndef __HelloWorld__ReRichText__
#define __HelloWorld__ReRichText__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

enum TextType
{
    enum_LabelTTF = 0,
    enum_Icon,
    enum_Animate,
};

struct ReRichTextList{
    int         _type;
    std::string _content;
    std::string _fontName;
    float       _fontSize;
    ccColor3B   _color;
    bool        _customColorFlag;
    GLubyte     _opacity;
    bool        _delegateFlag;
	int         _objId;
    bool        _isStroke;
};

int richTextFontSize(
                     char size1,
                     char size2 = 0,
                     char size3 = 0
                     );
const char *richTextFontName(
                             const char *fontName1,
                             const char *fontName2 = NULL,
                             const char *fontName3 = NULL
                             );

class ReRichText
: public RichText
{
public:
    
//    static ReRichText *create();
    static ReRichText* create();
    static ReRichText* create(
                              const char *string,
                              const char *fontName,
                              float fontSize,
                              const CCSize& dimensions = CCSizeMake(0, 0),
                              CCTextAlignment hAlignment = kCCTextAlignmentLeft
                              );
    
    void setColor(ccColor3B color);
    void setString(const char *label);
    
    void setDelegate(ReLinkTextDelegate *delegate);
    
    void addString( const char *label );
    void addBackElement(
                        const ReRichTextList *info,
                        int roleId = 0,
                        ReLinkTextDelegate *delegate = NULL
                        );
    
    void addChatMsg(
                    ccColor4B channalColor,
                    const char *channal,
                    ccColor4B nameColor,
                    const char* name,int roleId,
                    ccColor4B textColor,
                    const char *text,
                    const char *fontName,
                    int fontSize,
                    ReLinkTextDelegate *delegate = NULL
                    );
    
    void setFontName(const char* fontName);
    void setFontSize(float size);
protected:
    
    void parserStringWithAnyType();
    void formatString(
                      const char* string = NULL,
                      ccColor4B color = ccc4(0, 0, 0, 0),
                      const char *fontName = NULL,
                      float fontsize = 0,
                      int roleId = 0,
                      ReLinkTextDelegate *delegate = NULL,
                      bool forceDelegate = false
                      );
    
    void addSubString(
                      const char *s,
                      int n,
                      unsigned int color,
                      const char *fontName,
                      float fontSize,
                      bool customColorFlag,
                      int strType,
                      bool defStrFlag = true,
                      int roleId = 0,
                      ReLinkTextDelegate *delegate = NULL,
                      bool forceDelegate = false
                      );
    void addImage();
    void clearSubStrings();
    bool updateTexture();
    bool updateColor();
private:
    ReRichText();
    virtual ~ReRichText();
    bool init();
    bool init(
              const char *string,
              const char *fontName,
              float fontSize,
              const CCSize& dimensions = CCSizeMake(0, 0),
              CCTextAlignment hAlignment = kCCTextAlignmentLeft
              );
private:
    std::vector<ReRichTextList>  _vecList;
    std::string             _string;
    ccColor3B               _fontColor;
    float                   _fontSize;
    std::string             _fontName;
    int                     _reTag;
    ReLinkTextDelegate      *_delegate;
};


#endif /* defined(__HelloWorld__ReRichText__) */
