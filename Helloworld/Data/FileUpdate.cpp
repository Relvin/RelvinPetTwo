//}
//  FileUpdate.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-20.}
//
//

#include "FileUpdate.h"

//#include "curl.h"
#include "Log.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "DirOperate.h"
#include "pthread.h"
#include <zlib.h>
#include <fstream>

#pragma comment(lib, "pthreadVC2.lib")
#define MAX_PATH_LENGTH	256

static pthread_t thread;

FileUpdate * FileUpdate::sharedInstance()
{
    static FileUpdate instance;
    return &instance;
}

FileUpdate::FileUpdate()
{
    m_remoteAdd = NULL;
    m_localAdd = NULL;
    m_state = E_UPDATE_IDEL;
    m_dwMaxRetryCnt = 2;
    m_strErrorMsg = "";
    m_localReadFile = NULL;
    m_dwByteTotal = 0;
    m_dwFileCountTotal = 0;
    m_dwCompleteFileCount = 0;
    m_dwCompleteByteDetail = 0;
    m_dwCompleteByte = 0;
    m_fDiffCheckProgress = 0;
    m_bRequestFileList = false;
}

FileUpdate::~FileUpdate()
{
    
}

void FileUpdate::beginFetchMD5(GET_PATH_FUNC remoteAdd,
                               GET_PATH_FUNC localAdd,
                               GET_DATA_FUNC localReadFile)
{
    if (m_state == E_UPDATE_COMPLETE) {
        m_state = E_UPDATE_IDEL;
    }
    if (m_state != E_UPDATE_IDEL) return;
    IME_LOG("begin File Update");
    m_remoteAdd = remoteAdd;
    m_localAdd = localAdd;
    m_localReadFile = localReadFile;
    
//    TrimPath( m_strUpdateDir	, updateDir );
    
    m_bRequestFileList = false;
    
    fetchRemoteMD5();
}

void FileUpdate::fetchRemoteMD5()
{
    const char* versionUrl = (*m_remoteAdd)("res.md5");
    
    m_state = E_UPDATE_LOADING_MD5;
    
    HttpRequest *request = new HttpRequest(
                                           HttpRequest::E_HTTP_GET,
                                           versionUrl,
                                           this,
                                           downloadMD5Callback);
    HttpClient::GetInstance()->Send(request);
    IME_LOG(" >> Requets MD5 URL is:[%s]", versionUrl);
}

void FileUpdate::downloadNewFiles()
{
    if (m_state != E_UPDATE_READY) {
        return;
    }
    if (m_mapUpdateFiles.size() == 0) {
        IME_LOG(" >> Download Complete.");
        m_state = E_UPDATE_COMPLETE;
        return;
    }
    
    const char* filePath;
    
    m_state = E_UPDATE_LOADING_FILE;
    for (FileContainer::iterator it = m_mapUpdateFiles.begin(); it != m_mapUpdateFiles.end(); it++) {
        filePath = (*m_remoteAdd)(it->second.strPath.c_str());
        
        HttpRequest* request = new HttpRequest(
                                                 HttpRequest::E_HTTP_GET,
                                                 filePath,
                                                 this,
                                                 downloadFilesCallback);
        request->SetUserData(&(it->second));
        HttpClient::GetInstance()->Send(request);
        
        IME_LOG(" >> Add Request:%s", request->GetUrl());
    }
}

void FileUpdate::reset()
{
    m_dwByteTotal       = 0;
    m_dwFileCountTotal  = 0;
    m_dwCompleteByte    = 0;
    m_dwCompleteByteDetail  = 0;
    m_dwCompleteFileCount   = 0;
    m_state             = E_UPDATE_IDEL;
    m_bRequestFileList  = false;
    m_strErrorMsg       = "";
    m_mapUpdateFiles.clear();
    m_mapRemote.clear();
}

void FileUpdate::RequestFileList(GET_PATH_FUNC resRemoteRoot)
{
    m_remoteAdd = resRemoteRoot;
    
    m_bRequestFileList  =true;
    fetchRemoteMD5();
}

FileUpdate::UpdateStateType FileUpdate::Update()
{
    HttpClient::GetInstance()->DispatchResponse();
    m_dwCompleteByteDetail = m_dwCompleteByte + HttpClient::GetInstance()->GetProgressByte();
    IME_LOG(">> File Update m_state[%d]", m_state);
    return m_state;
}

