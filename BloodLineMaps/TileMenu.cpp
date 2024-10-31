#include "TileMenu.hpp"


sf::Color TileMenu::backgroundColor(100, 100, 100, 200);
uint16_t TileMenu::backgroundWidth = 100;

TileMenu::TileMenu(int windowWidth, int windowHeight, const sf::Texture& tileset)
	: view(sf::FloatRect(0, 0, windowWidth, windowHeight)), tileset(tileset), cols(tileset.getSize().x / 64),
	selectedTile(sf::Vector2f(68, 68)), firstTile(0)
{
	background.setFillColor(backgroundColor);
	background.setPosition(windowWidth - backgroundWidth, 0);
	background.setOutlineThickness(1);
	background.setSize(sf::Vector2f(backgroundWidth, windowHeight));

	selectedTile.setFillColor(sf::Color::Green);
	selectedTile.setPosition(windowWidth - backgroundWidth / 2 - 34, 2 * spacing - 2 + 64);

	setFirstTiles(windowWidth - backgroundWidth / 2);

}

void TileMenu::setFirstTiles(uint16_t xPos)
{
	for (int i = 0; i < 10; ++i) {
		tiles.emplace_back(sf::Vector2f(64, 64));
		sf::RectangleShape& tile = tiles.back();
		tile.setTexture(&tileset);
		tile.setTextureRect(sf::IntRect((i % cols) * 64, (i / cols) * 64, 64, 64));
		tile.setOrigin(32, 32);
		tile.setPosition(xPos, 32 + spacing * (i + 1) + 64 * i);
	}
}

void TileMenu::moveDown() // Move tiles down, giving the appearance of scrolling up
{
	auto last = std::prev(tiles.end());
	for (auto it = tiles.begin(); it != last; ++it)
	{
		it->move(0, 64 + spacing);
	}
	last->setPosition(last->getPosition().x, 32 + spacing);
	firstTile = (firstTile - 1) % (cols * cols);
	if (firstTile < 0) firstTile += cols * cols;
	last->setTextureRect(sf::IntRect((firstTile % cols) * 64, (firstTile / cols) * 64, 64, 64));

	tiles.splice(tiles.begin(), tiles, last); // move last to the front
}

void TileMenu::moveUp() // Move tiles up, giving the appearance of scrolling down
{
	auto first = tiles.begin();
	for (auto it = std::next(first); it != tiles.end(); ++it)
	{
		it->move(0, -64 - spacing);
	}
	first->setPosition(first->getPosition().x, 32 + 9 * 64 + 10 * spacing);
	int tileNum = (firstTile + 10) % (cols * cols);
	firstTile = (firstTile + 1) % (cols * cols);
	first->setTextureRect(sf::IntRect((tileNum % cols) * 64, (tileNum / cols) * 64, 64, 64));

	tiles.splice(tiles.end(), tiles, first); // move first to the back
}

void TileMenu::rotate()
{
	for (sf::RectangleShape& tile : tiles)
	{
		tile.rotate(90);
	}
}


void TileMenu::draw(sf::RenderWindow& window)
{
	window.setView(view);
	window.draw(background);
	window.draw(selectedTile);
	for (const sf::RectangleShape& tile : tiles)
	{
		window.draw(tile);
	}
}


sf::FloatRect TileMenu::getGlobalBounds()
{
	return background.getGlobalBounds();
}


