#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <deque>

class AppBase
{
public:
	virtual bool WinUpdate() = 0;
	virtual void Update() = 0;
	bool IsOpen() {
		return window.isOpen();
	}
protected:
	sf::RenderWindow window;
};