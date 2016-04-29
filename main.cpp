#include <SFML\Graphics.hpp>
#include "Pacman.h"
#include "PacmanGame.h"
int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	// Создаём окно игры
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pacman");

	PacmanGame game;

	// Создаём таймер
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			game.processEvent(event);
		}

		game.update(clock);

		game.draw(window);

		window.display();
	}
	return 0;
}