#pragma once

#include <SFML/Graphics.hpp>
#include "Cell.hpp"


class MapInterface : public sf::View
{
	using uint = unsigned int;
public:
	static const uint gridWindowWidth = 1280U;
	static const uint gridWindowHeight = 720U;
	// Returns the cell that was clicked
	static sf::Vector2i locateClick(const sf::Vector2f& click);

public:
	MapInterface(int windowWidth, int windowHeight);

	static void loadTexture();
	static sf::Texture tileTexture;
	static unsigned int textureWidth;


	void draw(sf::RenderWindow& window);

	void move(sf::Vector2f offset);

	Cell* locateCell(sf::Vector2i cellCoords);

	bool isFree(sf::Vector2i cellCoords);

	void addCell(const sf::Vector2i& cellCoords);
	void delCell(const sf::Vector2i& cellCoords);

	void nextTile();
	void prevTile();

//private:
	std::vector<Cell> mapData;

	sf::View linesView;
	sf::VertexArray hLines;
	sf::VertexArray vLines;

	unsigned int currentTile = 0;

};