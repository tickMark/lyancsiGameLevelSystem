#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef COLLIDER_H
#define COLLIDER_H

using namespace std;
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);

	void Move(float dx, float dy) { body.move(dx, dy); }

	Vector2f CheckCollision(Collider other, float push);
	Vector2f GetPosition() { return body.getPosition(); };
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; };

	RectangleShape& body;
};


#endif // !COLLIDER_H