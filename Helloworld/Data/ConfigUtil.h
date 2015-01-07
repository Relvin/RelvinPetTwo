#ifndef __CONFIG_UTIL_H__
#define __CONFIG_UTIL_H__

#include "string"
#include "vector"
#include "stdarg.h"

#define FORMAT_PARAM_END -1

class CUtil
{
public:
    static void StrSplit(const std::string & src, const std::string & sep, std::vector<std::string> & vecRes);
    
    static void ReplaceAll( std::string& str, const std::string& oldValue, const std::string& newValue );
    
    static std::string StrFormat( const char* str, int value, ... );
};



#endif
