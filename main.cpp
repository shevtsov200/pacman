#include <SFML\Graphics.hpp>
#include "Pacman.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman");

	Pacman pacman;


	sf::Clock clock;
	clock.restart();


	while (window.isOpen())
	{
		sf::Event event;
		
		if (event.type = sf::Event::KeyPressed)
		{
			pacman.changeDirection();
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		pacman.update(clock);

		window.clear(sf::Color::Black);
		window.draw(pacman);
		window.display();
	}
	return 0;
}