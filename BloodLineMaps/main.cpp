#include <iostream>
#include <SFML/Graphics.hpp>

#include "MapInterface.hpp"
#include "TileMenu.hpp"


uint16_t const g_windowWidth = MapInterface::gridWindowWidth + TileMenu::backgroundWidth;
uint16_t const g_windowHeight = MapInterface::gridWindowHeight;

int main(int argc, const char* argv[])
{
	MapInterface::loadTexture();


	sf::RenderWindow window(sf::VideoMode(g_windowWidth, g_windowHeight), "BloodLineMaps");

	MapInterface* mapInterface = new MapInterface(g_windowWidth, g_windowHeight);
	TileMenu* tileMenu = new TileMenu(g_windowWidth, g_windowHeight, MapInterface::tileTexture);
	
	Cell::setTileset(MapInterface::tileTexture);



	sf::Vector2i keyInput(0, 0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();

				if (event.key.code == sf::Keyboard::W) keyInput.y = -1;
				if (event.key.code == sf::Keyboard::S) keyInput.y = 1;
				if (event.key.code == sf::Keyboard::A) keyInput.x = -1;
				if (event.key.code == sf::Keyboard::D) keyInput.x = 1;

				if (event.key.code == sf::Keyboard::Up) {
					tileMenu->moveDown();
					mapInterface->prevTile();
				}
				if (event.key.code == sf::Keyboard::Down) {
					tileMenu->moveUp();
					mapInterface->nextTile();
				}
				if (event.key.code == sf::Keyboard::R) {
					tileMenu->rotate();
					mapInterface->rotate();
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::W && keyInput.y == -1) keyInput.y = 0;
				if (event.key.code == sf::Keyboard::S && keyInput.y == 1) keyInput.y = 0;
				if (event.key.code == sf::Keyboard::A && keyInput.x == -1) keyInput.x = 0;
				if (event.key.code == sf::Keyboard::D && keyInput.x == 1) keyInput.x = 0;

			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				window.setView(*mapInterface);
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				sf::Vector2i cell = MapInterface::locateClick(mousePos); // This is the position of the cell that was clicked

				if (event.mouseButton.button == sf::Mouse::Left && !tileMenu->getGlobalBounds().contains(mousePos))
				{
					mapInterface->addCell(cell);
				}
				else if (event.mouseButton.button == sf::Mouse::Right && !tileMenu->getGlobalBounds().contains(mousePos))
				{
					mapInterface->delCell(cell);
				}
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0)
				{
					tileMenu->moveUp();
					mapInterface->nextTile();
				}
				else if (event.mouseWheelScroll.delta > 0)
				{
					tileMenu->moveDown();
					mapInterface->prevTile();
				}
			}
		}




		mapInterface->move(sf::Vector2f(keyInput) * 64.0f);

		window.clear();

		mapInterface->draw(window);
		tileMenu->draw(window);

		window.display();

		

		sf::sleep(sf::milliseconds(64));
	}
	delete mapInterface;
}