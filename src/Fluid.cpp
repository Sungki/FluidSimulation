#include "Fluid.h"

Fluid::Fluid(int N, float _dt, float diffusion, float viscosity)
{
    size = N;
    dt = _dt;
    diff = diffusion;
    visc = viscosity;

    s = new float[N * N];
    density = new float[N * N];

    Vx = new float[N * N];
    Vy = new float[N * N];

    Vx0 = new float[N * N];
    Vy0 = new float[N * N];
}

Fluid::~Fluid()
{
    delete[] Vy0;
    delete[] Vx0;

    delete[] Vy;
    delete[] Vx;

    delete[] density;
    delete[] s;
}