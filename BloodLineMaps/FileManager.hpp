#pragma once
#include <fstream>


class FileManager
{
	std::fstream file;

public:
	static const std::string mapPath;

	FileManager();

};
