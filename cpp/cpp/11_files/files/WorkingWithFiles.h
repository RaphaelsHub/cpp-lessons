#pragma once

#include <iostream>
#include <fstream> // ifstream in; ofstream out; fstream io;
#include <string>

using namespace std;

/*
 *ios::app открытие файла+добавлен инфы в конец, применяется к файлам открытым для входа
 *ios::ate поиск конца файла, вод/вывод в любой части
 *ios::binary
 *ios::in,ios::out ввод и вывод
 *ios::trunk удаленние содержимого
 */

class Point
{
private:
    int x, y, z;
public:
    Point() = default;
    Point(int x, int y, int z)
    {
        this->x = x;
        this->z = z;
        this->y = y;
    }

    ~Point() = default;
    friend ostream &operator<<(ostream &obj, const Point &point);
    friend istream &operator>>(istream &obj, Point &point);
};

// для папблик полей
inline ostream &operator<<(ostream &obj, const Point &point)
{
    obj << point.x << " " << point.y << " " << point.z << "\n";
    return obj;
}

inline istream &operator>>(istream &obj, Point &point)
{
    obj >> point.x >> point.y >> point.z;
    return obj;
}


inline void IOFile()
{
    ofstream File("MyFile.txt");
    if (!File)
    {
        cout<<"Error open\n";
        return;
    }
        
    File << "Hello Daddy\n";
    File << "Hello Daddy\n";

    File.close();

    ifstream Pile("MyFile.txt");
    if (!File)
    {
        cout<<"Error open\n";
        return;
    }

    char ch;
    while (!Pile.eof())
    {
        Pile>>ch;
        cout<<ch;
    }
    cout<<"\n";

    string str;
    while (getline(Pile, str))
        cout<<str;
    
    Pile.close();
}

inline void Input10Str()
{
    const string fileName = "Text.txt";
    ofstream File; // создаем файл + говорим что будем записывать информцию

    File.open(fileName,ofstream::app); 

    if (File.is_open()) 
        cout << "The file was succesfully openned\n";
    else
        cout << "Error";

    for (size_t i = 0; i < 10; i++) 
        File << "The file is writting information \n";

    File.close(); // закрываем файл
}

inline void Output10Str()
{
    string fileName = "Text.txt";
    string str;


    ifstream Fin;
    Fin.open(fileName);

    if (!Fin.is_open()) // сделали проверку
        cout << "Error";
    else
        cout << "Good";
    

    while (!Fin.eof()) 
    {
        str = " ";
        getline(Fin, str); // записываем строчку из файла в str
        cout << str + "\n"; // конкантенация
    }

    Fin.close(); // закрываем
}

inline void OverLoadingIOstrem()
{
        string path = "Beska";
        Point a(2, 2, 3);

        fstream MyFile;

        MyFile.open(path, fstream::in | fstream::out | fstream::app);

        MyFile.is_open() ? cout << "Succesed openned! \n" : cout << "Failed openning \n";

        MyFile << a << "\n"; // записали данные в наш объект, потом записали в файл
        cout << a;

        MyFile.seekg(0); //переводит указатель на начальный элемент для чтения
    
        while (!MyFile.eof())
        {
            Point tmp;
            MyFile >> tmp; // считали из файла в объект tmp
            
            cout << tmp;   // вывели объект с помощью перегруженного оператора
        }

        MyFile.close();
}


