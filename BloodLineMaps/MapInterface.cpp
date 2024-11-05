#include "MapInterface.hpp"
#include <filesystem>

constexpr auto CELL_SIZE = 64;

std::vector<sf::Texture> MapInterface::tileTextures;
sf::Texture* MapInterface::currentTexture{};
unsigned int MapInterface::textureWidth;
std::vector<std::string> MapInterface::spriteSheets;

void MapInterface::findSpriteSheets()
{
	spriteSheets.clear();
	for (const auto& entry : std::filesystem::directory_iterator("spritesheets"))
	{
		spriteSheets.push_back(entry.path().string());
	}
}

void MapInterface::loadTextures()
{
	tileTextures.clear();
	findSpriteSheets();
	for (const std::string& path : spriteSheets)
	{
		sf::Texture texture;
		texture.loadFromFile(path);
		tileTextures.push_back(texture);
	}
	nextTexture();

}

void MapInterface::nextTexture()
{
	static unsigned int index = 0;
	currentTexture = &tileTextures[index];
	textureWidth = currentTexture->getSize().x / CELL_SIZE;
	index = (index + 1) % spriteSheets.size();
}

sf::Vector2i MapInterface::locateClick(const sf::Vector2f& click)
{
	return sf::Vector2i(click.x / CELL_SIZE + (click.x < 0 ? -1 : 0), click.y / CELL_SIZE + (click.y < 0 ? -1 : 0));
}


MapInterface::MapInterface(int windowWidth, int windowHeight)
	: sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)),
	linesView(sf::FloatRect(0, 0, windowWidth, windowHeight))
{

	uint vLinesAmount = 1 + gridWindowWidth / CELL_SIZE;
	uint hLinesAmount = 1 + gridWindowHeight / CELL_SIZE;

	hLines.setPrimitiveType(sf::Lines);
	vLines.setPrimitiveType(sf::Lines);
	hLines.resize(hLinesAmount * 2);
	vLines.resize(vLinesAmount * 2);

	for (uint i = 0; i < vLinesAmount; ++i)
	{
		vLines[i * 2].position = sf::Vector2f(i * CELL_SIZE, 0);
		vLines[i * 2 + 1].position = sf::Vector2f(i * CELL_SIZE, gridWindowHeight);
		vLines[i * 2].color = sf::Color::White;
		vLines[i * 2 + 1].color = sf::Color::White;
	}

	for (uint i = 0; i < hLinesAmount; ++i)
	{
		hLines[i * 2].position = sf::Vector2f(0, i * CELL_SIZE);
		hLines[i * 2 + 1].position = sf::Vector2f(gridWindowWidth, i * CELL_SIZE);
		hLines[i * 2].color = sf::Color::White;
		hLines[i * 2 + 1].color = sf::Color::White;
	}
}

void MapInterface::draw(sf::RenderWindow& window)
{
	window.setView(linesView);
	window.draw(hLines);
	window.draw(vLines);
	window.setView(*this);

	for (const Cell& cell : mapData)
	{
		window.draw(cell);
	}

}


void MapInterface::move(sf::Vector2f offset)
{
	setCenter(getCenter() + offset);
}

bool MapInterface::isFree(sf::Vector2i cellCoords)
{
	for (const Cell& cell : mapData)
	{
		if (cell.row == cellCoords.x && cell.col == cellCoords.y)
		{
			return false;
		}
	}
	return true;
}

Cell* MapInterface::locateCell(sf::Vector2i cellCoords)
{
	for (Cell& cell : mapData)
	{
		if (cell.col == cellCoords.x && cell.row == cellCoords.y)
		{
			return &cell;
		}
	}
	return nullptr;
}


void MapInterface::addCell(const sf::Vector2i& cellCoords)
{
	Cell* cell = locateCell(cellCoords);
	if (cell)
	{
		cell->setTexture(*currentTexture);
		cell->setTextureNum(currentTile);
		cell->setRotation(currentRotation * 90);
	} else
	{
		mapData.emplace_back(cellCoords, currentTile, currentRotation);
	}
}

void MapInterface::delCell(const sf::Vector2i& cellCoords)
{
	for (auto it = mapData.begin(); it != mapData.end(); ++it)
	{
		if (it->col == cellCoords.x && it->row == cellCoords.y)
		{
			mapData.erase(it);
			break;
		}
	}
}

void MapInterface::nextTile()
{
	currentTile = (currentTile + 1) % (textureWidth * textureWidth);
}

void MapInterface::prevTile()
{
	currentTile = (currentTile - 1) % (textureWidth * textureWidth);
}

void MapInterface::rotate()
{
	currentRotation = (currentRotation + 1) % 4;
}