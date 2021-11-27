#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>
using namespace std;
using namespace sf;

#ifndef FADE_H
#define FADE_H
class Fade
{
public:
	Fade(Clock* clock, bool doFadeIn, float duration, float startTime = 0, Color color = Color(0, 0, 0, 255));
	void Draw(RenderWindow& window);
	bool drawAfterFinish = false;
private:
	bool doDraw = true;
	bool doRectInit = true;
	RectangleShape rect;

	void UpdateColor();
	bool doUpdate = true;

	Clock* clock;
	bool doFadeIn;
	float duration;
	float startTime;
	Color color;
};
#endif // !FADE_H