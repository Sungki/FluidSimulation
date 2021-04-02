#pragma once

class Fluid
{
    int size;
    float dt;
    float diff;
    float visc;

    int iter;

    float* s;
    float* density;

    float* Vx;
    float* Vy;

    float* Vx0;
    float* Vy0;

    int IX(int x, int y);
    void AddDensity(int x, int y, float amount);
    void AddVelocity(int x, int y, float amountX, float amountY);

    void Diffuse(int b, float* x, float* x0, float diff, float dt);
    void LinSolve(int b, float* x, float* x0, float a, float c);

public:
    Fluid(int N, float _dt, float diffusion, float viscosity);
    ~Fluid();
};

