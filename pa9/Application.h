#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <deque>

class App
{
public:
	App();
	void WinUpdate();
	void Update();
	void Render();
	bool IsOpen();
private:
	sf::RenderWindow window;
private:
	sf::RectangleShape doodler;
	sf::Vector2f doodlerVelocity;
	std::deque<Platform*> platforms;
	sf::Font font;
	bool inLevel;
	bool ml;
	bool mr;
	int score;
	int nextPlat;
};