void FileUpdate::downloadMD5Callback(void *target, HttpResponse *response)
{
    FileUpdate *ins = FileUpdate::sharedInstance();
    
    if (!response->IsSucceed()) {
        IME_ERROR(">> Error when download %s", response->GetRequest()->GetUrl());
        ins->setError(response->GetErrorMsg()->c_str());
        HttpClient::DestroyInstance();
        return;
    }
    
    IME_LOG(" >> MD5 Loaded");

    // we don't use res.md5.gz, cz our res.md5 is not very big.
    // If want to use this, should change "res.md5" to "res.md5.gz" in fetchMD5 method.
//    unsigned char* 	unzipData 	= NULL;
//	unsigned int	unzipLength	= 0;
//    
//	int unzipResult = ins->UnZip( (unsigned char*)response->GetResponseData()->data(), response->GetResponseData()->length(), &unzipData, &unzipLength );
//    
//    if ( unzipResult != Z_OK )
//	{
//		IME_ERROR( "Unzip Failed [%d]", unzipResult );
//		ins->setError( "Unzip Failed" );
//		HttpClient::DestroyInstance();
//		return;
//	}
    
    std::stringstream ss( *(response->GetResponseData()) );
    // path, md5, size
    std::string linePath, lineMd5, lineSize;
    
    ins->m_mapRemote.clear();
    while (std::getline(ss, linePath) && std::getline(ss, lineMd5) && std::getline(ss, lineSize)) {
        STC_FILE_INFO stcFileInfo;
        
        stcFileInfo.strPath = linePath;
        stcFileInfo.strMD5 = lineMd5;
        stcFileInfo.dwSize = std::atoi(lineSize.c_str());
        
        ins->m_mapRemote.insert(std::make_pair(stcFileInfo.strPath, stcFileInfo));
    }
    
//    delete[] unzipData;
    
    if (ins->m_bRequestFileList) {
        IME_LOG(" >> FileUpdate: bRequestFileList true, E_UPDATE_IDEL");
        ins->m_state = E_UPDATE_IDEL;
    } else {
        IME_LOG(" >> FileUpdate: bRequestFileList false, E_UPDATE_CHECK_DIF");
        ins->m_state = E_UPDATE_CHECK_DIF;
        
        pthread_create(&thread, NULL, CheckDiff, NULL);
        pthread_detach(thread);
    }
    
    const char* localFilePath;
    localFilePath = (*ins->m_localAdd)("res.md5");
    IME_LOG(">> local file path is[%s]", localFilePath);

    FILE* pf = fopen(localFilePath, "wb");
    if (!pf) {
        IME_ERROR(">> Cannot open File:%s", localFilePath);
        FileUpdate::sharedInstance()->setError("Cann't Write File");
        HttpClient::DestroyInstance();
        return;
    }
    fwrite(response->GetResponseData()->data(), response->GetResponseData()->size(), 1, pf);
    fclose( pf );
    
    IME_LOG(">> Write Complete:%s", response->GetRequest()->GetUrl());
    
}

void FileUpdate::readLocalMd5File()
{
//    FileUpdate *ins = FileUpdate::sharedInstance();
//    std::string strDocPath = ins->m_localAdd + "res.md5";
    const char* documentMd5Path = (*m_localAdd)("res.md5");
    CCLOG("FileUpdate: >> read local md5 file [%s]", documentMd5Path);
    std::ifstream fin;
    fin.open(documentMd5Path);
    while ( !fin.is_open() ) {
        std::string fullIpaPath = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("res.md5");
        CCLOG("FileUpdate: >> full path for res.md5[%s]", fullIpaPath.c_str());
        fin.open(fullIpaPath.c_str());
    }
    std::string linePath, lineMd5, lineSize;
    m_mapLocal.clear();
    
    while (std::getline(fin, linePath) && std::getline(fin, lineMd5) && std::getline(fin, lineSize)) {
        STC_FILE_INFO stcFileInfo;
        
        stcFileInfo.strPath = linePath;
        stcFileInfo.strMD5 = lineMd5;
        stcFileInfo.dwSize = std::atoi(lineSize.c_str());
        
        m_mapLocal.insert( std::make_pair(stcFileInfo.strPath, stcFileInfo));
    }
    fin.close();
}


