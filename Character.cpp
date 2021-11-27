#include <iostream>
#include <math.h>
#include "Character.h"

Character::Character(Vector2f startPos, Texture* texture, Vector2u imageCount, float jumpHeight, float gravityStrength, float mass, float switchTime) :
	animation(texture, imageCount), levelBorder(nullptr, Vector2i(20, 720), Vector2u(0, 0), Vector2i(-1, 0)), levelBorder2(nullptr, Vector2i(20, 720), Vector2u(0, 0), Vector2i(-1, 0)), runStep(0)
{
	this->speed = 0.8;
	this->jumpHeight = jumpHeight;
	this->gravityStrength = gravityStrength;
	this->startPos = startPos;
	this->mass = mass;
	this->switchTime = switchTime;
	row = 0;
	faceRight = true;
	velocity = Vector2f(0.0f, 0.0f);
	accel = 0.0f;
	
	levelBorder.updateTile();

	body.setSize(Vector2f((texture->getSize().x / imageCount.x), (texture->getSize().y / imageCount.y)));
	body.setOrigin(GetSize().x / 2, GetSize().y / 2);
	body.setPosition(startPos);
	body.setTexture(texture);

	jump.loadFromFile("data/sounds/jump.ogg");
	jumpPlayer.setBuffer(jump);

	elapsedTime = 0.0f;
}

Character::Character()
	: 
	animation(nullptr, Vector2u(1, 1)),
	speed(0.8f),
	runStep(0),
	row(0),
	mass(1),
	jumpHeight(130),
	gravityStrength(GRAVITY_STRENGTH),
	faceRight(0),
	elapsedTime(0),
	accel(0)
{
}

void Character::Update(float deltaTime)
{
	elapsedTime += deltaTime;

	if (!doLive || !doMove)
		accel = 0;
	Vector2f bDirection = levelBorder.GetCollider().CheckCollision(GetCollider(), 1);
	if (bDirection != Vector2f(0, 0))
	{
		OnCollision(bDirection);
	}
	Vector2f cDirection = levelBorder2.GetCollider().CheckCollision(GetCollider(), 1);
	if (cDirection != Vector2f(0, 0))
	{
		OnCollision(cDirection);
	}

	if ((accel == 1 || accel == -1) && abs(velocity.x) > 15)
		running = true;

	this->processCollisions();

	velocity.x += speed * (deltaTime / 0.001f) * accel;
	if (groundedClock.getElapsedTime().asMilliseconds() < 5)
	{
		float slowdown = pow(0.994f, (deltaTime / 0.001f)); // slowdown in the x direction if the player is grounded (by the ground)
		if ((velocity.x < 0 && collision.x < 0) || (velocity.x > 0 && collision.x > 0))
		{
			velocity.x = 0;
		}
		else if(!running)
		{
			velocity.x *= slowdown;
		}
	}
	
	drag(deltaTime);

	collision = Vector2f(0, 0);
	accel = 0.0f;

	if (doLive && doMove)
	if (spaceClock.getElapsedTime().asMilliseconds() < PREJUMPTIME && groundedClock.getElapsedTime().asMilliseconds() < AFTERJUMPTIME && !isJumping && doubleJumpTimer.getElapsedTime().asMilliseconds() > AFTERJUMPTIME)
	{   //jump
		velocity.y = -sqrtf(2 * gravityStrength * jumpHeight);
		isJumping = true;
		jumpPlayer.play();
		doubleJumpTimer.restart();
	}
	else if (spaceReleaseClock.getElapsedTime().asMilliseconds() < 10 && isJumping)
	{	//cut jump
		if (velocity.y <= 0)
			velocity.y *= 0.5f;
		isJumping = false;
		doubleJumpTimer.restart();
	}

	velocity.y += gravityStrength * deltaTime; //gravity

	if (abs(velocity.x) < 6.0f)
	{	//velocity lower limit
		velocity.x = 0;
		running = false;
	}
	if (abs(velocity.x) > 140 + 140 * speed && !noDrag)
	{	//velocity upper limit
		velocity.x = abs(velocity.x) / velocity.x * (140 + 140 * speed);
	}
	body.move(velocity * deltaTime);

	this->updateAnimation(deltaTime);
}

void Character::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Character::OnCollision(Vector2f direction)
{
	if (abs(direction.x) > 0 && collision.x != direction.x)
		collision.x = direction.x;
	if (abs(direction.y) > 0 && collision.y != direction.y)
		collision.y = direction.y;
}

void Character::updateAnimation(float deltaTime)
{
	runStep += abs(velocity.x * deltaTime) / 4;
	if (running)
	{
		row = 1;

		if (velocity.x > 0.0f)
			faceRight = true;
		if (velocity.x < 0.0f)
			faceRight = false;

		while (runStep > 1)
		{
			animation.Update(row, faceRight);
			body.setTextureRect(animation.uvRect);
			if (groundedClock.getElapsedTime().asMilliseconds() < 50)
			{
				runStep -= 1;
			}
			else
			{
				runStep -= 6;
			}
		}
		running = false;
	}
	else
	{
		row = 0;
		animation.Update(row, deltaTime, switchTime, faceRight);
		body.setTextureRect(animation.uvRect);
		runStep = 0;
	}
}

void Character::processCollisions()
{
	if (collision != Vector2f(0, 0))
	{	//on collision
		if (collision.x > 0)
		{
			velocity.x = max(0.0f, velocity.x);
			accel = max(0.0f, accel);
		}
		if (collision.x < 0)
		{
			velocity.x = min(0.0f, velocity.x);
			accel = min(0.0f, accel);
		}
		if (collision.y < 0 && velocity.y > 0)
		{
			velocity.y = 0;
			groundedClock.restart();
		}
		if (collision.y > 0 && velocity.y < 0)
		{
			velocity.y = 0;
		}
	}
}

void Character::drag(float deltaTime)
{
	if (noDrag)
		return;
	if (deltaTime != 0)
	{
		velocity.x *= powf(2.718281, float(-dragconst / mass * deltaTime));
		velocity.y *= powf(2.718281, float(-dragconst / mass * deltaTime));
	}
}