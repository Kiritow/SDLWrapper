#pragma once
#include "includes.h"

class RWOP
{
public:
	std::shared_ptr<SDL_RWops> sp;

	RWOP(const std::string& filename, const std::string& mode = "rb");
};
