#pragma once

#include <iostream>
#include <math.h>
#include <SFML/graphics.hpp>
#include <vector>
#include <time.h>

#include "body.h"
#include "physics.h"
#include "quadtree.h"

Node::Node(sf::Vector2f position, double hw, sf::Vector2f c_o_m, double mass) {
	this->position = position;
	this->half_width = hw;
	
	this->c_o_m = c_o_m;
	this->mass = mass;
}

bool Node::within_bounds(sf::Vector2f position) {
	if (position.x > this->position.x && position.x < this->position.x + this->half_width*2 && position.y > this->position.y && position.y < this->position.y + this->half_width*2)
		return true;
	else
		return false;
}

void Node::split_and_insert(Body& body) {
	
	this->is_leaf = false;

	sf::Vector2f position = body.position;
	double mass = body.mass;
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
					this->nw = new Node(nw_pos, new_hw, c_o_m, mass); //create node object
				this->nw->insert(body); //insert body into node object
				this->nw->self_body = &body; //define contained body
			}
			// north - east
			else {
				if (this->ne == nullptr)
					this->ne = new Node(ne_pos, new_hw, c_o_m, mass); //create node object
				this->ne->insert(body); //insert body into node object
				this->ne->self_body = &body; //define contained body
				
			}
		}
		
		// south
		else {
			// south - west
			if (position.x < mid_x) {
				if (this->sw == nullptr)
					this->sw = new Node(sw_pos, new_hw, c_o_m, mass); //create node object
				this->sw->insert(body); //insert body into node object
				this->sw->self_body = &body; //define contained body
			}
			// south - east
			else {
				if (this->se == nullptr)
					this->se = new Node(se_pos, new_hw, c_o_m, mass); //creat node object
				this->se->insert(body); //insert body into node object
				this->se->self_body = &body; //define contained body
			}
		}
	}
}


void Node::insert(Body& body) {
	double total_m = this->mass + body.mass;

	//fix vector multiplication

	this->c_o_m = ((this->c_o_m * this->position * (float)this->mass ) + (body.position * (float)body.mass)) / total_m;
	
	if (this->is_leaf && this->contains==0) {//is leaf and is empty
		this->is_leaf = false;
		split_and_insert(body);
		
	}
	else if (is_leaf && this->contains == 1) {//is leaf and is NOT empty
		this->is_leaf = false;
		split_and_insert(*this->self_body);
		split_and_insert(body);
		this->contains = 0;
	}
	else{
		split_and_insert(body);
	}
}

Node::~Node()
{
	delete ne;
	delete nw;
	delete se;
	delete sw;
}

