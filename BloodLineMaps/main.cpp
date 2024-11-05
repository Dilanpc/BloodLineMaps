#include <iostream>
#include <SFML/Graphics.hpp>

#include "MapInterface.hpp"
#include "TileMenu.hpp"
#include "FileManager.hpp"


uint16_t const g_windowWidth = MapInterface::gridWindowWidth + TileMenu::backgroundWidth;
uint16_t const g_windowHeight = MapInterface::gridWindowHeight;

int main(int argc, const char* argv[])
{
	MapInterface::loadTextures();


	sf::RenderWindow window(sf::VideoMode(g_windowWidth, g_windowHeight), "BloodLineMaps");

	MapInterface* mapInterface = new MapInterface(g_windowWidth, g_windowHeight);
	TileMenu* tileMenu = new TileMenu(g_windowWidth, g_windowHeight, MapInterface::currentTexture);
	
	Cell::setTileset(MapInterface::currentTexture);

	sf::Vector2i keyInput(0, 0);
	sf::Clock saveTimer;
	sf::Time saveTime = sf::seconds(5 * 60); // 5 minutes



	// Open last map
	File::openMap(mapInterface);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();

				else if (event.key.code == sf::Keyboard::W) keyInput.y = -1;
				else if (event.key.code == sf::Keyboard::S) keyInput.y = 1;
				else if (event.key.code == sf::Keyboard::A) keyInput.x = -1;
				else if (event.key.code == sf::Keyboard::D) keyInput.x = 1;

				else if (event.key.code == sf::Keyboard::Up) {
					tileMenu->moveDown();
					mapInterface->prevTile();
				}
				else if (event.key.code == sf::Keyboard::Down) {
					tileMenu->moveUp();
					mapInterface->nextTile();
				}
				else if (event.key.code == sf::Keyboard::R || event.key.code == sf::Keyboard::Right) {
					tileMenu->rotate();
					mapInterface->rotate();
				}
				else if (event.key.code == sf::Keyboard::G) {
					File::saveMap(mapInterface);
				}
				else if (event.key.code == sf::Keyboard::T) {
					MapInterface::nextTexture();
					tileMenu->setTileset(MapInterface::currentTexture);
					Cell::setTileset(MapInterface::currentTexture);
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

		if (saveTimer.getElapsedTime() > saveTime)
		{
			File::saveMap(mapInterface);
			saveTimer.restart();
		}

		sf::sleep(sf::milliseconds(64));
	}
	delete mapInterface, tileMenu;
}