#pragma once


#include <SFML/Graphics.hpp>


class Cell : public sf::Sprite
{
public:
	Cell(const sf::Vector2i& gridCoords, const sf::Vector2i& textureCoords);

	int row;
	int col;

	void setTextureCoords(const sf::Vector2i& textureCoords);

	static const sf::Texture* texture;
	static void setTileset(const sf::Texture& texture);
};