//
//  XMLParse.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-5-14.}
//
//

#ifndef __HelloWorld__XMLParse__
#define __HelloWorld__XMLParse__

#include <iostream>
#include "cocos2d.h"
#include <stack>

USING_NS_CC;

class XMLParse : public CCSAXDelegator {
    
public:
    XMLParse();
    ~XMLParse();
    
    CCDictionary* dictionaryWithContentsOfFile(const char* pFileName);
    CCDictionary* dictionaryWithContentsOfData(const char* pData, unsigned int uLength);
    CCArray* arrayWithContentsOfFile(const char* pFileName);
    CCArray* arrayWithContentsOfData(const char* pData, unsigned int uLength);
    
    virtual void startElement(void *ctx, const char *name, const char **atts);
    virtual void endElement(void *ctx, const char *name);
    virtual void textHandler(void *ctx, const char *s, int len);
    
    typedef enum
    {
        SAX_NONE = 0,
        SAX_KEY,
        SAX_DICT,
        SAX_INT,
        SAX_REAL,
        SAX_STRING,
        SAX_ARRAY
    }CCSAXState;
    
    typedef enum
    {
        SAX_RESULT_NONE = 0,
        SAX_RESULT_DICT,
        SAX_RESULT_ARRAY
    }CCSAXResult;
    
public:
    CCSAXResult m_eResultType;
    CCArray* m_pRootArray;
    CCDictionary *m_pRootDict;
    CCDictionary *m_pCurDict;
    std::stack<CCDictionary*> m_tDictStack;
    std::string m_sCurKey;   ///< parsed key
    std::string m_sCurValue; // parsed value
    CCSAXState m_tState;
    CCArray* m_pArray;
    
    
    std::stack<CCArray*> m_tArrayStack;
    std::stack<CCSAXState>  m_tStateStack;
};

#endif /* defined(__HelloWorld__XMLParse__) */
