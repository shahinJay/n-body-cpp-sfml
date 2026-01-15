#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <SFML/graphics.hpp>

//PHYSICS CLASS DECLARATION

class Physics {
public:
	const double G = 6e9;
	double step;

	Physics(double step);
	void apply_velocity(std::vector<Body>& bodies);
	

	void apply_arcade_gravity(std::vector<Body>& bodies, int ground);
};