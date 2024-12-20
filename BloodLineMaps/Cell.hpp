#pragma once


#include <SFML/Graphics.hpp>

enum rotation
{
	Up,	Right, Down, Left
};

class Cell : public sf::Sprite
{
	unsigned int m_tileNum;
	unsigned short m_transform;
public:
	Cell(const sf::Vector2i& gridCoords, const unsigned int tileNum, const uint8_t transform);
	Cell(const sf::Vector2i& gridCoords, const int code);

	int row;
	int col;

	void setTextureNum(unsigned int num);
	void setTransform(uint8_t transform);

	static const sf::Texture* texture;
	static void setTileset(const sf::Texture* texture);
	static unsigned int textureWidth;

	int getEncode() const;
};