#include "RWOP.h"

RWOP::RWOP(const std::string& filename, const std::string& mode) : sp(SDL_RWFromFile(filename.c_str(), mode.c_str()), SDL_RWclose)
{
	
}
