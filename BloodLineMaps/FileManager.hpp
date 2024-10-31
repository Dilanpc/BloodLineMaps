#pragma once
#include <fstream>

class MapInterface;

class FileManager
{

public:
	static const std::string mapPath;

	FileManager();

	static void saveMap(MapInterface* map);

};
