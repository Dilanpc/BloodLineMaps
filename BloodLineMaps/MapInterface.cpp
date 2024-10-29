#include "MapInterface.hpp"

sf::Texture MapInterface::tileTexture;
unsigned int MapInterface::textureWidth;
void MapInterface::loadTexture()
{
	tileTexture.loadFromFile("../../BloodLine/BloodLine/resources/tilesets/city.jpg");
	textureWidth = tileTexture.getSize().x / 64;
}


sf::Vector2i MapInterface::locateClick(const sf::Vector2f& click)
{
	return sf::Vector2i(click.x / 64 + (click.x < 0 ? -1 : 0), click.y / 64 + (click.y < 0 ? -1 : 0));
}


MapInterface::MapInterface()
	: sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight)),
	linesView(sf::FloatRect(0, 0, windowWidth, windowHeight))
{

	uint vLinesAmount = 1 + windowWidth / 64;
	uint hLinesAmount = 1 + windowHeight / 64;

	hLines.setPrimitiveType(sf::Lines);
	vLines.setPrimitiveType(sf::Lines);
	hLines.resize(hLinesAmount * 2);
	vLines.resize(vLinesAmount * 2);

	for (uint i = 0; i < vLinesAmount; ++i)
	{
		vLines[i * 2].position = sf::Vector2f(i * 64, 0);
		vLines[i * 2 + 1].position = sf::Vector2f(i * 64, windowHeight);
		vLines[i * 2].color = sf::Color::White;
		vLines[i * 2 + 1].color = sf::Color::White;
	}

	for (uint i = 0; i < hLinesAmount; ++i)
	{
		hLines[i * 2].position = sf::Vector2f(0, i * 64);
		hLines[i * 2 + 1].position = sf::Vector2f(windowWidth, i * 64);
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
		if (cell.row == cellCoords.x && cell.col == cellCoords.y)
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
		cell->setTextureCoords(sf::Vector2i(currentTile % textureWidth, currentTile / textureWidth));
	} else
	{
		mapData.emplace_back(cellCoords, sf::Vector2i(currentTile % textureWidth, currentTile / textureWidth));
	}
}

void MapInterface::delCell(const sf::Vector2i& cellCoords)
{
	for (auto it = mapData.begin(); it != mapData.end(); ++it)
	{
		if (it->row == cellCoords.x && it->col == cellCoords.y)
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