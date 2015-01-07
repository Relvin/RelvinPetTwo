#include "CcbUpdateResourceLayer.h"
//#include "CcbManager.h"
#include "FileUpdate.h"
#include "StartGameLayer.h"
#include "ServerListCtrl.h"
#include "ConfigGet.h"
#include "ResourceStringClient.h"
#include "GlobalData.h"

USING_NS_CC;
USING_NS_CC_EXT;

CcbUpdateResourceLayer::~CcbUpdateResourceLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLabelTTFTips);
    CC_SAFE_RELEASE_NULL(m_pSpriteDownload);
    CC_SAFE_RELEASE_NULL(m_pLabelGameTips);
}

//-- copy this to CcbManager 
/*
//CcbManager.h
CCNode* LoadCcbUpdateResourceLayer( CCObject* owner );

//CcbManager.cpp
CCNode* CcbManager::LoadCcbUpdateResourceLayer( CCObject* owner ) {
	CCNodeLoaderLibrary* pLoaderLib = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
	pLoaderLib->registerCCNodeLoader( "CcbUpdateResourceLayer", CcbUpdateResourceLayerLoader::loader() );
	
    
	CCBReader* pCCBReader = new CCBReader(pLoaderLib);
	CCNode* pNode = pCCBReader->readNodeGraphFromFile("ccb/update_resource.ccbi", owner);
	pCCBReader->release();

	return pNode;
}
*/

static int repeat = 0;

bool CcbUpdateResourceLayer::init()
{
	// First be called.
	if (!CCLayer::init()) {
		return false;
	}
	// code here
    setTouchEnabled(true);
    
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
//    m_pLabelTTFTips = CCLabelTTF::create("Update.....---....", T_Font, 14.0, CCSize(400, 0), kCCTextAlignmentCenter, true);
//    m_pLabelTTFTips->setColor(ccWHITE);
//    m_pLabelTTFTips->setAnchorPoint(ccp(0.5, 0.5));
//    m_pLabelTTFTips->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
//    addChild(m_pLabelTTFTips, 10);
    
	return true;
}

void CcbUpdateResourceLayer::onEnter()
{
	CCLayer::onEnter();
	//在scene()之后被调用}
	//这里可以定义进入场景的初始化，比如控件的初始位置，初始状态等}
    startUpdate();
}

void CcbUpdateResourceLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void CcbUpdateResourceLayer::onExit()
{
	CCLayer::onExit();
}

void CcbUpdateResourceLayer::onExitTransitionDidStart()
{
	CCLayer::onExitTransitionDidStart();
}

void CcbUpdateResourceLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool CcbUpdateResourceLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

// Inhert MemberVariableAssigner
bool CcbUpdateResourceLayer::onAssignCCBMemberVariable( CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode )
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelTTFTips", CCLabelTTF*, this->m_pLabelTTFTips);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pSpriteDownload", CCSprite*, this->m_pSpriteDownload);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_pLabelGameTips", CCLabelTTF*, this->m_pLabelGameTips);
	return false;
}

bool CcbUpdateResourceLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
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
SEL_CallFuncN CcbUpdateResourceLayer::onResolveCCBCCCallFuncSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_MenuHandler CcbUpdateResourceLayer::onResolveCCBCCMenuItemSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

SEL_CCControlHandler CcbUpdateResourceLayer::onResolveCCBCCControlSelector( CCObject * pTarget, const char* pSelectorName )
{

	return NULL;
}

const static float F_Gap = 0.3f;

// Inhert CCNodeLoaderListener
void CcbUpdateResourceLayer::onNodeLoaded(cocos2d::CCNode *pNode, cocos2d::extension::CCNodeLoader *pNodeLoader)
{
	// 变量绑定较init函数更晚，在下面的代码中进行初始化或其他控制}
	// 可以删除，如果不需要}
    loadWidth = m_pSpriteDownload->getContentSize().width;
    loadHeight = m_pSpriteDownload->getContentSize().height;
    
    m_pSpriteDownload->setTextureRect(CCRectMake(0, 0, 0, loadHeight));
    m_curTipsId = 0;
    schedule(schedule_selector(CcbUpdateResourceLayer::updateForShowGameTips), 8.0);
}

