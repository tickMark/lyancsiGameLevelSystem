#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <cmath>
#include "Player.h"
#include "Level.h"
#include "Consts.cpp"
#include "Fade.h"

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

class Gameplay
{
public:
	Gameplay(RenderWindow* window, Font& font, Texture* playerTexture, Texture* tileset, int levelnumber);
	void Update(float deltaTime, RenderWindow& window);
	void Draw(RenderWindow& window);
	void Win()
	{
		won = true;
	}
	bool won = false;


	bool Isjumping() { return player.isJumping(); }
	Clock& Spaceclock() { return player.body.spaceClock; }
	Clock& Spacereleaseclock() { return player.body.spaceReleaseClock; }

	Level level;
	Player player;

	FloatRect levelBounds;

	bool doRestart = false;
	bool doClose = false;
	bool doContinue = false;

	Fade fade;
	Clock noTouch;
};

#endif // !GAMEPLAY_H



