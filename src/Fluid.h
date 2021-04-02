#pragma once

#include <iostream>
#include <math.h>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Fluid
{
    int size;
    float dt;
    float diff;
    float visc;

    int iter;
    int scale;

    float s[128 * 128];
    float density[128 * 128];

    float Vx[128 * 128];
    float Vy[128 * 128];

    float Vx0[128 * 128];
    float Vy0[128 * 128];

    int IX(int x, int y);

    void Diffuse(int b, float x[], float x0[], float diff, float dt);
    void LinSolve(int b, float x[], float x0[], float a, float c);
    void Project(float velocX[], float velocY[], float p[], float div[]);
    void Advect(int b, float d[], float d0[], float velocX[], float velocY[], float dt);
    void SetBnd(int b, float x[]);

    void InitArr(float arr[], int size);

public:
    Fluid(int N, float _dt, float diffusion, float viscosity);

    void Step();
    void Render(sf::RenderWindow& win);
    void AddDensity(int x, int y, float amount);
    void AddVelocity(int x, int y, float amountX, float amountY);
    void FadeDensity(int size);
};

