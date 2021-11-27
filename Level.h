#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "Character.h"
#include "Tile.h"

#ifndef LEVEL_H
#define LEVEL_H

using namespace std;
using namespace sf;

class Level
{
public:
	Level(Texture* tileset, Vector2i tileSize, int levelNumber);
	Level();
	~Level();

	void Load();
	void Unload();
	void Draw(RenderWindow& window);
	void Collide(Character& character, float ledgeTreshold = 0.6f);
	FloatRect GetBounds();

	vector<unsigned int> GetTileVector() { return tileType; };
	Vector2u GetSize() { return levelSize; };

	Texture* tileset;
	Vector2i tileSize;
	Vector2u levelSize;

	int levelNumber;
	string filename;

	vector<unsigned int> tileType;
	vector<Tile> tile;
};

#endif // !LEVEL_H
