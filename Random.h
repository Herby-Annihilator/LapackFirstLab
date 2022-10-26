#pragma once

#include <random>
using namespace std;

class Random
{
public:
    Random(){}
    int Next(int minimum, int maximum)
    {
        random_device rd;   // non-deterministic generator
        mt19937 gen(rd());  // to seed mersenne twister.
        uniform_int_distribution<> dist(minimum, maximum); // distribute results between minimum and maximum inclusive.
        return dist(gen);
    }
    int Next()
    {
        random_device rd;   // non-deterministic generator
        mt19937 gen(rd());  // to seed mersenne twister.
        return gen();
    }
};
