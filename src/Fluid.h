#pragma once
class Fluid
{
    int size;
    float dt;
    float diff;
    float visc;

    float* s;
    float* density;

    float* Vx;
    float* Vy;

    float* Vx0;
    float* Vy0;

public:
    Fluid(int N, float _dt, float diffusion, float viscosity);
    ~Fluid();
};

