#pragma once
#include<iostream>

namespace Mechanism
{
    int upperBound;
    int lowerBound;

    class Counter
    {
    private:
        int count;

    public:
        Counter(int n) { (n <= upperBound) ? count = n : count = upperBound; }
        ~Counter() = default;
        void Reset(int n) { (n <= upperBound) ? count = n : count = upperBound; }

        int Run()
        {
            if (count > lowerBound)
                return count--;
            else
                return lowerBound;
        }
    };
}

inline void OpenNameSpace()
{
    using Mechanism::lowerBound;
    using Mechanism::upperBound;

    lowerBound = 0;
    upperBound = 100;

    int i;
    Mechanism::Counter A(10);

    do
    {
        i = A.Run();
        std::cout << i << " ";
    }
    while (i > lowerBound);

    std::cout << "\n";
}
