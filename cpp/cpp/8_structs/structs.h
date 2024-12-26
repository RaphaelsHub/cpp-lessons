#pragma once

#include <iostream>
#include <string>

struct Location
{
    int PostIndex = 0;
};

struct Human
{
    int age = 21;
    Location address;
} Alex;

struct Player
{
    int id = 11;
    std::string name = "Alex";
    std::string surName = "Hack";
} Pupil[2];

struct Timing
{
    int hours = 0;
    int minutes = 0;
    int seconds = 0;

    void AdjustTime(Timing& time)
    {
        if (time.seconds >= 60)
        {
            time.minutes += time.seconds / 60;
            time.seconds %= 60;
        }
        if (time.minutes >= 60)
        {
            time.hours += time.minutes / 60;
            time.minutes %= 60;
        }

        std::cout << "Seconds: " << time.seconds << "\n";
        std::cout << "Minutes: " << time.minutes << "\n";
        std::cout << "Hours: " << time.hours << "\n";
    }
};

enum Valute { EURO = 20, DOLLAR = 18, LEU_ROMAN = 4 };

void CheckForStatus(Valute status)
{
    switch (status) 
    {
    case EURO:
        std::cout << "euro";
        break;
    case DOLLAR:
        std::cout << R"(dollar)";
        break;
    case LEU_ROMAN:
        std::cout << "leu roman";
        break;
    }
}

void SendPlayerInfo(int ind, const std::string& nm, const std::string& surname) {}

void SendPlayerReference(Player& obj) {}

void SendPlayerCopy(Player obj) {}

void SetPlayerInfo()
{
    for (auto& player : Pupil)
        player.id = 0;
    Pupil[0] = Pupil[1];
}

void InitStructs()
{
    Player teacher = { 12, "Alexia", "Petrov" };
    SendPlayerInfo(teacher.id, teacher.name, teacher.surName);
    SendPlayerCopy(teacher);
    SendPlayerReference(teacher);
    SetPlayerInfo();

    Timing time = { 0, 133, 230 };
    time.AdjustTime(time);

    Alex.address.PostIndex = 10;

    typedef int Num;
    Num even[2] = { 0, 1 };

    CheckForStatus(Valute::DOLLAR);

    Human* citizenPtr = &Alex;
    citizenPtr->age = 10;
    std::cout << citizenPtr->age << "\n";
}
