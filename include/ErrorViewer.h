#pragma once
#include <string>
#include <exception>

class ErrorViewer : std::exception
{
public:
	std::string msg;
	ErrorViewer();
	ErrorViewer(const char* errtype, const char* filename, int line, const std::string& hint = std::string());
	const char* what() const noexcept override;
};

#define SDLErrorViewer() ErrorViewer("SDLError", __FILE__, __LINE__)
#define SDLErrorViewerHint(hint) ErrorViewer("SDLError", __FILE__, __LINE__, hint)
