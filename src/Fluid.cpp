#include "Fluid.h"

Fluid::Fluid(int N, float _dt, float diffusion, float viscosity)
{
    iter = 10;

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

int Fluid::IX(int x, int y)
{
    return x + y * size;
}

void Fluid::AddDensity(int x, int y, float amount)
{
    int index = IX(x, y);
    density[index] += amount;
}

void Fluid::AddVelocity(int x, int y, float amountX, float amountY)
{
    int index = IX(x, y);
    Vx[index] += amountX;
    Vy[index] += amountY;
}

void Fluid::Diffuse(int b, float* x, float* x0, float diff, float dt)
{
    float a = dt * diff * (size - 2) * (size - 2);
    LinSolve(b, x, x0, a, 1 + 6 * a);
}

void Fluid::LinSolve(int b, float* x, float* x0, float a, float c)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++) {
        for (int j = 1; j < size - 1; j++) {
            for (int i = 1; i < size - 1; i++) {
                x[IX(i, j)] =
                    (x0[IX(i, j)]
                        + a * (x[IX(i + 1, j)]
                            + x[IX(i - 1, j)]
                            + x[IX(i, j + 1)]
                            + x[IX(i, j - 1)]
                            )) * cRecip;
            }
        }
//        set_bnd(b, x, N);
    }
}