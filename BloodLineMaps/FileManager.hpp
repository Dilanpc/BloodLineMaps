#pragma once
#include <fstream>

class MapInterface;

namespace File
{
	extern const std::string mapPath;

	void saveMap(MapInterface* map);
	void openMap(MapInterface* map, std::string path = mapPath);

};
