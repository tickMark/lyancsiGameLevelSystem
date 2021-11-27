#include "Tile.h"

Tile::Tile(Texture* tileset, Vector2i tileSize, Vector2u tilePosition, Vector2i position) : tileset(tileset), tileSize(tileSize), tilePosition(tilePosition), position(position)
{
}

void Tile::setTileset(Texture* tileset)
{
	this->tileset = tileset;
}

void Tile::setTileSize(Vector2i tileSize)
{
	this->tileSize = tileSize;
}

void Tile::setTilePosition(Vector2u tilePosition)
{
	this->tilePosition = tilePosition;
}

void Tile::setPosition(Vector2i position)
{
	this->position = position;
}

void Tile::updateTile()
{
	body.setSize(Vector2f(tileSize));
	body.setOrigin(Vector2f(tileSize.x / 2, tileSize.y / 2));
	body.setPosition(Vector2f((position.x * tileSize.x), (position.y * tileSize.y)));
	body.setTexture(tileset);
	tileRect = IntRect(tilePosition.x * tileSize.x, tilePosition.y * tileSize.y, tileSize.x, tileSize.y);
	body.setTextureRect(tileRect);
}

void Tile::Draw(RenderWindow& window)
{
	updateTile();
	window.draw(body);
}

Collider Tile::GetCollider()
{
	updateTile();
	return Collider(body);
}
