//}
//  DirOperate.cpp
//  HelloWorld
//
//  Created by 朱 俊杰 on 13-6-28.}
//
//
#include "DirOperate.h"
#include <fstream>
#include <sys/stat.h>
#include "dirent.h"

int DirOperate::DirIsExist( const char* path ) {
//    return access( path, F_OK );
    //#define	F_OK		0	/* test for existence of file */
//    return access( path, 0 );
    //Each of these functions returns 0 if the file has the given mode. The function returns –1 if the named file does not exist or is not accessible in the given mode; in this case, errno is set as follows:}
    std::fstream _file;
    _file.open( path, std::ios::in );
    if (!_file) {
        // not exist
        return -1;
    } else {
        // exist
        return 0;
    }
    return -1;
}

int DirOperate::DirCreate( const char* path ) {
   if ( mkdir( path, 0777 ) == -1 ) return -1;
   return 0;
}

int DirOperate::DelFile(const char *path, bool delRoot) {
    struct stat info;
    stat(path, &info);
    
    if (S_ISDIR(info.st_mode)) {
        DIR* dp = opendir(path);
        struct dirent *curDir = NULL;
        while ( (curDir = readdir(dp)) != NULL ) {
            std::string n_path = path;
            if (n_path[n_path.length() - 1] != '/') {
                n_path += '/';
            }
            n_path += curDir->d_name;
            
            if (strcmp(curDir->d_name, ".") != 0 && strcmp(curDir->d_name, "..") != 0) {
                DelFile(n_path.c_str(), true);
            }
        }
        if (delRoot) {
            if (rmdir(path) == -1) {
                return -1;
            }
            return 0;
        }
        return 0;
    } else {
        if (remove(path) == -1) {
            return -1;
        }
        return 0;
    }
}
