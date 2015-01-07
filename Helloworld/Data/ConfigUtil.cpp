#include "ConfigUtil.h"

void CUtil::StrSplit(const std::string & src, const std::string & sep, std::vector<std::string> & vecRes)
{
	vecRes.clear();
	std::string s;
	for(std::string::const_iterator i = src.begin(); i != src.end(); i++)
	{
		if (sep.find(*i) != std::string::npos)
		{
			if (s.length()) vecRes.push_back(s);
			s = "";
		}
		else
		{
			s += *i;
		}
	}
	if (s.length()) vecRes.push_back(s);
}

void CUtil::ReplaceAll(std::string &str, const std::string &oldValue, const std::string &newValue)
{
    for ( std::string::size_type pos(0);; pos += newValue.length() )
    {
        if ( ( pos = str.find( oldValue, pos ) ) != std::string::npos )
        {
            str.replace( pos, oldValue.length(), newValue );
        }
        else 
        {
            break;
        }
    }
}

std::string CUtil::StrFormat(const char *str, int value, ...)
{
    va_list params;
    va_start( params, value );
    
    int cnt     = 0;
    int prev    = value;
    
    std::string ret( str );
    
    while ( prev != FORMAT_PARAM_END )
    {
        char pOld[16];
        sprintf( pOld, "{%d}", cnt++ );
        std::string oldString( pOld );
        
        char pNew[16];
        sprintf( pNew, "%d", prev );
        std::string newString( pNew );
        
        ReplaceAll( ret, oldString, newString );
        
        prev = va_arg( params, int );
    }
    
    va_end( params );
    
    return ret;
}


