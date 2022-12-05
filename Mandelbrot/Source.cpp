#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>

constexpr int Width = 160;
constexpr int Height = 80;
constexpr int MaxIterations = 100;

void Draw(int width = Width, int height = Height, int maxIterations = MaxIterations)
{
    // Allocate the plane on the heap

    auto complexPlane = new std::complex<double>[height * width];

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Map the x and y coordinates to the complex plane

            double r = (1.5 * (x - width / 2)) / (0.5 * width);
            double i = (1.0 * (y - height / 2)) / (0.5 * height);

            complexPlane[y * width + x] = { r, i };
        }
    }

    // Iterate over each point in the complex plane and calculate its membership in the Mandelbrot set
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            std::complex<double> c = complexPlane[y * width + x];
            std::complex<double> z = 0;

            int iterations = 0;

            // Iterate until the point escapes the circle of radius 2 centered at the origin
            // or until the maximum number of iterations is reached
            while (abs(z) < 2 && iterations < maxIterations)
            {
                z = z * z + c;
                ++iterations;
            }

            // If the point escaped the circle, print a dot, otherwise print a space
            if (abs(z) < 2)
                std::cout << ' ';
            else
                std::cout << '~';
        }

        std::cout << '\n';
    }

    delete[] complexPlane;
}

void GenerateOnFullConsoleSize()
{
#ifdef _WIN32

    // Get console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == nullptr)
    {
        std::cerr << "Failed to get the handle to the console window\n";
        return;
    }

    // Get console width and height

    CONSOLE_SCREEN_BUFFER_INFO info;

    if (!GetConsoleScreenBufferInfo(hConsole, &info))
    {
        std::cerr << "Failed to get the current size of the console window\n";
        return;
    }

    return Draw(info.srWindow.Right - info.srWindow.Left + 1, info.srWindow.Bottom - info.srWindow.Top + 1, 100);

#else

    std::cerr << "This function can only be used on Windows!\n";

#endif
}

int main()
{
    //Draw();

    // Adjust to the current console window width and height
    GenerateOnFullConsoleSize();

    getchar();
    return 0;
}
