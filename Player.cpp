#include "Player.h"

Player::Player(Vector2f startPos, Texture* texture, Vector2u imageCount, float jumpHeight, float gravityStrength)
	:
	body(startPos, texture, imageCount, jumpHeight, gravityStrength),
	gravityStrength(gravityStrength)
{
}

void Player::Update(float deltaTime, Level& level)
{

	body.speed = 0.8f * slowplayerpercent;

	body.accel = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A))
		body.accel -= 1.0f;
	if (Keyboard::isKeyPressed(Keyboard::D))
		body.accel += 1.0f;
	body.Update(deltaTime);

	level.Collide(body);
}

void Player::Draw(RenderWindow& window)
{
	if (body.body.getFillColor() != Color(123, 123, 420, 0))
	{
		body.Draw(window);
	}
}

void Player::OnCollision(Vector2f direction)
{
	body.OnCollision(direction);
}