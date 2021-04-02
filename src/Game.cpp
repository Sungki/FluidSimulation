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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        fluid->AddDensity(currentMouse.y/SCALE, currentMouse.x/SCALE, 200);

    currentMouse = sf::Mouse::getPosition(window);
}

void Game::Run()
{
    fluid = new Fluid(N, 0.2, 0, 0.0000001f);

    previousMouse = sf::Mouse::getPosition(window);
    currentMouse = sf::Mouse::getPosition(window);

    while (window.isOpen()) {
        HandleInput();
        Render();
    }
}

void Game::Render()
{
    float amountX = currentMouse.x - previousMouse.x;
    float amountY = currentMouse.y - previousMouse.y;

    fluid->AddVelocity(currentMouse.y/SCALE, currentMouse.x/SCALE, amountY / 10, amountX / 10);

    previousMouse = currentMouse;

    fluid->Step();
    fluid->Render(window);
//    fluid->FadeDensity(N * N);

    window.display();
}