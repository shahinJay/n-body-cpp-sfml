#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>
#include <time.h>

#include "body.h"
#include "physics.h"
#include "quadtree.h"

//PHYSICS CLASS IMPLEMENTATION

Physics::Physics(double step) {
	this->step = step;
}

sf::Vector2f Physics::scale(sf::Vector2f vec, double scalar) {
	return sf::Vector2f(vec.x * scalar, vec.y * scalar);
}

double Physics::distance(sf::Vector2f a, sf::Vector2f b) {
	double x_comp = (b.x - a.x) * (b.x - a.x);
	double y_comp = (b.y - a.y) * (b.y - a.y);

	return (sqrt(x_comp + y_comp));
}

sf::Vector2f Physics::dir(sf::Vector2f a, sf::Vector2f b) {
	double dist = distance(a, b);

	if (dist == 0)
		return sf::Vector2f(0, 0);

	return sf::Vector2f((b.x - a.x) / dist, (b.y - a.y) / dist);
}

double Physics::length(sf::Vector2f vec) {
	return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

void Physics::apply_velocity(std::vector<Body>& bodies) {
	for (Body& b : bodies) {
		b.position -= b.velocity;
		std::cout << b.position.x << std::endl;
		b.shape.setPosition(b.position);
	}
}

sf::Vector2f Physics::apply_circular_velocity(sf::Vector2f center, double central_mass, sf::Vector2f pos) {
	sf::Vector2f direction = sf::Vector2f(dir(center, pos));
	return sf::Vector2f(-direction.y * sqrt(G * central_mass / distance(center, pos)), direction.x * sqrt(G * central_mass / distance(center, pos)));
}

bool Physics::collision(double dist, double a_rad, double b_rad) {
	if (dist < a_rad + b_rad)
		return true;
	else
		return false;
}

void Physics::apply_brute_force_gravity(std::vector<Body>& bodies, bool apply_boundary, double delta) {

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

				b.velocity += scale(this->accel, delta); //velocity update
			}
		}

		if (apply_boundary) {
			if (b.position.x - b.radius < 0 || b.position.x + b.radius > 800) {
				b.velocity.x *= -1 / 1.1;
			}
			else if (b.position.y - b.radius < 0 || b.position.y + b.radius > 800) {
				b.velocity.y *= -1 / 1.1;
			}
		}
		b.position += scale(b.velocity, delta); //position update
		b.shape.setPosition(b.position);


	}
}

void Physics::apply_gravity(Body& b, sf::Vector2f b2pos, double mass, double dist, double delta) {
	this->accel.x = (dir(b.position, b2pos).x * this->G * mass) / ((dist * dist) + softening_factor);
	this->accel.y = (dir(b.position, b2pos).y * this->G * mass) / ((dist * dist) + softening_factor);
	
	b.velocity += scale(this->accel, delta);//velocity update
	
}

void Physics::traverse_quadtree(Body& b, Node& curr, double delta) {
	
	if (curr.self_body == &b ) return;
	

	double s = 2 * curr.half_width;
	double d = distance(b.position, curr.c_o_m);

	if (d == 0) return;
	
	if (curr.is_leaf || s/d <0.5) {
		
		apply_gravity(b, curr.c_o_m, curr.mass, d, delta);
	}
	else{
		if (curr.nw) traverse_quadtree(b, *curr.nw, delta);
		if (curr.ne) traverse_quadtree(b, *curr.ne, delta);
		if (curr.sw) traverse_quadtree(b, *curr.sw, delta);
		if (curr.se) traverse_quadtree(b, *curr.se, delta);
	}
}

void Physics::apply_barnes_hut(std::vector<Body>& bodies, double delta) {
	delete this->quad_root;
	this->quad_root = new Node(sf::Vector2(0.f,0.f), 400, sf::Vector2f(400.f,400.f),0);

	for (Body& b : bodies) {
		quad_root->insert(b);
	}
	Node& curr = *this->quad_root;
	for (Body& b : bodies) {
		traverse_quadtree(b, curr, delta);
		
		b.position += scale(b.velocity, delta); //position update
		b.shape.setPosition(b.position);// setting position
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




