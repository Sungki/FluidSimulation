#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Fluid.h"

class Game
{
private:
    sf::RenderWindow window;
    const int N = 256;
    Fluid* fluid;

    sf::Vector2i mouseCoords;

    void Render();
    void HandleInput();

public:
    Game();
    void Run();
};
