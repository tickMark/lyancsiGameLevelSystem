#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Animation.h"
#include "Level.h"
#include "Tile.h"
#include "Collider.h"
#include "Character.h"
#include "Consts.cpp"

#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
using namespace sf;

class Player
{
public:
	Player(Vector2f startPos, Texture* texture, Vector2u imageCount, float jumpHeight, float gravityStrength);

	void Update(float deltaTime, Level& level);
	void Draw(RenderWindow& window);
	void OnCollision(Vector2f direction);

	float RestartSpaceClock() { return body.RestartSpaceClock(); }
	float RestartSpaceReleaseClock() { return body.RestartSpaceReleaseClock(); }
	float RestartGroundedClock() { return body.RestartGroundedClock(); }
	Vector2f GetPosition() { return body.GetPosition(); };

	Vector2f GetSize() { return body.GetSize(); };
	Collider GetCollider() { return body.GetCollider(); };
	bool isJumping() { return body.isJumping; };


	Character& GetCharatcterRef() { return body; }

	bool dead = false;

	float slowplayerpercent = 0.5f;

	Character body;

	float gravityStrength;
};
#endif // !PLAYER_H