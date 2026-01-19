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
	double mass_range_lower = 250.0;
	double mass_range_upper = 900.0;
	double radius_scale_factor = 50; // lower = bigger in scale
	double velocity_range = 5;
	sf::Vector2f position, velocity;
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

	sf::Vector2f center_pos = sf::Vector2f(350.0, 350.0);
	

	double central_mass = 3e7;
	double central_radius = 24.0;

	double radius, mass;
	double mass_range_lower = 5.0;
	double mass_range_upper = 10.0;
	double radius_scale_factor =2; // lower = bigger in scale
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

		position.x = random_range(0, 800);
		position.y = random_range(0, 800);

		red = random_range(5, 255);
		green = random_range(5, 255);
		blue = random_range(5, 255);
		
		color = sf::Color(red, green, blue);
		//color = sf::Color::White;

		
		
		velocity = phy.apply_circular_velocity(center_pos, central_mass, position);

		Body new_body(radius, mass, position, velocity, color);

		bodies.push_back(new_body);
	}
}


int main() {
	
	sf::RenderWindow window(sf::VideoMode({ 800,800 }), "my window");
	sf::Clock deltaclock;
	double delta = 0.001;

	Physics phy(0.00002);
	std::vector<Body> bodies;

	//spawn_random(bodies, 8);
	spawn_solar_system(phy, bodies, 15);

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
		phy.apply_gravity(bodies, false, delta);

		for (Body& b : bodies)
			window.draw(b.shape);

		window.display();
		delta = deltaclock.getElapsedTime().asSeconds();

	}
}