#include "FileManager.hpp"
#include "MapInterface.hpp"
#include <iostream>

namespace File
{

const std::string mapPath = "Maps.txt";




void saveMap(MapInterface* mapInterface)
{
	const std::vector<Cell>& mapData = mapInterface->mapData;
	
	// Find Matrix size
	int maxX = mapData[0].col;
	int maxY = mapData[0].row;
	int minX = maxX;
	int minY = maxY;
	for (const Cell& cell : mapData)
	{
		if (cell.col > maxX) maxX = cell.col;
		if (cell.row > maxY) maxY = cell.row;
		if (cell.col < minX) minX = cell.col;
		if (cell.row < minY) minY = cell.row;
	}

	// Create Matrix
	unsigned int matrixWidth = (maxX - minX) + 1;
	unsigned int matrixHeight = (maxY - minY) + 1;
	std::vector<std::vector<int>> matrix(matrixHeight, std::vector<int>(matrixWidth, 0));

	// Fill Matrix
	for (const Cell& cell : mapData)
	{
		matrix[cell.row - minY][cell.col - minX] = cell.getEncode();
	}

	// Write Matrix to file
	std::ofstream file(mapPath, std::ios::out);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file" << std::endl;
		return;
	}
	file << matrixWidth << '\n' << matrixHeight << std::endl;
	file << '{';
	int* last = &matrix.back().back();
	for (const std::vector<int>& row : matrix)
	{
		for (const int& code : row)
		{
			file << code;
			if (&code != last) file << ", ";
		}
		if (&row != &matrix.back()) file << std::endl;
	}
	file << '}';
	file.close();
}


void openMap(MapInterface* mapInterface, std::string path)
{
	// Open File 
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "No se pudo abrir el archivo." << std::endl;
		return;
	}

	std::string line;

	// Get Matrix size
	std::getline(file, line);
	unsigned int matrixWidth = std::stoi(line);
	std::getline(file, line);
	unsigned int matrixHeight = std::stoi(line);

	// Ignore '{'
	file.ignore(std::numeric_limits<std::streamsize>::max(), '{');

	std::vector<Cell>& data = mapInterface->mapData;
	data.clear();

	// Read Matrix
	unsigned int i = -1;
	while (std::getline(file, line, ','))
	{
		i++;
		int code = std::stoi(line);
		if (code == 0) continue;
		data.emplace_back(sf::Vector2i(i % matrixWidth, i / matrixWidth), code);
	}

	file.close();
}


} // namespace File