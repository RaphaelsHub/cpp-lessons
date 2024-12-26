#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// передача параметром в функцию и возврат
using namespace std;

void DoWork(int &a)
{
	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork STARTED\n";

	this_thread::sleep_for(chrono::seconds(2));

	a *= 2;

	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork ENDED\n";
}

int main()
{
	int a = 2;
	thread firstOne(DoWork, std::ref(a)); // передаем параметры в функцию)

	for (size_t i = 0; i < 15; i++)
	{
		cout << "MAIN WORKS: " << i + 1 << " IdThread: " << this_thread::get_id() << "\n";
		this_thread::sleep_for(chrono::seconds(1));
	}

	firstOne.join();//
	
	cout << "a = " << a << " \n";

	return 0;
}