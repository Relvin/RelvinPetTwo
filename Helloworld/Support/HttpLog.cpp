//
//  HttpLog.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 14-2-8.}
//
//

#include "HttpLog.h"

const static string m_strUrl = "172.16.1.107:8888/upload?";

HttpLog* HttpLog::m_pShared = NULL;

HttpLog::HttpLog() {
    
}

HttpLog::~HttpLog() {
    m_pShared = NULL;
}

bool HttpLog::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    m_pShared = this;
    m_pReqDic = CCDictionary::create();
    m_pReqDic->retain();
    return true;
}

HttpLog* HttpLog::GetInstance() {
    if (!m_pShared) {
        m_pShared = HttpLog::create();
    }
    return m_pShared;
}

void HttpLog::onExit() {
    if (m_pReqDic) {
        m_pReqDic->release();
    }
}

void HttpLog::onRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {
    if (!response) {
        return;
    }
    if (0 != strlen(response->getHttpRequest()->getTag())) {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    int sCode = response->getResponseCode();
//    char sString[64] = {};
//    sprintf(sString, "Code: %d, tag: %s", sCode, response->getHttpRequest()->getTag());
    CCLog("Code: %d, tag: %s", sCode, response->getHttpRequest()->getTag());
    if (!response->isSucceed()) {
        // 访问失败}
        CCLog("error msg: %s", response->getErrorBuffer());
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    for (int i = 0; i < buffer->size(); i++) {
        CCLog("%c", (*buffer)[i]);
    }
}

#pragma mark Public
void HttpLog::addLogInfo(string key, string value) {
    CCString* pValue = CCString::create(value);
    m_pReqDic->setObject(pValue, key);
}

void HttpLog::sendLogInfo() {
    string strUrl = m_strUrl;
    bool bFirst = true;
    
    CCDictElement* pElement;
    CCDICT_FOREACH(m_pReqDic, pElement) {
        string key = pElement->getStrKey();
        CCString* pValue = (CCString*)pElement->getObject();
        if (bFirst) {
            bFirst = false;
            strUrl += key + "=" + pValue->getCString();
        } else {
            strUrl += "&" + key + "=" + pValue->getCString();
        }
    }
    
    CCHttpRequest* request = new CCHttpRequest();
    CCLog("url = %s", strUrl.c_str());
    request->setUrl(strUrl.c_str());
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(HttpLog::onRequestCompleted));
    request->setTag("Log Test");
    
    CCHttpClient::getInstance()->send(request);
}

