#pragma once
#include <iostream>

using namespace std;
class Beer;

class Buyer
{
public:
    Buyer() = default;
    ~Buyer() = default;

    static void BuyBeer(const Beer &typeOfBeer);
};

class Beer
{
private:
    string nameBeer;
    string colorBeer;
    double weightBeer;

    //Нарушена инкапсуляция но для нашего класса Buyer появился доступ к приват полям яблока
    friend Buyer;

public:

    Beer(const string& typeBeer, const string& color, const double weight)
    {
        nameBeer = typeBeer;
        colorBeer = color;
        weightBeer = weight;
    }

    ~Beer() = default;
};

void Buyer::BuyBeer(const Beer &typeOfBeer)
{
    cout << "BeersName " << typeOfBeer.nameBeer << '\n';
    cout << "BeersColor " << typeOfBeer.colorBeer << '\n';
    cout << "BeersWeight " << typeOfBeer.weightBeer << '\n';
}

class Ananas;

class Customer
{
public:
    Customer() = default;
    ~Customer() = default;

    void BuyFruit(const Ananas &typeOfFruit) const;
};

class Ananas
{
private:
    string nameFruit;
    string colorFruit;
    double weightFruit;

    friend void Customer::BuyFruit(const Ananas &typeOfFruit) const;
public:

    Ananas(const string& typeFruit, const string& color, const double& weight)
    {
        nameFruit = typeFruit;
        colorFruit = color;
        weightFruit = weight;
    }
    ~Ananas() = default;
};

//Метод обязательно ставить где-то за классами, чтобы уомпилятор имел полное определение с точки зрения всех знаний о классах

inline void Customer::BuyFruit(const Ananas &typeOfFruit) const
{
    cout << "FruitsName " << typeOfFruit.nameFruit << '\n';
    cout << "FruitsColor " << typeOfFruit.colorFruit << '\n';
    cout << "FruitsWeight " << typeOfFruit.weightFruit << '\n';
}

class Veg
{
private:
    int a = 10;

public:
    Veg()=default;
    ~Veg()=default;
    friend void EatVeg(Veg obj);
};

// объявление френд функцией, дает нам знать что данная функция уже реализована вне класса
//еще можно сказать, что данная функция будет дружественной для нашего класса и будет иметь доступ к приватным полям
inline void EatVeg(Veg obj)
{
    std::cout << obj.a << "\n";
}

inline void CheckFriends()
{
    const Veg b;
    EatVeg(b);

    const Ananas fruit{"apple", "green", 234};
    Customer child;

    child.BuyFruit(fruit);

    Beer Beer{"apple", "green", 234};
    Buyer human;

    human.BuyBeer(Beer);

}
