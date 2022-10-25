#pragma once

#include "Indexator.h"
template<typename T>
class VectorIndexator : public Indexator<T>
{
private:
    T* _vector;
public:
    VectorIndexator(T* vector)
    {
        _vector = vector;
        CurrentIndex = 0;
    }
    int CurrentIndex;
    T Get() override
    {
        return _vector[CurrentIndex];
    }

    void Set(T value) override
    {
        _vector[CurrentIndex] = value;
    }
};

