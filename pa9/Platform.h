#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class Platform {
public:
	sf::RectangleShape* rect;
	//derived classes won't work without a default constructor
	Platform() {
		rect = new sf::RectangleShape;
	}
	Platform(float x, float y) {
		rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(60, 10));
		rect->setPosition(sf::Vector2f(x, y));
		rect->setFillColor(sf::Color::Green);
	}
	virtual int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) {
		dv->y -= 30;
		return 0;
	}
	//draw function needs a getter rather than a public member
	sf::RectangleShape getrect() {
		return *rect;
	}
	~Platform() {
		delete rect;
		rect = nullptr;
	}
};

class SuperPlatform : public Platform {
public:
	SuperPlatform(float x, float y) {
		rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(60, 10));
		rect->setPosition(sf::Vector2f(x, y));
		rect->setFillColor(sf::Color::Yellow);
	}
	
	int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) override {
		dv->y -= 60;
		return 0;
	}
};

class BreakPlatform : public Platform {
public:
	BreakPlatform(float x, float y) {
		rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(60, 10));
		rect->setPosition(sf::Vector2f(x, y));
		rect->setFillColor(sf::Color::Magenta);
	}

	int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) override {
		dv->y -= 30;
		return 1;
	}
};