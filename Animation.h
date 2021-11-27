#pragma once 
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef ANIMATION_H
#define ANIMATION_H

using namespace std;
using namespace sf;
class Animation
{
public:

	Animation(Texture* texture, Vector2u imageCount);

	IntRect Update(int row, float deltaTime, float switchTime, bool faceRight);
	IntRect Update(int row, bool faceRight);
	void Reset() { currentImage.x = 0; };


	IntRect uvRect;
	bool doLoop;


	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
};

#endif // !ANIMATION_H