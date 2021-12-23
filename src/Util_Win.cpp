#include "Util.h"
#include <memory>

#ifdef _WIN32

#include <Windows.h>

std::string GBKToUTF8(const std::string& str)
{
	DWORD dwBufSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, NULL, 0);
	auto buff = std::make_unique<wchar_t[]>(dwBufSize);
	wmemset(buff.get(), 0, dwBufSize);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), -1, buff.get(), dwBufSize);

	DWORD dwResultSize = WideCharToMultiByte(CP_UTF8, 0, buff.get(), -1, NULL, 0, NULL, NULL);
	auto result = std::make_unique<char[]>(dwResultSize);
	WideCharToMultiByte(CP_UTF8, 0, buff.get(), -1, result.get(), dwResultSize, NULL, NULL);

	return std::string(result.get(), dwResultSize);
}

std::string UTF8ToGBK(const std::string& str)
{
	DWORD dwBufSize = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.c_str(), -1, NULL, 0);
	auto buff = std::make_unique<wchar_t[]>(dwBufSize);
	wmemset(buff.get(), 0, dwBufSize);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.c_str(), -1, buff.get(), dwBufSize);

	DWORD dwResultSize = WideCharToMultiByte(CP_ACP, 0, buff.get(), -1, NULL, 0, NULL, NULL);
	auto result = std::make_unique<char[]>(dwResultSize);
	WideCharToMultiByte(CP_ACP, 0, buff.get(), -1, result.get(), dwResultSize, NULL, NULL);

	return std::string(result.get(), dwResultSize);
}

#endif
