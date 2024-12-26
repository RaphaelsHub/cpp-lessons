#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

mutex mt; //синхронизирует определенные потоки и обеспечивает независимую работу некоторых элементов

void Print(char c)
{
	lock_guard<mutex> g(mt); // обертка для mutex, которая дает возможность в момент попадания в данную точку исполнения синхронищировать поток 
	{
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
	}
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

