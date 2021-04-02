#include "Fluid.h"

Fluid::Fluid(int N, float _dt, float diffusion, float viscosity)
{
    iter = 16;
    scale = 4;

    size = N;
    dt = _dt;
    diff = diffusion;
    visc = viscosity;

    InitArr(s, 128 * 128);
    InitArr(density, 128 * 128);
    InitArr(Vx, 128 * 128);
    InitArr(Vy, 128 * 128);
    InitArr(Vx0, 128 * 128);
    InitArr(Vy0, 128 * 128);
}

void Fluid::InitArr(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

int Fluid::IX(int x, int y)
{
    if (x < 0) { x = 0; }
    if (x > size - 1) { x = size - 1; }

    if (y < 0) { y = 0; }
    if (y > size - 1) { y = size - 1; }

    return (y * size) + x;
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

void Fluid::Diffuse(int b, float x[], float x0[], float diff, float dt)
{
    float a = dt * diff * (size - 2) * (size - 2);
    LinSolve(b, x, x0, a, 1 + 6 * a);
}

void Fluid::LinSolve(int b, float x[], float x0[], float a, float c)
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
        SetBnd(b, x);
    }
}

void Fluid::Project(float velocX[], float velocY[], float p[], float div[])
{
    for (int j = 1; j < size - 1; j++) {
        for (int i = 1; i < size - 1; i++) {
            div[IX(i, j)] = -0.5f * (
                velocX[IX(i + 1, j)]
                - velocX[IX(i - 1, j)]
                + velocY[IX(i, j + 1)]
                - velocY[IX(i, j - 1)]
                ) / size;
            p[IX(i, j)] = 0;
        }
    }
    SetBnd(0, div);
    SetBnd(0, p);
    LinSolve(0, p, div, 1, 6);

    for (int j = 1; j < size - 1; j++) {
        for (int i = 1; i < size - 1; i++) {
            velocX[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)]
                - p[IX(i - 1, j)]) * size;
            velocY[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)]
                - p[IX(i, j - 1)]) * size;
        }
    }
    SetBnd(1, velocX);
    SetBnd(2, velocY);
}

void Fluid::Advect(int b, float d[], float d0[], float velocX[], float velocY[], float dt)
{
    float i0, i1, j0, j1;

    float dtx = dt * (size - 2);
    float dty = dt * (size - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float Nfloat = size;
    float ifloat, jfloat;
    int i, j;

    for (j = 1, jfloat = 1; j < size - 1; j++, jfloat++) {
        for (i = 1, ifloat = 1; i < size - 1; i++, ifloat++) {
            tmp1 = dtx * velocX[IX(i, j)];
            tmp2 = dty * velocY[IX(i, j)];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if (x < 0.5f) x = 0.5f;
            if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
            i0 = floor(x);
            i1 = i0 + 1.0f;
            if (y < 0.5f) y = 0.5f;
            if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
            j0 = floor(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = (int)i0;
            int i1i = (int)i1;
            int j0i = (int)j0;
            int j1i = (int)j1;

            d[IX(i, j)] =
                s0 * (t0 * d0[IX(i0i, j0i)]) + (t1 * d0[IX(i0i, j1i)]) +
                s1 * (t0 * d0[IX(i1i, j0i)]) + (t1 * d0[IX(i1i, j1i)]);
        }
    }
    SetBnd(b, d);
}

void Fluid::SetBnd(int b, float x[])
{
    for (int i = 1; i < size - 1; i++) {
        x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
        x[IX(i, size - 1)] = b == 2 ? -x[IX(i, size - 2)] : x[IX(i, size - 2)];
    }
    for (int j = 1; j < size - 1; j++) {
        x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
        x[IX(size - 1, j)] = b == 1 ? -x[IX(size - 2, j)] : x[IX(size - 2, j)];
    }

    x[IX(0, 0)] = 0.5f * (x[IX(1, 0)] + x[IX(0, 1)]);
    x[IX(0, size - 1)] = 0.5f * (x[IX(1, size - 1)] + x[IX(0, size - 2)]);
    x[IX(size - 1, 0)] = 0.5f * (x[IX(size - 2, 0)] + x[IX(size - 1, 1)]);
    x[IX(size - 1, size - 1)] = 0.5f * (x[IX(size - 2, size - 1)] + x[IX(size - 1, size - 2)]);
}

void Fluid::Step()
{
    Diffuse(1, Vx0, Vx, visc, dt);
    Diffuse(2, Vy0, Vy, visc, dt);

    Project(Vx0, Vy0, Vx, Vy);

    Advect(1, Vx, Vx0, Vx0, Vy0, dt);
    Advect(2, Vy, Vy0, Vx0, Vy0, dt);

    Project(Vx, Vy, Vx0, Vy0);

    Diffuse(0, s, density, diff, dt);
    Advect(0, density, s, Vx, Vy, dt);
}

void Fluid::Render(sf::RenderWindow& win)
{
    win.clear();

    for(int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(scale, scale));
            rect.setPosition(j* scale, i* scale);

            rect.setFillColor(sf::Color(255, 255, 255, (density[IX(i, j)] > 255) ? 255 : density[IX(i, j)]));

            win.draw(rect);
        }
}

void Fluid::FadeDensity(int size)
{
    for (int i = 0; i < size; i++) 
    {
        float d = density[i];
        density[i] = (d - 0.05f < 0) ? 0 : d - 0.05f;
    }
}