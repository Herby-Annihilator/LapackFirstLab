#pragma once
template<typename T>
class Indexator
{
public:
    virtual T Get() = 0;
    virtual void Set(T value) = 0;
};

