/**
 * Meet Programming Language Conversion.
 */

// https://blog.csdn.net/u012234115/article/details/83186386

#include "Conversion.hpp"

#ifdef _WIN32

#include <windows.h>

std::string utf8ToGbk(const char* utf8) {
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);

    wchar_t* wszGBK = new wchar_t[len + 1];

    memset(wszGBK, 0, len * 2 + 2);

    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wszGBK, len);

    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);

    char* szGBK = new char[len + 1];

    memset(szGBK, 0, len + 1);

    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);

    std::string strTemp(szGBK);

    if (wszGBK) delete[] wszGBK;
    if (szGBK) delete[] szGBK;
    
    return strTemp;
}

#else

#include <iconv.h>

typedef long unsigned int size_t;

int utf8ToGbk(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
    iconv_t cd;

    char **pin = &inbuf;
    char **pout = &outbuf;
    
    cd = iconv_open("gbk", "utf-8");

    if (0 == cd) 
        return -1;
    if (-1 == iconv(cd, pin, &inlen, pout, &outlen)) {
        iconv_close(cd);

        return -1;
    }
 
    iconv_close(cd);

    return 0;
}

#endif