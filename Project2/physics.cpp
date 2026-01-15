#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>

#include "body.h"
#include "physics.h"

//PHYSICS CLASS IMPLEMENTATION

Physics::Physics(double step) {
	this->step = step;
}

void Physics::apply_velocity(std::vector<Body>& bodies) {
	for (Body& b : bodies) {
		b.position -= b.velocity;
		std::cout << b.position.x << std::endl;
		b.shape.setPosition(b.position);
	}
}

void Physics::apply_arcade_gravity(std::vector<Body>& bodies, int ground) {
	double accel;
	for (Body& b : bodies) {
		accel = this->G / ((b.position.y - ground) * (b.position.y - ground));
		if (b.position.y < ground && b.velocity.y < 1000) {
			b.velocity.y += accel * this->step;
			b.position.y += b.velocity.y * this->step;

			b.shape.setPosition(b.position);
		}
		else {
			b.velocity.y == 0;
		}
		std::cout << b.position.y << std::endl;
	}

}




