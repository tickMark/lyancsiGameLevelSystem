#include "Gameplay.h"

Gameplay::Gameplay(RenderWindow* window, Font& font, Texture* playerTexture, Texture* tileset, int levelnumber)
	:
	level(tileset, Vector2i(TILE_WIDTH, TILE_HEIGHT), levelnumber),
	player(Vector2f(0, 300), playerTexture, Vector2u(8, 2), 130, GRAVITY_STRENGTH),
	levelBounds(level.GetBounds()),
	fade(&noTouch, 1, 2000)
{
	noTouch.restart();
	switch (levelnumber)
	{
	case 1:
		player.body.startPos = Vector2f(0, 295);
		player.slowplayerpercent = 0.8f;
		break;
	default:
		cout;
	}
}

void Gameplay::Update(float deltaTime, RenderWindow& window)
{
	player.Update(deltaTime, level);

	if (noTouch.getElapsedTime().asSeconds() < 1)
	{
		player.body.setPosition(player.body.startPos);
		player.body.velocity = Vector2f();
	}
}

void Gameplay::Draw(RenderWindow& window)
{
	level.Draw(window);
	player.Draw(window);
	fade.Draw(window);
}
