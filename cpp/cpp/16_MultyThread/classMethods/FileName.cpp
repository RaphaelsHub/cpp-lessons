#include <iostream>
#include <string>
#include <thread>
#include <chrono>

// лябда выражение для получение результата
using namespace std;

class Timer
{
public:
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> dur = finish - start;
		std::cout << "Duration is: " << dur.count() << " seconds\n";
	}

private:
	std::chrono::high_resolution_clock::time_point start, finish;
};

class MyClass
{
public:
	void DoWork()
	{
		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoWork STARTED\n";

		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoWork ENDED\n";
	}

	void DoRest(int& a)
	{
		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoRest STARTED\n";

		a = a * 2;

		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoRest ENDED\n";
	}

	int DoSum(int a, int b)
	{
		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoSum STARTED\n";

		this_thread::sleep_for(chrono::seconds(2));

		cout << "DoSum ENDED\n";

		return a + b;
	}
};

int main()
{
	Timer b;

	MyClass A;
	int a = 4;
	int res;

	//thread th([&]() { A.DoRest(a); }); // thread th(A.DoWork,std::ref(a));
	//thread th1([&]() { A.DoWork(); });
	//thread th2([&]() {res = A.DoSum(a, a); });

	thread th(&MyClass::DoRest, A, std::ref(a));
	thread th1(&MyClass::DoWork, A);
	thread th2(&MyClass::DoSum, A, 3, 4);


	for (size_t i = 0; i < 10; i++)
	{
		cout << "MAIN WORKS: " << i + 1 << " IdThread: " << this_thread::get_id() << "\n";
		this_thread::sleep_for(chrono::seconds(1));
	}

	th.join();
	th1.join();
	th2.join();
}