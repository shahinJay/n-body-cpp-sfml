#pragma once

#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>
#include <time.h>

#include "body.h"
#include "physics.h"

class Node {

	public:
		Node();
		double half_width;

		sf::Vector2f position;
		sf::Vector2f c_o_m;

		int contains = 0;
		int max_bodies = 1;
		
		Body* self_body = nullptr;

		double mass;

		bool is_leaf = true;


		Node *ne = nullptr;
		Node *nw = nullptr;
		Node *se = nullptr;
		Node *sw = nullptr;



	bool within_bounds(sf::Vector2f position);
	void split_and_insert(Body& body, sf::Vector2f position, double mass);

	void insert(Body& body);

	~Node();
};