#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef BLACKBARS_H
#define BLACKBARS_H

using namespace std;
using namespace sf;

class Blackbars
{
public:

	Blackbars(RenderWindow& window, View& view, float viewWidth, float viewHeight);
	void UpdateSize();
	void UpdatePosition();
	void Draw();

private:
	RenderWindow& window;
	View& view;
	float viewWidth;
	float viewHeight;

	float blackbarSideSize = 0.0f;
	float blackbarTopSize = 0.0f;
	vector<RectangleShape> blackbar;

};

#endif // !BLACKBARS_H