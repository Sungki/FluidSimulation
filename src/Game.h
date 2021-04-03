#pragma once
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Fluid.h"

class Game
{
private:
    sf::RenderWindow window;
    const int N = 128;
    const int SCALE = 5;
    Fluid* fluid;

    sf::Vector2i previousMouse;
    sf::Vector2i currentMouse;

    void Render();
    void HandleInput();

public:
    Game();
    void Run();
};
