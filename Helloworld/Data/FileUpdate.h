//}
//  FileUpdate.h
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-20.}
//
//

#ifndef __HelloWorld__FileUpdate__
#define __HelloWorld__FileUpdate__

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpClient.h"
#include <string>
#include "Defines.h"
#include "md5.h"
#include <map>

class FileUpdate {
    
public:
    enum UpdateStateType {
        E_UPDATE_IDEL           = 0,
        E_UPDATE_LOADING_MD5    = 1,
        E_UPDATE_CHECK_DIF      = 2,
        E_UPDATE_READY          = 3, //
        E_UPDATE_LOADING_FILE   = 4,
        E_UPDATE_COMPLETE       = 5,
        E_UPDATE_ERROR          = 6,
    };
    
    typedef struct {
        std::string strPath;
        std::string strMD5;
        uint32 dwSize;
    }STC_FILE_INFO;
    
    typedef const char* (*GET_PATH_FUNC) (const char* pRealPath);
    typedef unsigned char* (*GET_DATA_FUNC) (const char* pRealPath, unsigned long* pSize);
    typedef std::map< std::string, STC_FILE_INFO > FileContainer;
    
    
    static FileUpdate *sharedInstance();
    
    void reset();
    
    uint32 GetFileCountTotal();
    uint32 GetFileCountComplete();
    
    uint32 GetByteTotal();
    uint32 GetByteComplete();
    uint32 GetByteCompleteDetail();
    
    float GetDiffCheckProgress();
    
    FileContainer& GetRemoteFileMap();
    FileContainer& GetUpdateFileMap();
    
    const std::string& GetErrorMsg();
    
    void SetMaxRetryTime(int v) { m_dwMaxRetryCnt = v; }
    
    // 初始化地址}
    void beginFetchMD5(GET_PATH_FUNC remoteAdd,
                       GET_PATH_FUNC localAdd,
                       GET_DATA_FUNC localReadFile );
    void downloadNewFiles();
    void RequestFileList(GET_PATH_FUNC resRemoteRoot);
    
    // 读取本地res.md5文件}
    void readLocalMd5File();
    
    // 下载文件回调}
    static void downloadFilesCallback(void* target, HttpResponse* response);
    // 下载MD5回调}
    static void downloadMD5Callback(void* target, HttpResponse* response);
    UpdateStateType Update();
    
    int UnZip(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int *outLength);
protected:
    GET_PATH_FUNC m_remoteAdd;
    GET_PATH_FUNC m_localAdd;
    GET_DATA_FUNC m_localReadFile;
    
//    std::string m_strUpdateDir;
    
private:
    FileUpdate();
    virtual ~FileUpdate();
    
    static void* CheckDiff(void *data);
    bool createDirOfFile(const char* path);
    std::string GetMD5(const void* data, size_t len);
    std::string GetMD5(const std::string* str);
    std::string GetMD5( const char* filePath );
    
    void TrimPath( std::string& dest, const char* from );
    
    // 开始下载MD5}
    void fetchRemoteMD5();
    void setError(const char* errorMsg);
    UpdateStateType m_state;
    
    int m_dwMaxRetryCnt;
    std::string m_strErrorMsg;
    
    // 服务器的Res.md5文件map}
    FileContainer m_mapRemote;
    FileContainer m_mapUpdateFiles;
    // 本地的Res.md5文件map}
    FileContainer m_mapLocal;
    
    uint32 m_dwFileCountTotal;
    uint32 m_dwCompleteFileCount;
    
    uint32 m_dwByteTotal;
    uint32 m_dwCompleteByte;
    
    uint32 m_dwCompleteByteDetail;
    
    float m_fDiffCheckProgress;
    
    MD5 m_md5;
    bool m_bRequestFileList;
};

#endif /* defined(__HelloWorld__FileUpdate__) */
