#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

recursive_mutex mt; //синхронизирует определенные потоки и обеспечивает независимую работу некоторых элементов

void Print(int a)
{
	mt.lock();

	cout << a<<" ";

	if (a == 1) {
		cout <<"\n";
		mt.unlock();
		return;
	}

	mt.unlock();
	Print(a - 1);
}

int main()
{

	thread th(Print, 10);
	thread th1(Print, 10);
	thread th2(Print, 10);

	th.join();
	th1.join();
	th2.join();

}

