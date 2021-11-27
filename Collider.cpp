#include "Collider.h"

Collider::Collider(RectangleShape& body) :
	body(body)
{
}

Vector2f Collider::CheckCollision(Collider other, float push)
{
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (thisHalfSize.x + otherHalfSize.x);
	float intersectY = abs(deltaY) - (thisHalfSize.y + otherHalfSize.y);

	Vector2f direction = Vector2f(0, 0);

	if (body.getGlobalBounds().contains(other.GetPosition()))
	{
		Move(deltaX * intersectX * (1.0f - push), deltaY * intersectY * (1.0f - push));
		other.Move(-deltaX * intersectX * push, -deltaY * intersectY * push);
		intersectX = 0;
		intersectY = 0;
	}

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);

		if (abs(intersectX) < abs(intersectY))
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);

				direction.x = 1;
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);

				direction.y = 1;
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);

				direction.y = -1;
			}
		}
	}

	return direction;
}
