#include "Cell.hpp"

const sf::Texture* Cell::texture = nullptr;
unsigned int Cell::textureWidth = 0;

Cell::Cell(const sf::Vector2i& gridCoords, const unsigned int tileNum, const uint8_t transform)
	: row(gridCoords.y), col(gridCoords.x), sf::Sprite(*texture), m_tileNum(tileNum), m_transform(transform)
{
	setTextureNum(m_tileNum);
	setOrigin(32, 32);
	setPosition(col * 64 + 32, row * 64 + 32);
	setTransform(transform);
}

Cell::Cell(const sf::Vector2i& gridCoords, const int code)
	: row(gridCoords.y), col(gridCoords.x), sf::Sprite(*texture)
{
	m_tileNum = code & 0x0000ffff;
	m_transform = (code & 0x00070000) >> 16;

	setTextureNum(m_tileNum);
	setOrigin(32, 32);
	setPosition(col * 64 + 32, row * 64 + 32);
	setTransform(m_transform);

}

void Cell::setTextureNum(const unsigned int num)
{
	m_tileNum = num;
	setTextureRect(sf::IntRect(64 * (num % textureWidth), 64 * (num / textureWidth), 64, 64));
}

void Cell::setTransform(const uint8_t transform)
{
	m_transform = transform; 
	setRotation((m_transform & 0b11) * 90); // first 2 bits are the rotation
	if (transform & 0b100) scale(-1, 1); // 3th bit is the mirror
}

void Cell::setTileset(const sf::Texture* texture)
{
	Cell::texture = texture;
	textureWidth = texture->getSize().x / 64;
}

int Cell::getEncode() const
{
	return m_tileNum | (m_transform << 16);
}