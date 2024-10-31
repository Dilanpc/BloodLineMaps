#include "FileManager.hpp"


FileManager::FileManager()
	: file(mapPath, std::ios::in | std::ios::out)
{
	if (!file.is_open())
	{
		file.open(mapPath, std::ios::out);
		file.close();
		file.open(mapPath, std::ios::in | std::ios::out);
	}
}