#include "Animation.h"                   

Animation::Animation(Texture* texture, Vector2u imageCount) : totalTime(0.0f), doLoop(true)
{
	if (texture != nullptr)
	{
		this->imageCount = imageCount;
		currentImage.x = 0;

		uvRect.width = texture->getSize().x / float(imageCount.x);
		uvRect.height = texture->getSize().y / float(imageCount.y);
	}
}

IntRect Animation::Update(int row, float deltaTime, float switchTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;
	float mSwitchTime = switchTime / 1000;

	while (totalTime >= mSwitchTime)
	{
		totalTime -= mSwitchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			if (doLoop)
				currentImage.x = 0;
			else
				currentImage.x--;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	return uvRect;
}

IntRect Animation::Update(int row, bool faceRight)
{
	currentImage.y = row;
	currentImage.x++;

	if (currentImage.x >= imageCount.x && doLoop)
	{
		currentImage.x = 0;
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (faceRight) {
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	return uvRect;
}
