#pragma once

#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>
#include <time.h>

#include "body.h"
#include "physics.h"

class quadtree {

	struct node {
		double half_width;
		sf::Vector2f centre;
		sf::Vector2f c_o_m;

		struct node* ne;
		struct node* nw;
		struct node* se;
		struct node* sw;

		double mass;
	};

	void insert(std::vector<Body>& bodies) {
		//for each body
		//check for underflow
		//if not, check root
		//if root not empty, 
		// temp = root.body, 
		// make 4 new nodes , assign bodies, and link correctly to the right region,
		//if root is empty, 
		//create a node and put the curr body there

	}

};