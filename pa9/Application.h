#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <deque>
#include "ApplicationBase.h"

class App : public AppBase
{
public:
	App();
	bool WinUpdate();
	void Update();
	bool IsOpen();
	void ResetLevel();
private:
	sf::RectangleShape doodler;
	sf::RectangleShape back;
	sf::Vector2f doodlerVelocity;
	std::deque<Platform*> platforms;
	sf::Font font;
	bool inLevel;
	bool ml;
	bool mr;
	int score;
	int nextPlat;
	int backPos;
};