void CcbUpdateResourceLayer::startUpdate()
{
    FileUpdate* ins = FileUpdate::sharedInstance();
    ins->reset();
    ins->beginFetchMD5(&GetRemoteFullPath, &GetLocalWriteFullPath, &GetLocalFileData);
    ins->readLocalMd5File();
    
    setState(E_STATE_GET_FILE_LIST);
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(CcbUpdateResourceLayer::DeltaUpdate), this, 0.1, false);
    
    cnt = 0;
    return;
}

static char RemoteFullPath[256];
const char* CcbUpdateResourceLayer::GetRemoteFullPath(const char* pRemotePath) {
#ifdef DEBUG
    sprintf(RemoteFullPath, "%s/v%d/%s", DEBUG_UPDATE_IP, ServerListCtrl::Get()->resourceVersion(), pRemotePath);
#else
    sprintf(RemoteFullPath, "%s/v%d/%s", RELEASE_UPDATE_IP, ServerListCtrl::Get()->resourceVersion(), pRemotePath);
#endif
    return RemoteFullPath;
}

static char LocalWriteFullPath[256];
const char* CcbUpdateResourceLayer::GetLocalWriteFullPath(const char* pLocalPath)
{
    std::string str = CCFileUtils::sharedFileUtils()->getWritablePath();
    if (str[str.length() - 1] == '/') {
        sprintf(LocalWriteFullPath, "%s%s", str.c_str(), pLocalPath);
    } else {
        sprintf(LocalWriteFullPath, "%s/%s", str.c_str(), pLocalPath);
    }
    
    CCLog("Local Write Path:[%s]", LocalWriteFullPath);
    
    return LocalWriteFullPath;
}

static char ReadFullPath[256];
unsigned char* CcbUpdateResourceLayer::GetLocalFileData(const char *pLocalPath, unsigned long *size)
{
    std::string str = CCFileUtils::sharedFileUtils()->getWritablePath();
    if (str[str.length() - 1] == '/') {
        sprintf(LocalWriteFullPath, "%s%s", str.c_str(), pLocalPath);
    } else {
        sprintf(LocalWriteFullPath, "%s/%s", str.c_str(), pLocalPath);
    }
    
    CCLog("Local Read Path:[%s]", LocalWriteFullPath);
    return CCFileUtils::sharedFileUtils()->getFileData(ReadFullPath, "rb", size);
}

//static int Load_MD5_Cnt = 0;

