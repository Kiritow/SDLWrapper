#include "includes.h"
#include <sstream>

ErrorViewer::ErrorViewer() : msg(SDL_GetError())
{
	
}

ErrorViewer::ErrorViewer(const char* errtype, const char* filename, int line, const std::string& hint) : msg(SDL_GetError())
{
	std::ostringstream ostr;
	if (hint.empty())
	{
		ostr << errtype << "@" << filename << ":" << line << ": " << msg;
	}
	else
	{
		ostr << errtype << "@" << filename << ":" << line << ": " << hint << "(" << msg << ")";
	}
	msg = ostr.str();
}

const char* ErrorViewer::what() const noexcept
{
	return msg.c_str();
}
