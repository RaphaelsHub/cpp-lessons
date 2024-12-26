#pragma once
#include <iostream>

using namespace std;

//композиция и агрегация, это такое состтояяние классов, где одни не могут существоввать одни бещ других
class Car
{
private:
    class Monitor
    {
    private:
        double Benzin = 200;
        double Battery = 59;
        double Gaz = 23;

    public:
        void ShowMoreInformationAboutTheCurrentStateOfCar() const
        {
            cout << Benzin << "\n";
            cout << Battery << "\n";
            cout << Gaz << "\n";
        }
        Monitor()=default;
        ~Monitor()=default;
    };

    Monitor main;

public:
    void ShowMoreInformationAboutTheCurrentStateOfCar() const
    {
        main.ShowMoreInformationAboutTheCurrentStateOfCar();
    }
    Car() = default;
    ~Car()=default;
};

inline void CallInfo()
{
    Car BMW;
    BMW.ShowMoreInformationAboutTheCurrentStateOfCar();
}