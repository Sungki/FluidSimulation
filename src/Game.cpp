#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Game::Game()
{
    window.create(sf::VideoMode(N*SCALE, N*SCALE, 32), "FluidSimulation");
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
/*    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        currentMouse = sf::Mouse::getPosition(window);
        fluid->AddDensity(currentMouse.x / SCALE, currentMouse.y / SCALE, 100);
    }*/
}

void Game::Run()
{
    fluid = new Fluid(N, 0.1, 0, 0);

//    previousMouse = sf::Mouse::getPosition(window);
//    currentMouse = sf::Mouse::getPosition(window);

    while (window.isOpen()) {
        HandleInput();
        Render();
    }
}

void Game::Render()
{
/*    float amountX = currentMouse.x - previousMouse.x;
    float amountY = currentMouse.y - previousMouse.y;
    fluid->AddVelocity(currentMouse.x / SCALE, currentMouse.y / SCALE, amountX, amountY);
    previousMouse = currentMouse;*/

    int cx = (int)(0.5 * N);
    int cy = (int)(0.5 * N);

    fluid->AddDensity(cx,cy, rand()%400 + 100);

    float amountX = rand() % 50 - 30;
    float amountY = rand() % 50 - 30;

    fluid->AddVelocity(cx, cy, amountX/2, amountY/2);

    fluid->Step();
    fluid->Render(window);
    fluid->Fade();

    window.display();
}