void CcbUpdateResourceLayer::DeltaUpdate(float dt)
{
    FileUpdate* ins = FileUpdate::sharedInstance();
    FileUpdate::UpdateStateType type = FileUpdate::E_UPDATE_IDEL;
    
    CCLog("Game Update, m_state=%d", m_state);
    
    char tmp[256] = {0};
    char spd[32] = {0};
    std::string str;
    
    switch (m_state) {
        case E_STATE_NEED_UPDATE:
            // 需要更新，点击对话框更新}
            break;
        case E_STATE_WAIT_USER:
            break;
        case E_STATE_GET_FILE_LIST: {
            type = ins->Update();
            CCLog("FileUpdate Type:%d", type);
            if (type == FileUpdate::E_UPDATE_CHECK_DIF) {
                setState(E_STATE_CHECK_DIF);
            } else if (type == FileUpdate::E_UPDATE_READY) {
                setState(E_STATE_DOWNLOAD);
                ins->downloadNewFiles();
            } else if (type == FileUpdate::E_UPDATE_ERROR) {
                // handle error
                CCLog("Get File List Error.");
                sprintf( tmp, "%s", GET_STR(Str_download_list_error));
                m_pLabelTTFTips->setString(tmp);
                setState(E_STATE_ERROR);
                break;
            }
//            else if (type == FileUpdate::E_UPDATE_LOADING_MD5) {
//                Load_MD5_Cnt++;
//                if (Load_MD5_Cnt > 10) {
//                    // handle error
//                    CCLog("Get File List Error.");
//                    sprintf( tmp, "%s", GET_STR(Str_download_list_error));
//                    m_pLabelTTFTips->setString(tmp);
//                    setState(E_STATE_ERROR);
//                    break;
//                }
//            }
            //计算速度，显示速度}
            m_lstSpeedCal.push_front( std::make_pair( dt, ins->GetByteCompleteDetail() ) );
            sprintf( spd, "  %.2f kb/s", calcSpeed() / 1024.0 );
            sprintf( tmp, "%s%s", GET_STR(Str_download_list), spd);
            
            m_pLabelTTFTips->setString(tmp);
            break;
        }
        case E_STATE_CHECK_DIF: {
            type = ins->Update();
            
            sprintf( tmp, "%s%d%%", GET_STR(Str_check_file), int(ins->GetDiffCheckProgress() * 100) );
            m_pLabelTTFTips->setString(tmp);
            m_pSpriteDownload->setTextureRect(CCRectMake(0, 0, ins->GetDiffCheckProgress() * loadWidth * F_Gap, loadHeight));
            if (type == FileUpdate::E_UPDATE_READY) {
                m_pSpriteDownload->setTextureRect(CCRectMake(0, 0, loadWidth * F_Gap, loadHeight));
                setState(E_STATE_DOWNLOAD);
                // 开始下载文件}
                ins->downloadNewFiles();
            } else if (type == FileUpdate::E_UPDATE_ERROR) {
                // handle error.
                CCLog("Check Diff Error.");
                sprintf( tmp, "%s", GET_STR(Str_check_file_error));
                m_pLabelTTFTips->setString(tmp);
                setState(E_STATE_ERROR);
                break;
            }
            break;
        }
        case E_STATE_DOWNLOAD: {
            type = ins->Update();
            
            if (type == FileUpdate::E_UPDATE_LOADING_FILE) {
                // 显示下载速度}
                m_lstSpeedCal.push_front( std::make_pair(dt, ins->GetByteCompleteDetail()) );
                sprintf( spd, "  %.2f kb/s", calcSpeed() / 1024.0 );
                sprintf( tmp, "%s(%s %d / %d - %s %d kb / %d kb)",
                        GET_STR(Str_update_file),
                        GET_STR(Str_file_cnt),
                        ins->GetFileCountComplete(),
                        ins->GetFileCountTotal(),
                        GET_STR(Str_file_size),
                        int(ins->GetByteComplete() / 1024.0),
                        int(ins->GetByteTotal() / 1024.0) );
                strcat( tmp, spd );
                m_pLabelTTFTips->setString(tmp);
                //进度条}
                float toPercentage = float(ins->GetByteComplete())/float(ins->GetByteTotal()) / 2 + F_Gap;
                m_pSpriteDownload->setTextureRect(CCRectMake(0, 0, toPercentage * loadWidth, loadHeight));
                
                
            } else if (type == FileUpdate::E_UPDATE_COMPLETE) {
                m_pSpriteDownload->setTextureRect(CCRectMake(0, 0, loadWidth, loadHeight));
                setState(E_STATE_RELOAD);
            } else if (type == FileUpdate::E_UPDATE_ERROR) {
                // handle error
                CCLog("Download Error.");
                sprintf( tmp, "%s", GET_STR(Str_download_error));
                m_pLabelTTFTips->setString(tmp);
                setState(E_STATE_ERROR);
                break;
            }
            break;
        }
        case E_STATE_RELOAD: {
            // 下载完成，更新version文件}
            // 重新读配置文件}
            cnt++;
            int d = cnt % 4;
            switch (d) {
                case 0:
                    sprintf( tmp, "%s", GET_STR(Str_reload_file));
                    break;
                case 1:
                    sprintf( tmp, "%s%s", GET_STR(Str_reload_file), ".");
                    break;
                case 2:
                    sprintf( tmp, "%s%s", GET_STR(Str_reload_file), "..");
                    break;
                case 3:
                    sprintf( tmp, "%s%s", GET_STR(Str_reload_file), "...");
                    break;
                default:
                    break;
            }
            CCLog("%s", tmp);
//            if (d < 5) {
//                sprintf( tmp, "%s", GET_STR(STR_UPDATE_RELOAD));
//            }
//            else if (d < 10 && d >= 5) {
//                sprintf( tmp, "%s%s", GET_STR(STR_UPDATE_RELOAD), ".");
//            }
//            else if (d < 15 && d >= 10)
//            {
//                sprintf( tmp, "%s%s", GET_STR(STR_UPDATE_RELOAD), "..");
//            }
//            else if (d > 15)
//            {
//                sprintf( tmp, "%s%s", GET_STR(STR_UPDATE_RELOAD), "...");
//            }
//          sprintf( tmp, "%s", GET_STR(STR_UPDATE_RELOAD));
            m_pLabelTTFTips->setString(tmp);
            setState(E_STATE_COMPLETE);
            break;
        }
        case E_STATE_COMPLETE: {
            onFinish();
            break;
        }
        default: {
            m_state = E_STATE_ERROR;
            onFinish();
            break;
        }
    }
}

