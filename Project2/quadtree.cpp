#pragma once

#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>
#include <time.h>

#include "body.h"
#include "physics.h"
#include "quadtree.h"

Node::Node() {
	this->half_width = 400;
	this->position = sf::Vector2f(0, 0);
	this->c_o_m = sf::Vector2f(400.f, 400.f);
	this->mass = 0;
}

bool Node::within_bounds(sf::Vector2f position) {
	if (position.x > this->position.x && position.x < this->position.x + this->half_width*2 && position.y > this->position.y && position.y < this->position.y + this->half_width*2)
		return true;
	else
		return false;
}

void Node::split_and_insert(Body& body, sf::Vector2f position, double mass) {
	//within bounds
	double pos_x = this->position.x;
	double pos_y = this->position.y;
	double new_hw = this->half_width / 2;

	double mid_x = pos_x + this->half_width;
	double mid_y = pos_y + this->half_width;
	sf::Vector2f center = sf::Vector2f(pos_x + new_hw, pos_y + new_hw);
	

	sf::Vector2f nw_pos = sf::Vector2f(pos_x, pos_y);
	sf::Vector2f ne_pos = sf::Vector2f(pos_x +this->half_width, pos_y);
	sf::Vector2f sw_pos = sf::Vector2f(pos_x, pos_y + this->half_width);
	sf::Vector2f se_pos = sf::Vector2f(pos_x + this->half_width, pos_y + this->half_width);



	if (within_bounds(position)) {

		// north 
		if (position.y < mid_y) {
			// north - west
			if (position.x < mid_x) {
				if (this->nw == nullptr)
					this->nw = new Node(); //create node object
				this->nw->insert(body); //insert body into node object
				this->half_width = new_hw;
				this->position = position;
				this->c_o_m = position;// !_!_!_!_!_!_!_!_!_!_!_!_
				this->mass = mass;
				this->nw->self_body = &body; //define contained body
			}
			// north - east
			else {
				if (this->ne == nullptr)
					this->ne = new Node(); //create node object
				this->half_width = new_hw;
				this->position = position;
				this->c_o_m = position;// !_!_!_!_!_!_!_!_!_!_!_!_
				this->mass = mass;
				this->ne->insert(body); //insert body into node object
				this->ne->self_body = &body; //define contained body
				
			}
		}
		
		// south
		else {
			// south - west
			if (position.x < mid_x) {
				if (this->sw == nullptr)
					this->sw = new Node(); //create node object
				this->half_width = new_hw;
				this->position = position;
				this->c_o_m = position;// !_!_!_!_!_!_!_!_!_!_!_!_
				this->mass = mass;
				this->sw->insert(body); //insert body into node object
				this->sw->self_body = &body; //define contained body
			}
			// south - east
			else {
				if (this->se == nullptr)
					this->se = new Node(); //creat node object
				this->half_width = new_hw;
				this->position = position;
				this->c_o_m = position; // !_!_!_!_!_!_!_!_!_!_!_!_
				this->mass = mass;
				this->se->insert(body); //insert body into node object
				this->se->self_body = &body; //define contained body
			}
		}
	}
}


void Node::insert(Body& body) {
	if (!this->is_leaf) { // not a leaf
		//pass
	}
	else if (this->is_leaf && this->contains == 0) { // is leaf and is empty
		this->self_body = &body;
		this->contains += 1;
	}
	else if (this->is_leaf && this->contains > 0) { // is leaf and is full
		split_and_insert(*this->self_body, this->self_body->position, this->self_body->mass);
		split_and_insert(body, body.position, body.mass);
		this->contains -= 1;
	}
}

Node::~Node()
{
	delete ne;
	delete nw;
	delete se;
	delete sw;
}

