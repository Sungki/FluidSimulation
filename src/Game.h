#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{
private:
    sf::RenderWindow window;
    int window_width;
    int window_height;

    void Render();
    void HandleInput();

public:
    Game();
    void Run();
};