void* FileUpdate::CheckDiff(void *data)
{
    FileUpdate* ins = FileUpdate::sharedInstance();
    IME_LOG(" >> -- Check Diff --");
    
    int total = ins->m_mapRemote.size(), cur = 0;
    ins->m_mapUpdateFiles.clear();
    ins->m_fDiffCheckProgress = 0;
    
    IME_LOG(" >> Remote File Count:[%d]", total);
    
    int t = 0;
    
    for (FileContainer::iterator it = ins->m_mapRemote.begin(); it != ins->m_mapRemote.end(); it++) {
        // skip file that we don't want update
//        if ( it->second.strPath.find( ins->m_strUpdateDir, 0 ) != 0 ) continue;
        

//        unsigned long size;
//        unsigned char* data = (ins->m_localReadFile)(it->second.strPath.c_str(), &size);
//
//        std::string strMD5;
//        
//        if (!data || ( strMD5 = ins->GetMD5(data, size) ) != it->second.strMD5 ) {
//            if (data) {
//                IME_LOG("[U] >> [%s] %u(%u) %s(%s)",
//                        it->second.strPath.c_str(),
//                        size,
//                        it->second.dwSize,
//                        strMD5.c_str(),
//                        it->second.strMD5.c_str());
//            } else {
//                IME_LOG("[A] >> [%s]", it->second.strPath.c_str());
//            }
//            
//            ins->m_mapUpdateFiles.insert(std::make_pair(it->first, it->second));
//            ins->m_dwFileCountTotal++;
//            ins->m_dwByteTotal += it->second.dwSize;
//        }
//        
//        if (data) {
//            delete [] data;
//        }
        
        FileContainer::iterator localIter = ins->m_mapLocal.find(it->first);
        if (localIter == ins->m_mapLocal.end()) {
            IME_LOG("[A] >> [%s]", it->second.strPath.c_str());
            
            ins->m_mapUpdateFiles.insert( std::make_pair(it->first, it->second) );
            ins->m_dwFileCountTotal++;
            ins->m_dwByteTotal += it->second.dwSize;
            
            t++;
        } else {
            if (localIter->second.strMD5 == it->second.strMD5 && localIter->second.dwSize == it->second.dwSize) {
                // Same File, Continue
            } else {
                IME_LOG("[U] >> replace file[%s] \n%s(%s) \n%u(%u)",
                        localIter->second.strPath.c_str(),
                        localIter->second.strMD5.c_str(),
                        it->second.strMD5.c_str(),
                        localIter->second.dwSize,
                        it->second.dwSize);
                
                ins->m_mapUpdateFiles.insert( std::make_pair(it->first, it->second) );
                ins->m_dwFileCountTotal++;
                ins->m_dwByteTotal += it->second.dwSize;
                
                t++;
            }
        }
        
        ins->m_fDiffCheckProgress = ++cur / (float) total;
    }
    
    IME_LOG(" >> --Check Diff Complete--, [%u] need to update.", t);
    ins->m_state = E_UPDATE_READY;
    
    return 0;
}

void FileUpdate::downloadFilesCallback(void *target, HttpResponse *response)
{
    FileUpdate* ins = FileUpdate::sharedInstance();
    
    if (! response->IsSucceed()) {
        IME_ERROR( "Error when download %s", response->GetRequest()->GetUrl() );
        ins->setError(response->GetErrorMsg()->c_str());
        HttpClient::DestroyInstance();
        return;
    }
    
    STC_FILE_INFO* pInfo = (STC_FILE_INFO*) response->GetRequest()->GetUserData();
    
    std::string strMD5 = ins->GetMD5(response->GetResponseData());
    
    if (strMD5 != pInfo->strMD5) {
        IME_LOG(" >> Wrong MD5 downloaded, url=%s,\n get=%s,\n target=%s",
                response->GetRequest()->GetUrl(),
                strMD5.c_str(),
                pInfo->strMD5.c_str());
        
        if (response->GetRequest()->GetRetryCnt() >= ins->m_dwMaxRetryCnt) {
            ins->setError("Update Fail( Wrong MD5 ), Plz Try Again.");
            HttpClient::DestroyInstance();
        } else {
            HttpRequest* retryRequest = new HttpRequest( *response->GetRequest() );
            retryRequest->SetRetryCnt(response->GetRequest()->GetRetryCnt() + 1);
            HttpClient::GetInstance()->Send(retryRequest);
            IME_LOG(" >> Add Retry Request[%s], retry[%d].", retryRequest->GetUrl(), retryRequest->GetRetryCnt());
        }
        return;
    }
    
    const char* localFilePath;
    
    localFilePath = (*ins->m_localAdd)(pInfo->strPath.c_str());
    IME_LOG(" >> Update Local File:%s", localFilePath);
    
    if (!ins->createDirOfFile(localFilePath)) {
        IME_ERROR(">> Error in Write Local File Dir.");
        ins->setError("Cann't write File Dir");
        HttpClient::DestroyInstance();
        return;
    }
    
    FILE* pf = fopen(localFilePath, "wb");
    if (!pf) {
        IME_ERROR("Can't Open File:%s", localFilePath);
        ins->setError("Can't Write File.");
        HttpClient::DestroyInstance();
        return;
    }
    fwrite(response->GetResponseData()->data(), response->GetResponseData()->size(), 1, pf);
    fclose(pf);
    
    IME_LOG(" >> Write [%s] Complete.", response->GetRequest()->GetUrl());
    
    ins->m_dwCompleteFileCount++;
    ins->m_dwCompleteByte += pInfo->dwSize;
    
    if (ins->m_dwCompleteFileCount == ins->m_dwFileCountTotal) {
        IME_LOG(" >> Write All Files Complete.");
        ins->m_state = E_UPDATE_COMPLETE;
    }
}

