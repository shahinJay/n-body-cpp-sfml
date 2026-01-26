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

void spawn_random(std::vector<Body>& bodies, int amount) {
	double radius, mass;
	double mass_range_lower = 2e4;
	double mass_range_upper = 3e4;
	double radius_scale_factor = 2e4; // lower = bigger in scale
	double velocity_range = 10;
	sf::Vector2f position, velocity;//fix this
	sf::Color color = sf::Color::White;
	for (int i = 0; i < amount; i++)
	{
		mass = random_range(mass_range_lower, mass_range_upper);
		radius = mass / radius_scale_factor;

		position.x = random_range(-0, 800.0);
		position.y = random_range(-0, 800.0);

		velocity.x = random_range(-velocity_range, velocity_range);
		velocity.y = random_range(-velocity_range, velocity_range);

		Body new_body(radius, mass, position, velocity, color);

		bodies.push_back(new_body);
	}

}

void spawn_solar_system(Physics& phy, std::vector<Body>& bodies, int planets) {
	double central_mass = 1.9e17;
	double central_radius = 20.0;
	sf::Vector2f center_pos = sf::Vector2f(450+central_radius, 450+central_radius);


	double radius, mass;
	double mass_range_lower = 2e5;
	double mass_range_upper = 3e5;
	double radius_scale_factor =3e5; // lower = bigger in scale
	double red;
	double blue;
	double green;

	sf::Vector2f position, velocity;
	sf::Color color;

	Body sun(central_radius, central_mass, center_pos, sf::Vector2f(0.0f, 0.0f), sf::Color::White);
	bodies.push_back(sun);

	for (int i = 0; i < planets; i++)
	{
		mass = random_range(mass_range_lower, mass_range_upper);
		radius = mass / radius_scale_factor;
		position.x = random_range(0, 1000);
		position.y = random_range(0, 1000);
		

		red = random_range(200, 255);
		green = random_range(200, 255);
		blue = random_range(200, 255);
		
		color = sf::Color(red, green, blue);
		//color = sf::Color::White;
		
		velocity = phy.apply_circular_velocity(center_pos, central_mass, position);

		Body new_body(radius, mass, position, velocity, color);

		bodies.push_back(new_body);
	}
}

int main() {
	sf::Vector2u resolution = sf::Vector2u(1000, 1000);
	sf::RenderWindow window(sf::VideoMode(resolution), "n body sim");
	sf::Clock deltaclock;
	double delta = 0.001;

	int particles = 800; //number of particles

	Physics phy(resolution);
	std::vector<Body> bodies;

	//spawn_random(bodies, particles);
	spawn_solar_system(phy, bodies, particles);

	while (window.isOpen())
	{
		deltaclock.restart();
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		phy.apply_barnes_hut(bodies, delta);

		for (Body& b : bodies)
			window.draw(b.shape);

		window.display();
		delta = deltaclock.getElapsedTime().asSeconds();
		//std::cout << 1/delta << std::endl;
	}
}