#include "Blackbars.h"

Blackbars::Blackbars(RenderWindow& window, View& view, float viewWidth, float viewHeight) : window(window), view(view), viewWidth(viewWidth), viewHeight(viewHeight)
{
    for (int i = 0; i < 4; i++) {
        blackbar.push_back(RectangleShape(Vector2f(0, 0)));
        blackbar[i].setFillColor(Color::Black);
    }
}

void Blackbars::UpdateSize()
{
    Vector2f windowSize = Vector2f(float(window.getSize().x), float(window.getSize().y));
    float aspectRatio = windowSize.x / windowSize.y;

    if (aspectRatio == (viewWidth / viewHeight))
    {
        view.setSize(viewWidth, viewHeight);
        blackbarSideSize = 0.0f;
        blackbarTopSize = 0.0f;
    }
    else if (aspectRatio < (viewWidth / viewHeight))
    {
        view.setSize(viewWidth, viewWidth * (1 / aspectRatio));
        blackbarSideSize = 0.0f;
        blackbarTopSize = -(windowSize.y - windowSize.x * (1 / (viewWidth / viewHeight))) / 2;
    }
    else if (aspectRatio > (viewWidth / viewHeight))
    {
        view.setSize(viewHeight * aspectRatio, viewHeight);
        blackbarSideSize = -(windowSize.x - (windowSize.y * (viewWidth / viewHeight))) / 2;
        blackbarTopSize = 0.0f;
    }

    blackbar[0].setSize(Vector2f(windowSize.x, blackbarTopSize));
    blackbar[1].setSize(Vector2f(-(blackbarSideSize), -windowSize.y));
    blackbar[2].setSize(Vector2f(-(windowSize.x), -(blackbarTopSize)));
    blackbar[3].setSize(Vector2f(blackbarSideSize, windowSize.y));
}

void Blackbars::UpdatePosition()
{
    blackbar[0].setPosition(Vector2f((view.getCenter().x - (viewWidth / 2)), (view.getCenter().y - (viewHeight / 2))));
    blackbar[1].setPosition(Vector2f((view.getCenter().x + (viewWidth / 2)), (view.getCenter().y + (viewHeight / 2))));
    blackbar[2].setPosition(Vector2f((view.getCenter().x + (viewWidth / 2)), (view.getCenter().y + (viewHeight / 2))));
    blackbar[3].setPosition(Vector2f((view.getCenter().x - (viewWidth / 2)), (view.getCenter().y - (viewHeight / 2))));
}

void Blackbars::Draw()
{
    window.draw(blackbar[0]);
    window.draw(blackbar[1]);
    window.draw(blackbar[2]);
    window.draw(blackbar[3]);
}
