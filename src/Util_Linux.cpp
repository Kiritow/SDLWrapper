#include "Util.h"
#include <memory>

#ifndef _WIN32
#include <iconv.h>

std::string GBKToUTF8(const std::string& str)
{
    iconv_t ivt = iconv_open("utf-8", "gb2312");
    if (!ivt) return std::string();

    size_t inLeft = str.size();
    size_t outLeft = 1024;
    char buffer[1024];

    char* pIn = (char*)str.c_str();
    char* pOut = buffer;
    std::string result;

    while(1)
    {
        int ret = iconv(ivt, &pIn, &inLeft, &pOut, &outLeft);
        if (ret == (size_t) - 1)
        {
            if (errno == E2BIG)
            {
                // need more space in output
                result.append(buffer, 1024 - outLeft);
                pOut = buffer;
                outLeft = 1024;
                continue;
            }

            iconv_close(ivt);
            return std::string();
        }

        if (outLeft < 1024)
        {
            result.append(buffer, 1024 - outLeft);
            iconv_close(ivt);
            break;
        }
    }

    return result;
}

std::string UTF8ToGBK(const std::string& str)
{
    iconv_t ivt = iconv_open("gb2312", "utf-8");
    if (!ivt) return std::string();

    size_t inLeft = str.size();
    size_t outLeft = 1024;
    char buffer[1024];

    char* pIn = (char*)str.c_str();
    char* pOut = buffer;
    std::string result;

    while(1)
    {
        int ret = iconv(ivt, &pIn, &inLeft, &pOut, &outLeft);
        if (ret == (size_t) - 1)
        {
            if (errno == E2BIG)
            {
                // need more space in output
                result.append(buffer, 1024 - outLeft);
                pOut = buffer;
                outLeft = 1024;
                continue;
            }

            iconv_close(ivt);
            return std::string();
        }

        if (outLeft < 1024)
        {
            result.append(buffer, 1024 - outLeft);
            iconv_close(ivt);
            break;
        }
    }

    return result;
}

#endif
