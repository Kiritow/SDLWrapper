#include "Util.h"
#include <memory>

#ifdef _WIN32

#include <Windows.h>

std::string GBKToUTF8(const std::string& str)
{
	DWORD dwBufSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, NULL, 0);
	std::unique_ptr<wchar_t[]> buff(new wchar_t[dwBufSize + 1]);
	wmemset(buff.get(), 0, dwBufSize + 1);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, buff.get(), dwBufSize);

	DWORD dwResultSize = WideCharToMultiByte(CP_UTF8, 0, buff.get(), -1, NULL, 0, NULL, NULL);
	std::unique_ptr<char[]> result(new char[dwResultSize + 1]);
	WideCharToMultiByte(CP_UTF8, 0, buff.get(), -1, result.get(), dwResultSize, NULL, NULL);

	return std::string(result.get(), dwResultSize);
}

#endif
