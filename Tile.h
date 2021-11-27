#pragma once
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Collider.h"

#ifndef TILE_H
#define TILE_H

using namespace std;
using namespace sf;

class Tile
{
public:
	Tile(Texture* tileset, Vector2i tileSize, Vector2u tilePosition, Vector2i position);
	Tile() : tileset(nullptr) {};
	~Tile() {};

	void setTileset(Texture* tileset);
	void setTileSize(Vector2i tileSize);
	void setTilePosition(Vector2u tilePosition);
	void setPosition(Vector2i position);
	float getX() { return body.getPosition().x; }
	float getY() { return body.getPosition().y; }

	void updateTile();
	void Draw(RenderWindow& window);
	Collider GetCollider();

	RectangleShape body;
	IntRect tileRect;

	Texture* tileset;
	Vector2i tileSize;
	Vector2u tilePosition;
	Vector2i position;
};

#endif // !TILE_H