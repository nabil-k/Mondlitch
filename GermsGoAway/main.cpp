#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

int main()
{
	sf::Clock clock; // clock starts
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		
		sf::Time fiveSeconds = sf::seconds(5.f);

		// Game Exit
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() >= 5.f) {
			std::cout << "Five seconds has passed" << std::endl;
			clock.restart();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}