static const int Max_Repeat = 3;

void CcbUpdateResourceLayer::onFinish()
{
    if (m_state == E_STATE_ERROR) {
        CCLog("error finish");
        //TODO: send Log Info to Server!!!!
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CcbUpdateResourceLayer::DeltaUpdate), this);
        
        repeat++;
        
        if (repeat < Max_Repeat) {
            snprintf(strBuff1024, BUFFER_SIZE_1024, "%s", GET_STR(Str_update_error));
        } else {
            snprintf(strBuff1024, BUFFER_SIZE_1024, "%s", GET_STR(Str_update_dead));
        }
        SystemMessage::showSystemMessage(0, this, strBuff1024, this, true, repeat, NULL, true);
        return;
    }
    char tmp[256] = {0};
    sprintf(tmp, "%s", GET_STR(Str_update_success));
    m_pLabelTTFTips->setString(tmp);
    
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(CcbUpdateResourceLayer::DeltaUpdate), this);
    
    SystemMessage::showSystemMessage(0, this, GET_STR(Str_update_success), this, true, 0, NULL, true);
    StartGameLayer::GetCurLayer()->updateFinish();
}

void CcbUpdateResourceLayer::systemMessageOKTapped(SystemMessage *systemMessage)
{
    if (systemMessage->getParam() >= Max_Repeat) {
        exit(0);
    } else {
        this->removeFromParentAndCleanup(true);
    }
}

void CcbUpdateResourceLayer::setState(int state)
{
    CCLog(" >> m_state[%d], new state[%d]", m_state, state);
    m_state = state;
    switch (m_state) {
        case E_STATE_NEED_UPDATE:
            break;
        case E_STATE_WAIT_USER:
            break;
        case E_STATE_GET_FILE_LIST:
            break;
        case E_STATE_CHECK_DIF:
            break;
        case E_STATE_RELOAD:
            break;
        case E_STATE_COMPLETE:
            break;
        case E_STATE_DOWNLOAD:
            break;
        default:
            m_state = E_STATE_ERROR;
            break;
    }
}

float CcbUpdateResourceLayer::calcSpeed()
{
    float total_time = 0;
    uint32 total_byte = 0;
    std::list< std::pair<float, uint32> >::iterator sit = m_lstSpeedCal.begin();
    
    if ( sit != m_lstSpeedCal.end() ) total_byte = sit->second;
    
    while (sit != m_lstSpeedCal.end()) {
        total_time += sit->first;
        ++sit;
        if (total_time > 5.0) break;
    }
    if (sit != m_lstSpeedCal.end()) {
        total_byte -= sit->second;
        m_lstSpeedCal.erase(sit, m_lstSpeedCal.end());
    }
    
    if (total_time != 0) {
        return total_byte / total_time; //b/s
    }
    return 0;
}

void CcbUpdateResourceLayer::updateForShowGameTips(float time)
{
    std::map<uint16, TipsConfig::STC_CONFIG_TIPS> mapTips = GET_CONFIG_MAP(TipsConfig);
    if (mapTips.size() > 0) {
        uint16 r = rand() % mapTips.size();
        
        while (r == m_curTipsId) {
            r = rand() % mapTips.size();
        }
        
        m_curTipsId = r;
        
        TipsConfig::STC_CONFIG_TIPS* tips = GET_CONFIG_STC(TipsConfig, r);
        if (tips) {
            m_pLabelGameTips->setString(tips->strText.c_str());
        }
    }
}



