#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/graphics.hpp>

#include "body.h"
#include "quadtree.h"

//PHYSICS CLASS DECLARATION

class Physics {
public:
	const double G = 6e-3;

	double step;
	double softening_factor = 0.0005;

	sf::Vector2f accel;

	Node* quad_root = nullptr;

	Physics(double step);

	sf::Vector2f scale(sf::Vector2f, double scalar);

	double distance(sf::Vector2f a, sf::Vector2f b);

	sf::Vector2f dir(sf::Vector2f a, sf::Vector2f b);

	double length(sf::Vector2f vec);

	void apply_velocity(std::vector<Body>& bodies);

	sf::Vector2f apply_circular_velocity(sf::Vector2f centre, double central_mass, sf::Vector2f pos);
	
	bool collision(double dist, double a_rad, double b_rad);

	void apply_gravity(std::vector<Body>& bodies, bool apply_boundary, double delta);
	
	void init_barnes_hut(std::vector<Body>& bodies);

	void apply_barnes_hut(std::vector<Body>& bodies, double delta);

	void apply_arcade_gravity(std::vector<Body>& bodies, int ground);
};