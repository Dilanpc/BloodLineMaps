#include "Cell.hpp"

const sf::Texture* Cell::texture = nullptr;
unsigned int Cell::textureWidth = 0;

Cell::Cell(const sf::Vector2i& gridCoords, const unsigned int tileNum, const uint8_t rotationn)
	: row(gridCoords.y), col(gridCoords.x), sf::Sprite(*texture), m_tileNum(tileNum), m_rotation(rotationn)
{
	setTextureNum(m_tileNum);
	setOrigin(32, 32);
	setPosition(col * 64 + 32, row * 64 + 32);
	setRotation(m_rotation * 90);
}

Cell::Cell(const sf::Vector2i& gridCoords, const int code)
	: row(gridCoords.y), col(gridCoords.x), sf::Sprite(*texture)
{
	m_tileNum = code & 0x0000ffff;
	m_rotation = (code & 0x000f0000) >> 16;

	setTextureNum(m_tileNum);
	setOrigin(32, 32);
	setPosition(col * 64 + 32, row * 64 + 32);
	setRotation(m_rotation * 90);

}

void Cell::setTextureNum(const unsigned int num)
{
	m_tileNum = num;
	setTextureRect(sf::IntRect(64 * (num % textureWidth), 64 * (num / textureWidth), 64, 64));
}

void Cell::setTileset(const sf::Texture& texture)
{
	Cell::texture = &texture;
	textureWidth = texture.getSize().x / 64;
}

int Cell::getEncode() const
{
	return m_tileNum | (m_rotation << 16);
}