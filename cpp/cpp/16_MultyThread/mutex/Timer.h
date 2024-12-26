#pragma once
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