bool FileUpdate::createDirOfFile(const char *path)
{
    char dir[MAX_PATH_LENGTH];
    int len = strlen(path);
    memcpy(dir, path, len);
    
    bool valid = false;
    
    for (int i = len - 1; i >= 0; i--) {
        if (dir[i] == '/' || dir[i] == '\\') {
            dir[i] = '\0';
            valid = true;
            break;
        }
    }
    
    if (!valid) {
        IME_ERROR("Create Dir param path error.[%s]", path);
        return false;
    }
    
    if (DirOperate::DirIsExist(dir) == -1) {
        if ( !createDirOfFile(dir) ) {
            return false;
        }
        DirOperate::DirCreate(dir);
    }
    
    return true;
}

std::string FileUpdate::GetMD5(const void *data, size_t len)
{
    m_md5.reset();
    m_md5.update(data, len);
    return m_md5.toString();
}

std::string FileUpdate::GetMD5(const std::string *str)
{
    m_md5.reset();
    m_md5.update(*str);
    return m_md5.toString();
}

std::string FileUpdate::GetMD5( const char* filePath )
{
	std::ifstream stream( filePath, std::ios::in | std::ios::binary );
	m_md5.reset();
	m_md5.update( stream );
	return m_md5.toString();
}

void FileUpdate::setError(const char *errorMsg)
{
    m_state = E_UPDATE_ERROR;
    m_strErrorMsg = errorMsg;
}

FileUpdate::FileContainer& FileUpdate::GetRemoteFileMap()
{
    return m_mapRemote;
}

FileUpdate::FileContainer& FileUpdate::GetUpdateFileMap()
{
    return m_mapUpdateFiles;
}

const std::string& FileUpdate::GetErrorMsg()
{
    return m_strErrorMsg;
}

uint32 FileUpdate::GetFileCountTotal()
{
    return m_dwFileCountTotal;
}

uint32 FileUpdate::GetFileCountComplete()
{
    return m_dwCompleteFileCount;
}

uint32 FileUpdate::GetByteTotal()
{
    return m_dwByteTotal;
}

uint32 FileUpdate::GetByteComplete()
{
    return m_dwCompleteByte;
}

uint32 FileUpdate::GetByteCompleteDetail()
{
    return m_dwCompleteByteDetail;
}

float FileUpdate::GetDiffCheckProgress()
{
    return m_fDiffCheckProgress;
}

void FileUpdate::TrimPath( std::string& dest, const char* from )
{
	char 	tmp[MAX_PATH_LENGTH];
	int		len = strlen( from );
	memcpy( tmp, from, len + 1 );
	if ( tmp[ len - 1 ] == '/' ) tmp[ len - 1 ] = '\0';
	dest = tmp;
}

int FileUpdate::UnZip(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int *outLength)
{
    /* ret value */
    int err = Z_OK;
    
    int bufferSize = 256 * 1024;
    *out = new unsigned char[bufferSize];
    
    z_stream d_stream; /* decompression stream */
    d_stream.zalloc 	= (alloc_func)0;
    d_stream.zfree 		= (free_func)0;
    d_stream.opaque 	= (voidpf)0;
    
    d_stream.next_in  	= in;
    d_stream.avail_in 	= inLength;
    d_stream.next_out 	= *out;
    d_stream.avail_out 	= bufferSize;
    
    /* window size to hold 256k */
    if( (err = inflateInit2(&d_stream, 15 + 32)) != Z_OK )
        return err;
    
    for (;;)
    {
        err = inflate(&d_stream, Z_NO_FLUSH);
        
        if (err == Z_STREAM_END)
        {
            break;
        }
        
        switch (err)
        {
            case Z_NEED_DICT:
                err = Z_DATA_ERROR;
                break;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&d_stream);
                return err;
        }
        
        // not enough memory ?
        if (err != Z_STREAM_END)
        {
            delete [] *out;
            *out = new unsigned char[bufferSize * 2];
            
            /* not enough memory, ouch */
            if (! *out )
            {
            	IME_ERROR("UnZip Realloc Failed");
                inflateEnd(&d_stream);
                return Z_MEM_ERROR;
            }
            
            d_stream.next_out = *out + bufferSize;
            d_stream.avail_out = bufferSize;
            bufferSize *= 2;
        }
    }
    
    *outLength = bufferSize - d_stream.avail_out;
    err = inflateEnd(&d_stream);
    return err;
}


