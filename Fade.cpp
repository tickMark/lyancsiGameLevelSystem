#include "Fade.h"

Fade::Fade(Clock* clock, bool doFadeIn, float duration, float startTime, Color color)
	:
	clock(clock),
	doFadeIn(doFadeIn),
	duration(duration),
	startTime(startTime),
	color(color)
{
}

void Fade::UpdateColor()
{
	if (!doUpdate)
		return;

	if(doFadeIn)
		rect.setFillColor(Color(color.r, color.g, color.b, 255 - min(255.0f, max(0.0f, (clock->getElapsedTime().asMilliseconds() - startTime) / duration * 255))));
	else
		rect.setFillColor(Color(color.r, color.g, color.b, min(255.0f, max(0.0f, (clock->getElapsedTime().asMilliseconds() - startTime) / duration * 255))));

	if (clock->getElapsedTime().asMilliseconds() > startTime + duration)
	{
		doUpdate = false;
		doDraw = false;
	}
}

void Fade::Draw(RenderWindow& window)
{
	if (!doDraw && !drawAfterFinish)
		return;

	if (doRectInit)
	{
		rect.setSize(Vector2f(window.getView().getSize().x, window.getView().getSize().y));
		rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
		doRectInit = false;
	}

	UpdateColor();

	rect.setPosition(window.getView().getCenter());

	window.draw(rect);
}
