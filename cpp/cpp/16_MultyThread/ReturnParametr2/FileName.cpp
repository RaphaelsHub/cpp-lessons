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
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;
		cout << "The duration of this thread is " << duration.count() << ".\n";
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
};


int DoWork(int a, int b)
{
	Timer r;

	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork STARTED\n";

	this_thread::sleep_for(chrono::seconds(2));

	cout << "DoWork ENDED\n";

	return a + b;
}

int main()
{
	Timer entire;
	int res;

	//само лямда выражение, передали рес и решили его судьбу.
	thread th([&res]() {res = DoWork(2, 1); });

	Timer b;
	for (size_t i = 0; i < 10; i++)
	{
		cout << "MAIN WORKS: " << i + 1 << " IdThread: " << this_thread::get_id() << "\n";
		this_thread::sleep_for(chrono::seconds(1));
	}


	th.join();
	cout << "Result of sum is = " << res << " \n";

	return 0;
}