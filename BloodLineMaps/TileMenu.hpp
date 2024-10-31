#pragma once

#include <SFML/Graphics.hpp>
#include <list>

class TileMenu
{
	sf::View view;
	sf::RectangleShape background;
	const sf::Texture& tileset;
	const uint16_t cols;

	sf::RectangleShape selectedTile;

	std::list<sf::RectangleShape> tiles;
	uint16_t spacing = 10;

	uint16_t firstTile = 0;

	void setFirstTiles(uint16_t xPos);

public:
	static sf::Color backgroundColor;
	static uint16_t backgroundWidth;

public:
	TileMenu(int windowWidth, int windowHeight, const sf::Texture& tileset);
	void draw(sf::RenderWindow& window);

	void moveDown();
	void moveUp();

	void rotate();

	sf::FloatRect getGlobalBounds();
};