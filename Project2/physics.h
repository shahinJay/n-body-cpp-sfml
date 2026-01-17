#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/graphics.hpp>

//PHYSICS CLASS DECLARATION

class Physics {
public:
	const double G = 6e4;
	double step;
	double softening_factor = 0.0005;
	sf::Vector2f accel;


	Physics(double step);

	sf::Vector2f scale(sf::Vector2f, double scalar);

	void apply_velocity(std::vector<Body>& bodies);

	double distance(sf::Vector2f a, sf::Vector2f b);

	double normalize(double n);

	sf::Vector2f dir(sf::Vector2f a, sf::Vector2f b);

	void apply_gravity(std::vector<Body>& bodies);

	void apply_arcade_gravity(std::vector<Body>& bodies, int ground);
};