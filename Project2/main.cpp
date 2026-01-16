#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <random>

#include "body.h"
#include "physics.h"

double random_range(double lower, double upper) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dist(lower, upper);

	return dist(gen);
}

void spawn(std::vector<Body>& bodies, int amount) {
	double radius, mass;
	sf::Vector2f position, velocity;
	sf::Color color = sf::Color::White;
	for (int i = 0; i < amount; i++)
	{
		radius = random_range(3.0, 5.0);
		mass = random_range(70.0, 200.0);

		position.x = random_range(-0, 800.0);
		position.y = random_range(-0, 800.0);

		velocity.x = random_range(-0.2, 0.2);
		velocity.x = random_range(-0.2, 0.2);

		Body new_body(radius, mass, position, velocity, color);

		bodies.push_back(new_body);
	}

}


int main() {
	sf::RenderWindow window(sf::VideoMode({ 800,800 }), "my window");

	Physics phy(0.00002);
	std::vector<Body> bodies;

	spawn(bodies, 10);

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
		phy.apply_gravity(bodies);

		for (Body& b : bodies)
			window.draw(b.shape);
		window.display();
	}
}