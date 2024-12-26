#include <iostream>
#include <string>
#include <thread>
#include<chrono>
#include "ThreadBasic.h"

using namespace std;

void DoWork()
{
	for (size_t i = 0; i < 10; i++)
	{
		cout << "Id THREAD = " << this_thread::get_id() << " WORKS DOWORK FUNCTION. " << "Was called for " << i + 1 << " times\n";
		this_thread::sleep_for(chrono::seconds(2));
	}
}

void DoRest()
{
	for (size_t i = 0; i < 10; i++)
	{
		cout << "Id THREAD = " << this_thread::get_id() << " WORKS REST FUNCTION. " << "Was called for " << i + 1 << " times\n";
		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main()
{
	thread firstOne(DoWork);
	//firstOne.detach(); //завершит данный поток, как завершится основной из них.
	DoRest();

	firstOne.join(); //завершит данный поток, когда дойдет до конца

	return 0;
}