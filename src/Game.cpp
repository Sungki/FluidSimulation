#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Game::Game()
{
    window.create(sf::VideoMode(N, N, 32), "FluidSimulation");
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        mouseCoords = sf::Mouse::getPosition(window);
        fluid->AddDensity(mouseCoords.x, mouseCoords.y, 100);
    }
}

void Game::Run()
{
    fluid = new Fluid(N, 0.1, 0, 0);

    while (window.isOpen()) {
        HandleInput();
        Render();
    }
}

void Game::Render()
{
    fluid->AddVelocity(mouseCoords.x, mouseCoords.y, 0.5, 0.5);

    fluid->Step();
    fluid->Render(window);

    window.display();
}