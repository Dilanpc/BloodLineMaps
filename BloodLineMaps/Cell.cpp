#include "Cell.hpp"

const sf::Texture* Cell::texture = nullptr;

Cell::Cell(const sf::Vector2i& gridCoords, const sf::Vector2i& textureCoords)
	: row(gridCoords.x), col(gridCoords.y), sf::Sprite(*texture)
{
	setTextureRect(sf::IntRect(64 * textureCoords.x, 64 * textureCoords.y, 64, 64));
	setPosition(row * 64, col * 64);
	
}


void Cell::setTexture(const sf::Texture& texture)
{
	Cell::texture = &texture;
}