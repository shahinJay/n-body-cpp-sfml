#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>

#include "body.h"
#include "physics.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({ 800,800 }), "my window");

	Physics phy(0.0001);

	Body body(10.0, 200, sf::Vector2f(300.f, 300.f), sf::Vector2f(0.03f, 0.0f), sf::Color::White);

	std::vector<Body> bodies;
	bodies.push_back(body);

	/*
	 NEXT: do two bodies, apply gravity logic in the physics class, 
	 use nested for loops for now, 
	
	*/ 

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		phy.apply_velocity(bodies);

		for (Body& b : bodies)
			window.draw(b.shape);
		window.display();
	}
}