#pragma once

#include "Indexator.h"
template<typename T>
class MatrixIndexator : public Indexator<T>
{
private:
    T* _matrix;
    int _columnsCountInMatrix;
public:
    MatrixIndexator(T* matrix, int columnCount)
    {
        _matrix = matrix;
        _columnsCountInMatrix = columnCount;
    }
    int CurrentRow = 0;
    int CurrentColumn = 0;
    T Get() override
    {
        return *(_matrix + CurrentRow * _columnsCountInMatrix + CurrentColumn);
    }
    void Set(T value) override
    {
        *(_matrix + CurrentRow * _columnsCountInMatrix + CurrentColumn) = value;
    }
};

