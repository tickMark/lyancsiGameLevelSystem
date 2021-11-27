#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <thread>
#include <cmath>
#include "Blackbars.h"
#include "Gameplay.h"
#include "Consts.cpp"
#include "Fade.h"


using namespace std;
using namespace sf;

void reopenWindow(RenderWindow& window, Vector2u windowSize, Vector2i windowPos, Blackbars& blackbars, bool& isFullscreen)
{
    if (isFullscreen)
    {
        window.create(VideoMode(windowSize.x, windowSize.y), "lyancsi.");
        window.setPosition(windowPos);
    }
    else
    {
        window.create(VideoMode(VideoMode::getDesktopMode()), "lyancsi.", Style::Fullscreen);
    }
    blackbars.UpdateSize();
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

int main()
{
    Vector2u windowSize = Vector2u(VIEW_WIDTH, VIEW_HEIGHT);
    RenderWindow window(VideoMode(windowSize.x, windowSize.y), "lyancsi.");
    Vector2i windowPos = window.getPosition();

    View view(Vector2f(0.0, 0.0), Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    Blackbars blackbars(window, view, VIEW_WIDTH, VIEW_HEIGHT);

    Font font;
    font.loadFromFile("data/misc/font.ttf");

    Texture playerTexture;
    Texture tileset;

    playerTexture.loadFromFile("data/textures/player.png");
    tileset.loadFromFile("data/textures/tileset.png");

    bool doClose = false;
    int doStart = 1;

    Gameplay** gameplay = new Gameplay*;
    bool isplaying = false;

    float deltaTime = 0;
    Clock deltaClock;

    bool isFullscreen = true;
    reopenWindow(window, windowSize, windowPos, blackbars, isFullscreen);
    isFullscreen = false;

    while (window.isOpen())
    {
        if (doClose)
            window.close();

        if (isplaying)
        {
            if ((*gameplay)->doClose)
            {
                delete (*gameplay);
                isplaying = false;
            }
            else if ((*gameplay)->doRestart)
            {
                int level = (*gameplay)->level.levelNumber;
                //Gameplay gameplay(&playerTexture, &enemyTexture, &particleTexture, &fleshTexture, &tileset, &cloudTexture, &bgtexture);
                delete (*gameplay);
                delete gameplay;
                gameplay = new Gameplay*;
                (*gameplay) = new Gameplay(&window, font, &playerTexture, &tileset, level);
            }
            else if ((*gameplay)->doContinue)
            {
                int level = (*gameplay)->level.levelNumber;
                if (level != 6)
                    level++;
                //Gameplay gameplay(&playerTexture, &enemyTexture, &particleTexture, &fleshTexture, &tileset, &cloudTexture, &bgtexture);
                delete (*gameplay);
                delete gameplay;
                gameplay = new Gameplay*;
                (*gameplay) = new Gameplay(&window, font, &playerTexture, &tileset, level);
            }
        }
        
        if (doStart != 0)
        {
            if (!isplaying)
            {
                delete gameplay;
                gameplay = new Gameplay*;
                (*gameplay) = new Gameplay(&window, font, &playerTexture, &tileset, doStart);
                isplaying = true;
            }
            doStart = 0;
        }

        if (!window.hasFocus())
        {
            deltaTime += deltaClock.restart().asSeconds();
        }
        else
        {
            deltaTime = deltaClock.restart().asSeconds();
        }
        if (!isFullscreen)
        {
            windowPos = window.getPosition();
        }

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::Resized:
                if (event.size.width < VIEW_WIDTH)
                    window.setSize(Vector2u(VIEW_WIDTH, window.getSize().y));
                if (event.size.height < VIEW_HEIGHT)
                    window.setSize(Vector2u(window.getSize().x, VIEW_HEIGHT));
                windowSize = Vector2u(window.getSize().x, window.getSize().y);
                blackbars.UpdateSize();
                break;

            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::Space:
                    if (isplaying)
                    if (!(*gameplay)->Isjumping())
                        (*gameplay)->Spaceclock().restart();
                    break;
                case Keyboard::W:
                    if (isplaying)
                        if (!(*gameplay)->Isjumping())
                            (*gameplay)->Spaceclock().restart();
                    break;
                }
                break;

            case Event::KeyReleased:
                switch (event.key.code)
                {
                case Keyboard::Space:
                    if(isplaying)
                        (*gameplay)->Spacereleaseclock().restart();
                    break;
                case Keyboard::W:
                    if (isplaying)
                        (*gameplay)->Spacereleaseclock().restart();
                    break;
                }
                break;
            }


        }

        if (window.hasFocus())
        {
            if (deltaTime > 0.05)
            {
                int steps = ceil(deltaTime / 0.05);
                if (steps == 0)
                {
                    if(isplaying)
                        (*gameplay)->Update(deltaTime, window);
                }
                else
                {
                    float smallDeltaTime = deltaTime / steps;
                    for (int i = 0; i < steps; i++)
                    {
                        if (isplaying)
                            (*gameplay)->Update(smallDeltaTime, window);
                    }
                }
            }
            else
            {
                if (isplaying)
                    (*gameplay)->Update(deltaTime, window);
            }

            if (isplaying)
            {
                Vector2f viewCenter = Vector2f(min(max((*gameplay)->player.GetPosition().x + 100, (*gameplay)->levelBounds.left + 310.0f), (*gameplay)->levelBounds.left + (*gameplay)->levelBounds.width - 330.0f), 170);
                view.setCenter(viewCenter);
            }
            window.setView(view);

            
            blackbars.UpdatePosition();

            window.clear(BACKGROUND_COLOR);

            if (isplaying)
                (*gameplay)->Draw(window);

            blackbars.Draw();

            window.display();
        }
    };

    return 0;
}
