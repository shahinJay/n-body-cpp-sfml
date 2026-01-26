#pragma once

#include <SFML/graphics.hpp>

class Body {
	public:
		double radius;
		double mass;
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::CircleShape shape;
		sf::Color color;

	Body(double radius, double mass, sf::Vector2f position, sf::Vector2f velocity, sf::Color color);

	void set_position(sf::Vector2f new_pos);
};