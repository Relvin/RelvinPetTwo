//
//  ReRichText.cpp
//  HelloWorld
//
//  Created by Relvin on 14-5-14.
//
//

/***************************************************************************************************************
 USAGE:
 
 *从带颜色的转义字符串中析取分段颜色字符串。:  |cAARRGGBB + |s00(fontSize) + string|r + [/1...52]
 * Eg:  |cff88888812中国|cffffffff06人|r民[/1]
 * 		返回
 
 
 EXAMPLE :
 
 std::string reRichStr = "幻|cff888888|s20想|cffff00006精|r灵[/1]";
 ReRichText *reRichText = ReRichText::create(reRichStr.c_str(),15,"Thonburi",CCSizeMake(100, 0));
 this->addChild(reRichText,100);
 reRichText->setPosition(ccp(winSize.width / 2, winSize.height / 2));
 ****************************************************************************************************************/



#include "ReRichText.h"
#include "GlobalData.h"
#include <string>


int _calcCharCountUTF(const char * pszText)
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

bool _checkIsCharEnd(char curChr)
{
    if (0x80 != (0xC0 & curChr))
    {
        return true;
    }
    return false;
}

int richTextFontSize(char size1,char size2,char size3)
{
    if (size2 == 0) {
        size2 = size1;
    }
    if (size3 == 0) {
        size3 = size2;
    }
    return size1 << 16 | size2 << 8 | size3;
}

const char * fontJudge(const char *fontName)
{
    if (fontName == NULL || strlen(fontName) == 0) {
        return " ";
    }
    return fontName;
}

const char *richTextFontName(const char *fontName1,const char *fontName2,const char *fontName3)
{
    CCString *fontName = CCString::createWithFormat("%s|%s|%s",fontJudge(fontName1),fontJudge(fontName2),fontJudge(fontName3));
    return fontName->getCString();
}


