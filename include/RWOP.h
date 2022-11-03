#pragma once
#include "includes.h"

class RWOP
{
public:
	std::unique_ptr<SDL_RWops, decltype(&SDL_RWclose)> sp;

	RWOP(const std::string& filename, const std::string& mode = "rb");
};
