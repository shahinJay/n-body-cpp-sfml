#include <SFML/graphics.hpp>
#include "body.h"

Body::Body(double radius, double mass, sf::Vector2f position, sf::Vector2f velocity, sf::Color color) {
	this->radius = radius;
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->color = color;

	this->shape.setRadius(this->radius);
	this->shape.setFillColor(this->color);
	this->shape.setPosition(this->position);
}
