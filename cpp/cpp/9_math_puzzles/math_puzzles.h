#pragma once

#include <iostream>
#include <cmath> 

using namespace std;

// Function to convert Verst to Kilometers
void VerstToKm()
{
    constexpr double kmPerVerst = static_cast<double>(10000) / 10668;
    constexpr double verstPerKm = static_cast<double>(10668) / 10000;

    cout << 1000 << " km = " << 1000 * verstPerKm << " versts\n";
    cout << 1000 << " versts = " << 1000 * kmPerVerst << " km\n";
}

// Function to convert Kilograms to Pounds
void KgToFunts()
{
    constexpr double kgPerFunt = 0.453592;
    double weight = 100;

    cout << weight << " kg = " << weight / kgPerFunt << " pounds\n";
    cout << weight << " pounds = " << weight * kgPerFunt << " kg\n";
}

// Function to convert Miles to Kilometers
void MilesToKm()
{
    constexpr double kmPerMile = 1.6009;
    constexpr double milePerKm = 1 / kmPerMile;

    cout << 1000 << " km = " << 1000 * milePerKm << " miles\n";
    cout << 1000 << " miles = " << 1000 * kmPerMile << " km\n";
}

// Function to calculate integral of F(x) = x*x
double F(double x)
{
    return x * x;
}

void Integral()
{
    double S = 0, a = 1, b = 3;
    int N = 1000;
    double n = (b - a) / N;
    double x = a + n;

    while (x < b)
    {
        S = S + 4 * F(x);
        x += n;
        if (x >= b)
            break;
        S = S + 2 * F(x);
        x += n;
    }
    S = (n / 3) * (S + F(a) + F(b));
    std::cout << "Integral: " << S << "\n";
}

// Function to calculate the sum of limits
void Limit()
{
    int limit = 10;
    double sum = 0;

    for (int i = 0; i < limit; i++)
    {
        double x = static_cast<double>(i) / 10;
        sum += x;
    }
    std::cout << "Limit: " << sum << "\n";
}

// Function to calculate properties of Circle
void Circle()
{
    double r = 1;
    constexpr double pi = 3.14;
    double area = pi * r * r;
    double circumference = 2 * pi * r;

    std::cout << "Circle area: " << area << "\n";
    std::cout << "Circle circumference: " << circumference << "\n";
}

// Function to calculate properties of Sphere
void Sphere()
{
    constexpr double r = 1;
    constexpr double pi = 3.14;
    double surfaceArea = 4 * pi * r * r;
    double volume = (4.0 / 3.0) * pi * r * r * r;

    std::cout << "Sphere surface area: " << surfaceArea << "\n";
    std::cout << "Sphere volume: " << volume << "\n";
}

// Function to calculate properties of Ring
void Ring()
{
    constexpr double pi = 3.14;
    constexpr double r = 1;
    constexpr double R = 3;
    double area = ((R * R) - (r * r)) * pi;
    double circumference = 2 * pi * R;

    std::cout << "Ring area: " << area << "\n";
    std::cout << "Ring circumference: " << circumference << "\n";
}

// Function to calculate properties of Cylinder
void Cylinder()
{
    constexpr double pi = 3.14;
    double r = 1;
    double h = 3;
    double sideSurfaceArea = 2 * pi * r * h;
    double baseSurfaceArea = 2 * pi * r * r;
    double volume = pi * r * r * h;
    double totalSurfaceArea = sideSurfaceArea + baseSurfaceArea;

    std::cout << "Cylinder total surface area: " << totalSurfaceArea << "\n";
    std::cout << "Cylinder volume: " << volume << "\n";
}

// Function to calculate properties of Hollow Cylinder
void HollowCylinder()
{
    constexpr double pi = 3.14;
    double r = 1;
    double R = 4;
    double h = 5;
    double sideSurfaceArea = 2 * pi * (R - r) * h;
    double baseSurfaceArea = 2 * pi * r * r;
    double volume = pi * (R * R - r * r) * h;
    double totalSurfaceArea = sideSurfaceArea + baseSurfaceArea;

    std::cout << "Hollow Cylinder total surface area: " << totalSurfaceArea << "\n";
    std::cout << "Hollow Cylinder volume: " << volume << "\n";
}

// Function to calculate properties of Rectangle
void Rectangle()
{
    double a = 2, b = 3;
    double area = a * b;
    double perimeter = 2 * (a + b);

    std::cout << "Rectangle area: " << area << "\n";
    std::cout << "Rectangle perimeter: " << perimeter << "\n";
}

// Function to calculate properties of Cube
void Cube()
{
    constexpr double a = 32;
    double surfaceArea = 6 * a * a;
    double perimeter = 12 * a;
    double volume = a * a * a;

    std::cout << "Cube surface area: " << surfaceArea << "\n";
    std::cout << "Cube perimeter: " << perimeter << "\n";
    std::cout << "Cube volume: " << volume << "\n";
}

// Function to calculate properties of Trapezoid
void Trapezoid()
{
    constexpr double a = 2;
    constexpr double b = 4;
    constexpr double h = 5;
    double c = (b - a) / 2;
    double obliqueSide = sqrt(c * c + h * h);
    double area = (a + b) * h / 2;
    double perimeter = a + b + 2 * obliqueSide;

    std::cout << "Trapezoid area: " << area << "\n";
    std::cout << "Trapezoid perimeter: " << perimeter << "\n";
}

// Function to perform various geometry calculations
void Geometry()
{
    Circle();
    Sphere();
    Ring();
    Cylinder();
    HollowCylinder();
    Rectangle();
    Cube();
    Trapezoid();
}

// Function to convert Celsius to Fahrenheit
void CelsiusToFahrenheit()
{
    constexpr double ci = 5.0 / 9.0;
    constexpr double co = 9.0 / 5.0;
    double c = 0;
    double f = (c * co) + 32;
    c = (f - 32) * ci;

    std::cout << "Celsius: " << c << ", Fahrenheit: " << f << "\n";
}

void CallAllMathPuzzles()
{
    VerstToKm();
    KgToFunts();
    MilesToKm();
    CelsiusToFahrenheit();
    Integral();
    Limit();
    Geometry();
}