ReRichText *ReRichText::create()
{
    ReRichText* widget = new ReRichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

ReRichText *ReRichText::create(const char *string,const char *fontName, float fontSize, const cocos2d::CCSize &dimensions,CCTextAlignment hAlignment)
{
    ReRichText* widget = new ReRichText();
    if (widget && widget->init(string,fontName,fontSize,dimensions, hAlignment))
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

ReRichText::ReRichText()
: _fontColor(ccWHITE)
, _fontSize(0)
, _fontName("Helvetica")
, _reTag(0)
, _delegate(NULL)
{
    
}

ReRichText::~ReRichText()
{
    _string.clear();
    _vecList.clear();
    _fontName.clear();
}

bool ReRichText::init()
{
    return this->init("","Helvetica", 12);
}

bool ReRichText::init(const char *string,const char *fontName,float fontSize,
                      const CCSize& dimensions,CCTextAlignment hAlignment )
{
    if (!RichText::init()) {
        return false;
    }
    
    // RichText}
    if (dimensions.equals(CCSizeMake(0, 0))) {
        this->ignoreContentAdaptWithSize(true);
    }
    else
    {
        this->ignoreContentAdaptWithSize(false);
    }
    
    _fontSize = fontSize;
    _fontName = fontName;
    _hAlignment = hAlignment;
    
    this->setSize(dimensions);
    this->setString(string);
    
    return true;
}

void ReRichText::parserStringWithAnyType()
{
    _richElements->removeAllObjects();
    _reTag = _vecList.size();
    for (int i = 0; i < _vecList.size(); i ++) {
        RichElement *richElement = NULL;
        float fontSize = _fontSize;
        if (_vecList[i]._fontSize >= 1.0f ) {
            fontSize = _vecList[i]._fontSize;
        }
        switch (_vecList[i]._type) {
            case enum_LabelTTF:
            {
                richElement = RichElementText::create(i, _vecList[i]._color, _vecList[i]._opacity, _vecList[i]._content.c_str(), _fontName.c_str(), fontSize,_vecList[i]._objId,_delegate);
                if (_vecList[i]._objId || _vecList[i]._delegateFlag) {
                    richElement->setIsDelegateElement(true);
                }
                break;
            }
            case enum_Icon:
            {
                richElement = RichElementImage::create(i, ccWHITE, _vecList[i]._opacity, _vecList[i]._content.c_str());
                break;
            }
            default:
                break;
        }
        if (richElement) {
            this->pushBackElement(richElement);
        }
    }
    this->formatText();
    
}

typedef wchar_t WCHAR;
#if CC_TARGET_PLATFORM != CC_PLATFORM_WP8 && CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
typedef unsigned int DWORD;
#endif


inline GLubyte opacity_color(unsigned int cc)
{
    return (cc & 0xff000000) >> 24;
}

inline ccColor3B ccc3_color(unsigned int cc)
{
    GLubyte r = (cc & 0xff0000) >> 16;
    GLubyte g = (cc & 0xff00) >> 8;
    GLubyte b = (cc & 0xff);
    
    return ccc3(r, g, b);
    
}

inline ccColor4B ccc4_color(unsigned int cc)
{
    GLubyte a = (cc & 0xff000000) >> 24;
    GLubyte r = (cc & 0xff0000) >> 16;
    GLubyte g = (cc & 0xff00) >> 8;
    GLubyte b = (cc & 0xff);
    
    return ccc4(r, g, b,a);
    
}

inline unsigned int argb_ccc3(ccColor3B cc)
{
    return (0xFF000000 | (cc.r << 16) | (cc.g << 8) | (cc.b)) ;
}

inline unsigned int argb_ccc4(ccColor4B cc)
{
    return (0x00000000 | (cc.a << 24) | (cc.r << 16) | (cc.g << 8) | (cc.b)) ;
}


void ReRichText::formatString(const char* pString ,ccColor4B color , const char *pFontName ,float fontsize ,int roleId ,ReLinkTextDelegate *delegate ,bool forceDelegate)
{
    
	DWORD dwDefColor = argb_ccc3(_fontColor);
    std::string string;
    bool defStrFlag = false;
    std::string fontName = _fontName;
    if (pFontName) {
        fontName = pFontName;
    }
    float fontSize = fontsize;
    int nObjId = roleId;
    if (pString == NULL) {
        string = _string;
        defStrFlag = true;
    }
    else
    {
        string = pString;
        dwDefColor = argb_ccc4(color);
    }
    const char *pSrcText = string.c_str();
	int cch = string.length();
    
	char  subStrbuf[4096] = "\0";
	int   nChars = 0;
    bool  customColorFlag = false;
	DWORD dwCurrColor = dwDefColor;
    
	char *pDest = subStrbuf;
	for(int i = 0; i < cch; i++)
	{
		//如果是颜色定位...}
        
		if(pSrcText[i] == L'|' && i + 1 < cch)
		{
			if(pSrcText[i + 1] == L'r')
			{
				if(nChars > 0)
				{
                    addSubString(subStrbuf,nChars,dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
                    customColorFlag = false;
                    if (defStrFlag) {
                        fontSize = 0;
						nObjId = roleId;
                    }
                    memset(subStrbuf, '\0', sizeof(subStrbuf));
					nChars = 0;
				}
				dwCurrColor = dwDefColor;
				i ++;
				pDest = subStrbuf;
				continue;
			}
            else if (pSrcText[i + 1] == L'l')
            {
                int n = 0;
                int objId = 0;
                for (n = i + 2; n < cch ; n++) {
                    if (pSrcText[n] <= '9' && pSrcText[n] >= '0') {
                        objId = objId * 10 + pSrcText[n] - '0';
                    }
                    else
                    {
                        break;
                    }
                }
                nObjId = objId;
                if (nObjId != 0) {
                    i = n;
                }
            }
			else if(pSrcText[i + 1] == L'c' )
			{
				int n;
				DWORD dwValue = 0;
				for( n = i + 2 ; n < i + 10 && i + 9 < cch; n++)
				{
					char c = pSrcText[n];
					if(c >= '0' &&  c <= '9')
						dwValue = dwValue * 16 + c - '0';
					else if(c >= 'A' &&  c <= 'F')
						dwValue = dwValue * 16 + c - 'A' + 10;
					else if(c >= 'a' &&  c <= 'f')
						dwValue = dwValue * 16 + c - 'a' + 10;
					else
						break;
				}
				if(dwValue == 0)
                {
                    std::ostringstream streamBuf;
                    streamBuf.str("");
                    for( n = i + 2 ; n < cch ; n++)
                    {
                        char c = pSrcText[n];
                        if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')) {
                            streamBuf << c;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if ( streamBuf.str().length() > 0) {
                        dwValue = argb_ccc4(GlobalData::shared()->getColorByKey(streamBuf.str().c_str()));
                        if (pSrcText[n] == ' ') {
                            n++;
                        }
                    }
                }
				if (dwValue)
                {
					if(nChars > 0)
					{
                    
                        addSubString(subStrbuf,nChars,dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
                        customColorFlag = false;
                        fontSize = fontsize;
                        nObjId = roleId;
						nChars = 0;
                        memset(subStrbuf, '\0', sizeof(subStrbuf));
					}
                    customColorFlag = true;
					dwCurrColor = dwValue;
                    
					i = n - 1;
                    
					pDest = subStrbuf;
					continue;
				}
			}
            else if(pSrcText[i + 1] == L's')
            {
                float fontSizeT = 0;
                int n = 0;
                for( n = i + 2 ; n < i + 4; n++)
                {
                    char c = pSrcText[n];
                    if (c >= '0' && c <= '9') {
                        fontSizeT = fontSizeT * 10 + c - '0';
                    }
                    else
                        break;
                }
                if(fontSizeT != 0)
				{
					if(nChars > 0)
					{
                        
                        addSubString(subStrbuf,nChars,dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
                        customColorFlag = false;
						nChars = 0;
                        memset(subStrbuf, '\0', sizeof(subStrbuf));
					}
                    fontSize = fontSizeT;
                    
					i = n - 1;
                    
					pDest = subStrbuf;
					continue;
				}
            }
		}
        else if (pSrcText[i] == L'\r')
        {
            continue;
        }
        else if (pSrcText[i] == L'[' && ((i + 3 < cch && pSrcText[i + 3] == L']') || ((i + 4 < cch) && pSrcText[i + 4] == ']')))
        {
            if (pSrcText[i+1] == L'/') {
                int imgIdx = 0;
                int n = 0;
                bool picFlag = false;
                for (n = i + 2; n < cch && pSrcText[n] != L']'; n++) {
                    if (pSrcText[n] <= '9' && pSrcText[n] >= '0') {
                        imgIdx = imgIdx * 10 + pSrcText[n] - '0';
                        picFlag = true;
                    }
                    else
                    {
                        picFlag = false;
                        break;
                    }
                }
                if (imgIdx > 0 && imgIdx <= 52 && picFlag) {
                    if (nChars > 0) {
                        addSubString(subStrbuf, nChars, dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
                        nChars = 0;
                        memset(subStrbuf, '\0', sizeof(subStrbuf));
                    }
                    char chPath[256] = "\0";
                    sprintf(chPath, "%d.png",imgIdx);
                    addSubString(chPath, sizeof(chPath), dwCurrColor,fontName.c_str(),fontSize,false,enum_Icon,defStrFlag);
                    pDest = subStrbuf;
                    i = n ;
                    continue;
                }
                else
                {
                    imgIdx = 0;
                }
            }
        }
        else if(_calcCharCountUTF(subStrbuf) > 100 && _checkIsCharEnd(pSrcText[i]))
        {
            if(nChars > 0)
            {
                addSubString(subStrbuf,nChars,dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
                memset(subStrbuf, '\0', sizeof(subStrbuf));
                nChars = 0;
            }
            pDest = subStrbuf;
            i--;
            continue;
        }
		*pDest++ =  pSrcText[i];
		nChars ++;
	}
    
	if(nChars > 0)
	{
        addSubString(subStrbuf,nChars,dwCurrColor,fontName.c_str(),fontSize,customColorFlag,enum_LabelTTF,defStrFlag,nObjId,delegate,forceDelegate);
        customColorFlag = false;
        memset(subStrbuf, '\0', sizeof(subStrbuf));
	}
    
}

void ReRichText::addSubString(const char *str,int n,unsigned int color,const char *fontName,float fontSize,bool customColorFlag,int strType , bool defStrFlag,int roleId ,ReLinkTextDelegate *delegate ,bool forceDelegate)
{
    ReRichTextList info;
    
	char buf[4096];
	memcpy(buf,str,n);buf[n] = 0;

    info._type = strType;
    info._content = buf;
    info._fontName = fontName;
    info._color = ccc3_color(color);
    info._fontSize = fontSize;
    info._customColorFlag = customColorFlag;
    info._opacity = opacity_color(color);
    info._objId = roleId;
    if (roleId || delegate || forceDelegate) {
        info._delegateFlag = true;
    }
    else
    {
        info._delegateFlag = false;
    }
    
    if (defStrFlag) {
        _vecList.push_back(info);
    }
    else
    {
        this->addBackElement(&info,roleId,delegate);
    }
    
}

void ReRichText::clearSubStrings()
{
    _vecList.clear();
}

void ReRichText::setColor(ccColor3B color)
{
    if (!ccc3BEqual(_fontColor, color)) {
        _fontColor = color;
        this->updateColor();
    }
}

bool ReRichText::updateColor()
{
    for (int i = 0; i < _vecList.size(); i++) {
        if (!_vecList[i]._customColorFlag) {
            _vecList[i]._color = _fontColor;
        }
    }
    this->updateTexture();
    return true;
}

void ReRichText::setString(const char *string)
{
    if (_string.compare(string))
    {
        _string = string;
        this->updateTexture();
    }
}

void ReRichText::addString(const char *label)
{
    this->formatString(label);
}

bool ReRichText::updateTexture()
{
    this->clearSubStrings();
    this->formatString();
    this->parserStringWithAnyType();
    return true;
}

void ReRichText::addChatMsg(
                            ccColor4B channalColor,
                            const char *channal,
                            ccColor4B nameColor,
                            const char *name,
                            int roleId,
                            ccColor4B textColor,
                            const char *text,
                            const char *fontName,
                            int fontSize,
                            cocos2d::ui::ReLinkTextDelegate *delegate
                            )
{
    std::string fontStr = fontName;
    char *channalFont = NULL;
    char *nameFont = NULL;
    char *textFont = NULL;
    char fontBuf[256] = "\0";

    memcpy(fontBuf, fontStr.c_str(), fontStr.length());
    channalFont = strtok(fontBuf, "|");
    if (channalFont == NULL) {
        channalFont = fontBuf;
    }
    nameFont = strtok(NULL, "|");
    if (nameFont == NULL || strcmp(nameFont, " ") == 0) {
        nameFont = channalFont;
    }
    
    textFont = strtok(NULL, "|");
    if (textFont == NULL|| strcmp(textFont, " ") == 0) {
        textFont = nameFont;
    }
    
    int textSize = fontSize & 0xff;
    int nameSize = fontSize >> 8 & 0xff;
    int channalSize = fontSize >> 16 & 0xff;
    
    if (nameSize == 0) {
        nameSize = textSize;
    }
    
    if (channalSize == 0) {
        channalSize = nameSize;
    }
    
    this->formatString(channal,channalColor,channalFont,channalSize);
    _reTag ++;
    this->formatString(name,nameColor,nameFont,nameSize,roleId,delegate,true);
    _reTag ++;
    this->formatString(text,textColor,textFont,textSize);
    this->addNewLine();
    this->formatText();
}



void ReRichText::addBackElement(const ReRichTextList *info,int roleId ,ReLinkTextDelegate *delegate )
{
    RichElement *richElement = NULL;
    
    switch (info->_type) {
        case enum_LabelTTF:
        {
            richElement = RichElementText::create(_reTag, info->_color, info->_opacity,info->_content.c_str(), info->_fontName.c_str(), info->_fontSize,roleId,delegate);
            if (delegate || info->_delegateFlag) {
                richElement->setIsDelegateElement(true);
            }
            break;
        }
        case enum_Icon:
        {
            richElement = RichElementImage::create(_reTag, ccWHITE, info->_opacity,info->_content.c_str());
            break;
        }
        default:
            break;
    }
    if (richElement) {
        this->pushBackElement(richElement);
    }
    _reTag ++;
}

void ReRichText::setDelegate(cocos2d::ui::ReLinkTextDelegate *delegate)
{
    _delegate = delegate;
    for (int i = 0 ; i < _richElements->count(); i++) {
        RichElement* element = static_cast<RichElement*>(_richElements->objectAtIndex(i));
        switch (element->getType())
        {
            case RICH_TEXT:
            {
                if (element->isDelegateElement()) {
                    RichElementText* elmtText = static_cast<RichElementText*>(element);
                    if (elmtText)
                    {
                        elmtText->setDelegate(delegate);
                    }
                }
                
            }
                break;
            default:
                break;
        }
    }
    this->updateFormatText();
}


void ReRichText::setFontName(const char *fontName)
{
    _fontName = fontName;
}

void ReRichText::setFontSize(float size)
{
    _fontSize = size;
}


