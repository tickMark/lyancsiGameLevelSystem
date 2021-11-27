#pragma once 
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Animation.h"
#include "Tile.h"
#include "Collider.h"
#include "Consts.cpp"

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;
using namespace sf;

class Character
{
public:
	bool running = false;
	bool doLive = true;
	bool doMove = true;
public:

	Character(Vector2f startPos, Texture* texture, Vector2u imageCount, float jumpHeight, float gravityStrength, float mass = 1.0f, float switchTime = 500);
	//Character(const Vector2f startPos, const Texture* texture, const Vector2u imageCount, const float jumpHeight, const float gravityStrength, const float mass = 1.0f, const float switchTime = 500);
	Character();

	void Update(float deltaTime);

	float elapsedTime;

	void Draw(RenderWindow& window);
	void OnCollision(Vector2f direction);

	float RestartSpaceClock() { return spaceClock.restart().asMilliseconds(); }
	float RestartSpaceReleaseClock() { return spaceReleaseClock.restart().asMilliseconds(); }
	float RestartGroundedClock() { return groundedClock.restart().asMilliseconds(); }

	Vector2f GetPosition() { return body.getPosition(); };
	Vector2f GetSize() { return body.getSize(); };
	Collider GetCollider() { return Collider(body); };

	void setPosition(Vector2f position) { body.setPosition(position); }

	float accel; //1 if accelerating to the right, -1 if accelerating to the left

	bool isJumping = 0;
	float speed;
	Vector2f velocity;
	float jumpHeight;
	float gravityStrength;
	Vector2f collision;
	float dragconst = 0.45;
	float mass;

	float switchTime = 500;

	bool getGrounded()
	{
		return groundedClock.getElapsedTime().asMilliseconds() < AFTERJUMPTIME;
	}

	void Die()
	{
		body.setPosition(startPos);
		body.setScale(1, 1);
		velocity.x = 0;
		body.setFillColor(Color::Transparent);
	}

	void setColor(Color color) { body.setFillColor(color); };

	Tile levelBorder;
	Tile levelBorder2;

	RectangleShape body;
	Animation animation;
	void updateAnimation(float deltaTime);
	unsigned int row;
	float runStep;
	bool faceRight;

	Vector2f lastVelocity;

	void processCollisions();
	void drag(float deltaTime);

	float PREJUMPTIME = 100;
	float AFTERJUMPTIME = 100;
	Clock spaceClock;
	Clock spaceReleaseClock;
	Clock groundedClock;
	Clock doubleJumpTimer;

	Vector2f startPos;

	SoundBuffer jump;
	Sound jumpPlayer;


	bool noDrag = false;
};

#endif // !CHARACTER_H
