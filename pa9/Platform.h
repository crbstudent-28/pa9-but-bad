#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class Platform {
public:
	sf::RectangleShape* rect;
	Platform(float x, float y) {
		rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(60, 10));
		posX = x;
		posY = y;
		left = posX - 30;
		right = posX + 30;
		rect->setPosition(sf::Vector2f(x, y));
		rect->setTexture(new sf::Texture(sf::Image("BounceTile.png")));
	}
	virtual int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) {
		dv->y -= 30;
		return 0;
	}
	virtual void update() {}
	void move(int y)
	{
		posY += y;
		rect->setPosition(sf::Vector2f(posX, posY));
	}
	bool colliding(sf::Vector2f pos, sf::Vector2f size)
	{
		bool isColliding = true;
		isColliding &= pos.y		  > posY - 30;
		isColliding &= pos.y - size.y < posY - 20;
		isColliding &= pos.x - size.x < right;
		isColliding &= pos.x		  > left;
		return isColliding;
	}
	//draw function needs a getter rather than a public member
	sf::RectangleShape getrect() {
		return *rect;
	}
	~Platform() {
		delete rect;
		rect = nullptr;
	}
protected:
	int posX, posY;
	float left, right;
};

class SuperPlatform : public Platform {
public:
	SuperPlatform(float x, float y)
	: Platform(x, y)
	{
		rect->setTexture(new sf::Texture(sf::Image("BouncyTile.png")));
	}
	
	int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) override {
		dv->y -= 60;
		return 0;
	}
};

class BreakPlatform : public Platform {
public:
	BreakPlatform(float x, float y) 
		: Platform(x, y)
	{
		rect->setTexture(new sf::Texture(sf::Image("BreakTile.png")));
	}

	int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) override {
		dv->y -= 30;
		return 1;
	}
};



class MovePlatform : public Platform {
public:
	MovePlatform(float x, float y)
		: Platform(x, y)
	{
		rect->setTexture(new sf::Texture(sf::Image("MovingTile.png")));
		currentShift = -50;
		dir = 1;
	}

	int trigger(sf::RectangleShape* doodler, sf::Vector2f* dv) override {
		dv->y -= 30;
		return 0;
	}

	void update()
	{
		if (currentShift < -50)
			dir = 1;
		if (currentShift > 50)
			dir = -1;

		currentShift += dir;
		posX += dir;
		left = posX - 30;
		right = posX + 30;
		rect->setPosition(sf::Vector2f(posX, posY));
	}
private:
	int currentShift;
	int dir;
};