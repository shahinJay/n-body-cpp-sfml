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

sf::Vector2f Physics::scale(sf::Vector2f vec, double scalar) {
	return sf::Vector2f(vec.x * scalar, vec.y * scalar);
}

void Physics::apply_velocity(std::vector<Body>& bodies) {
	for (Body& b : bodies) {
		b.position -= b.velocity;
		std::cout << b.position.x << std::endl;
		b.shape.setPosition(b.position);
	}
}

double Physics::distance(sf::Vector2f a, sf::Vector2f b) {
	double x_comp = (b.x - a.x) * (b.x - a.x);
	double y_comp = (b.y - a.y) * (b.y - a.y);

	return (sqrt(x_comp + y_comp));
}

double Physics::normalize(double n) {
	if (n > 0)
		return 1;
	else if (n < 0)
		return -1;
	else
		return 0;
}

sf::Vector2f Physics::dir(sf::Vector2f a, sf::Vector2f b) {
	double x_comp = normalize(b.x - a.x);
	double y_comp = normalize(b.y - a.y);

	return sf::Vector2f(x_comp, y_comp);
}

bool Physics::collision(double dist, double a_rad, double b_rad) {
	if (dist < a_rad + b_rad)
		return true;
	else
		return false;
}

void Physics::apply_gravity(std::vector<Body>& bodies) {

	for (Body& b : bodies) {
		Body& curr = b;
		for (Body& b2 : bodies) {
			if (&b != &b2 && distance(b.position, b2.position) > b2.radius + 1.0) {

				double dist = distance(b.position, b2.position);

				if (collision(dist, b.radius, b2.radius)) {
					sf::Vector2f temp = b.velocity;
					b.velocity = b2.velocity;
					b2.velocity = temp;
				}

				this->accel.x = (dir(b.position, b2.position).x * this->G * b2.mass) / ((dist * dist) + softening_factor); 
				this->accel.y = (dir(b.position, b2.position).y * this->G * b2.mass) / ((dist * dist) + softening_factor);

				b.velocity += scale(this->accel, this->step);
				b.position += scale(b.velocity, this->step);
			}
		}
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
			b.velocity.y = 0;
		}
		std::cout << b.position.y << std::endl;
	}

}




