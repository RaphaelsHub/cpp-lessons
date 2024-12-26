#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// передача параметром в функцию и возврат
using namespace std;

void DoWork(int a, int b)
{
	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork STARTED\n";

	this_thread::sleep_for(chrono::seconds(2));

	cout << "a+b=" << a + b << endl;

	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork ENDED\n";
}

int main()
{
	thread firstOne(DoWork, 2, 3); // передаем параметры в функцию)

	for (size_t i = 0; i < 10; i++)
	{
		cout << "MAIN WORKS: " << i + 1 << " IdThread: " << this_thread::get_id()<<"\n";
		this_thread::sleep_for(chrono::seconds(1));
	}

	firstOne.join();

	return 0;
}