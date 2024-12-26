#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex mt; //синхронизирует определенные потоки и обеспечивает независимую работу некоторых элементов

void Print(char c)
{

	unique_lock<mutex> UL(mt, defer_lock); //тоже самое. что и lock guard, только здесь не надо вводить костыли, чтобы обеспечить тело, тут можно просто показатать начало и конец

	this_thread::sleep_for(std::chrono::seconds(1));

	UL.lock();


	for (size_t i = 0; i < 5; i++)
	{
		for (size_t y = 0; y < 10; y++)
		{
			cout << c;
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		cout << "\n";
	}
	cout << "\n";
	UL.unlock();

	this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{

	thread th(Print, '#');
	thread th1(Print, 'a');
	thread th2(Print, 'b');

	th.join();
	th1.join();
	th2.join();

}

