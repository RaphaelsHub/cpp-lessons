#pragma once

#include<iostream>

using namespace std;

class Weapon
{
public:
    virtual ~Weapon() = 0;
    virtual void Shoot() = 0;
    virtual void Reload() { std::cout << "Reloading...\n"; }
};

inline Weapon::~Weapon() = default;

class Gun : public Weapon
{
protected:
    void Shoot() override { cout << "Gun Shooting" << '\n'; }
};

class HardGun : public Weapon
{
protected:
    void Shoot() override { cout << "HardGun Shooting" << '\n'; }
};

class Knife : public Weapon
{
protected:
    void Shoot() override { cout << "Any knife is Cutting" << '\n'; }
};

class SubMachineGun : public Gun
{
protected:
    virtual void Shoot() override { cout << "SubMachineGun is Shooting" << '\n'; }
};

class KitchenKnife : public Knife
{
protected:
    void Shoot() override
    {
        cout << "Teberik knife is Cutting" << '\n';
        //Knife::Shoot();
    }
};

template <typename Weapon>
class Shooter
{
public:
    void Shoot(Weapon* weapon) { weapon->Shoot(); }
    void Reload(Weapon* weapon) { weapon->Reload(); }
};


inline void CheckInterface()
{
    Shooter<Weapon> player;
    Gun pistol;
    HardGun rpg;
    Knife fuck;
    SubMachineGun usp;
    KitchenKnife ruffian;

    player.Shoot(&pistol);
    player.Reload(&pistol);
    player.Shoot(&rpg);
    player.Reload(&rpg);
    player.Shoot(&fuck);
    player.Reload(&fuck);
    player.Shoot(&usp);
    player.Reload(&usp);
    player.Shoot(&ruffian);
    player.Reload(&ruffian);
}
