#pragma once

#include<iostream>

using namespace std;

enum Color
{
    green,
    red,
    yellow
};

class gig
{
private:
    int countRedApples = 0;
    int countGreenApples = 0;

public:
    void operator()(Color color)
    {
        if (color == green)
            countGreenApples++;
        else
            countRedApples++;

        cout << "GreenApples = " << countGreenApples << " RedApples = " << countRedApples << '\n';
    }
};

inline void ShowFuct()
{
    gig A;
    Color array[] = {red, green, green, green, green, red};

    for (const auto elem : array)
        A(elem);
}
