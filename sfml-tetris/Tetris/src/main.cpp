#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Blocks.h"

int main()
{
	sf::RenderWindow window{ sf::VideoMode(320, 640), "Tetris Game" };
	sf::Event event;
	sf::Clock clock;
	Blocks b;


	while (window.isOpen())
	{	
		srand(static_cast<unsigned int>(time(NULL)));
		sf::Time time{ clock.getElapsedTime() };
		b.fall(time, clock);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) b.rotate();
				if (event.key.code == sf::Keyboard::Left) b.move(sf::Vector2i(-1, 0));
				else if (event.key.code == sf::Keyboard::Right) b.move(sf::Vector2i(1, 0));				
			}
		}
		window.clear(sf::Color::White);
		b.draw(window);
		window.display();
		
	}
}