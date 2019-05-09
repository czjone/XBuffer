#ifndef XBUFFER_PATH_UTIL_HPP
#define XBUFFER_PATH_UTIL_HPP 1

#include <regex>
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#elif _LINUX
#include <stdarg.h>
#include <sys/stat.h>
#else
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#define ACCESS _access
#define MKDIR(a) _mkdir((a))
#elif _LINUX
#define ACCESS access
#define MKDIR(a) mkdir((a), 0755)
#else
#define ACCESS access
#define MKDIR(a) mkdir((a), 0755)
#endif

//分隔成目录数组
#define REGX_PATH_FOLDERS "(\\w|\\ |-|\\.)+"
#define REGX_FNAME_EXT "(\\w|-)+"
namespace XBF {
namespace PathUtil {

    inline std::string GetFName(const std::string& path)
    {
        std::regex reg(REGX_PATH_FOLDERS);
        std::sregex_iterator it(path.begin(), path.end(), reg);
        std::sregex_iterator end;
        std::vector<std::string> paths;
        for (; it != end; ++it) {
            paths.push_back(it->str());
        }
        return paths[paths.size() - 1];
    };

    inline std::string GetNameWithoutFileExtention(const std::string& path)
    {
        std::string name = GetFName(path);
        std::regex reg(REGX_FNAME_EXT);
        std::sregex_iterator it(name.begin(), name.end(), reg);
        std::sregex_iterator end;
        std::vector<std::string> paths;
        for (; it != end; ++it) {
            paths.push_back(it->str());
        }
        return paths[0];
    };

    inline int CreateDir(const std::string& path)
    {
        int i = 0;
        int iRet;
        int iLen;
        char* pszDir;
        const char* pDir = path.c_str();

        if (NULL == pDir) {
            return 0;
        }

        pszDir = strdup(pDir);
        iLen = strlen(pszDir);

        // 创建中间目录
        for (i = 0; i < iLen; i++) {
            if (pszDir[i] == '\\' || pszDir[i] == '/') {
                if(i==0) continue;
                pszDir[i] = '\0';
                //如果不存在,创建
                iRet = ACCESS(pszDir, 0);
                if (iRet != 0) {
                    iRet = MKDIR(pszDir);
                    if (iRet != 0) {
                        return -1;
                    }
                }
                //支持linux,将所有\换成/
                pszDir[i] = '/';
            }
        }

        iRet = MKDIR(pszDir);
        free(pszDir);
        return iRet;
    }
}
}

#endif