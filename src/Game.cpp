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
    window.clear();
    window.display();
}