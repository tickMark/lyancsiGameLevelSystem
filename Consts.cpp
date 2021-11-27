#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
#ifndef CONSTS
const float VIEW_WIDTH = 640.0f;
const float VIEW_HEIGHT = 360.0f;
const unsigned int TILE_WIDTH = 20;
const unsigned int TILE_HEIGHT = 20;
const float GRAVITY_STRENGTH = 750.0f;
const Color BACKGROUND_COLOR = Color(40, 222, 210, 255);
const float PI = 3.141592;
const char ABOUT_STRING[] = "Lyancsi is a short, weak, dumb, annoying boy, who has an even more annoying little brother, Matthew.\nIn this game, you\'ll get to experience what it feels like to get chased down and beaten by your younger siblings, while hardly being able to do anything about it.\nYour only escape is the dummy. When you place it, you become invisible to Matthew who still thinks he is seeing you. After he gets closer though, the dummy disappears, leaving Matthew bamboozled, and far away from you.\nYou complete levels by quickly platforming through them from left to right, but it is important to count every step and use the dummy wisely, because if Matthew catches you, it\'s game over.\nGood luck surviving the chaos of being Lyancsi.";
const char ITCH_URL[] = "https://tickmark.itch.io/lyancsi";
#ifndef _DEBUG
const bool IS_DEBUG = false;
#endif // !_DEBUG
#ifdef _DEBUG
const bool IS_DEBUG = true;
#endif // _DEBUG

#endif // !CONSTS