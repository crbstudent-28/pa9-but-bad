#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <deque>
#include "ApplicationBase.h"

class TestApp : public AppBase
{
public:
	TestApp();
	bool WinUpdate();
	void Update();
private:
	sf::RectangleShape doodler;
	sf::RectangleShape back;
	sf::Vector2f doodlerVelocity;
	std::deque<Platform*> platforms;
	sf::Font font;
	bool inLevel;
	bool ml;
	bool mr;
};