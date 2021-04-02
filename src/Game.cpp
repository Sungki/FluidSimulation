#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

Game::Game()
{
    window_height = 768;
    window_width = 1024;
    window.create(sf::VideoMode(window_width, window_height, 32), "FluidSimulation");
}

void Game::Run()
{
    while (window.isOpen()) {
        HandleInput();
        Render();
    }
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }
}

void Game::Render()
{
    window.clear();
    window.display();
}