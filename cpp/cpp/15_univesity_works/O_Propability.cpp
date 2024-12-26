#include <iostream>
#include <cmath>
#include <vector>

float probaility(float a, float sum)
{
    return a / sum;
}

float Chance(int z, int y)
{
    float a = 1, b = 1, c = 1;
    int dif = y - z;
    if (z == 0 || z == y)
        return a;
    else
    {
        for (int i = y; i >= 1; i--)
            a = a * i;
        for (int n = dif; n >= 1; n--)
            c = c * n;
        for (int r = z; r >= 1; r--)
            b = b * r;
        float result = a / (c * b);
        return (float)result;
    }
}

void P()
{
    float boys, girls, trans;

    do
    {
        static int count = 0;
        if (count > 0)
            std::cout << "Error. Please input positive numbers!\n\n\n";

        std::cout << "Enter the amount of boys: ";
        std::cin >> boys;
        std::cout << "Enter the amount of girls: ";
        std::cin >> girls;
        std::cout << "Enter the amount of trans: ";
        std::cin >> trans;

        count++;
    } while (trans < 0 || boys < 0 || girls < 0);

    float sum = boys + girls + trans;
    boys = probaility(boys, sum);
    girls = probaility(girls, sum);
    trans = probaility(trans, sum);

    std::cout << "\n";
    std::cout << "Chance to take a boy " << boys << "\n";
    std::cout << "Chance to take a girl " << girls << "\n";
    std::cout << "Chance to take a trans " << trans << "\n";
}

void D()
{
    int NUM, amount;

    std::cout << "Enter your position in the journal: ";
    std::cin >> NUM;
    std::cout << "Enter the number of experiments to be conducted: ";
    std::cin >> amount;

    float P = (float)(NUM + 10) / 100;
    float Q = 1 - P;
    const int N = (amount + 1);
    std::vector<double> PX(N);

    for (int x = 0; x < N; x++)
        PX[x] = pow(P, x) * pow(Q, amount - x) * Chance(x, amount);
    std::cout << "\n";

    for (int x = 0; x < N; x++)
        std::cout << x << " - " << PX[x] << "\n";

    double mat = 0, dis = 0;
    for (int x = 0; x < N; x++)
        mat = mat + PX[x] * x;

    for (int x = 0; x < N; x++)
        dis = dis + PX[x] * x * x;
    dis = dis + mat * mat;

    double otlonenie = sqrt(dis);

    std::cout << "Mathematical expectation is " << mat << "\n";
    std::cout << "Variance is " << dis << "\n";
    std::cout << "Standard deviation is " << otlonenie << "\n";
}

int main()
{
    P();
    D();
    return 0;
}
