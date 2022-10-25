#pragma once

#include "Indexator.h"
#include "VectorIndexator.h"
#include "Matrix.h"
#include <stdio.h>

extern "C" {
    void dscal_(int* N, double* alpha, double* X, int* incX);
}

class Vector
{
    friend class Matrix;
private:
    int _size = 0;
    double* _vector;
    VectorIndexator<double>* _indexator;
public:
    Vector(int size)
    {
        _size = size;
        _vector = new double[_size];
        _indexator = new VectorIndexator<double>(_vector);
    }
    static Vector* Create(int size, double value)
    {
        Vector* result = new Vector(size);
        result->FillBy(value);
        return result;
    }

    void FillBy(double value)
    {
        for (int i = 0; i < GetSize(); i++)
        {
            _vector[i] = value;
        }
    }

    int GetSize()
    {
        return _size;
    }

    Indexator<double>* Value(int index)
    {
        if (_indexator == nullptr)
            _indexator = new VectorIndexator<double>(_vector);
        _indexator->CurrentIndex = index;
        return _indexator;
    }

    Vector* operator*(double value)
    {
        int n = GetSize(), incX = 1;
        double alpha = value;
        dscal_(&n, &alpha, _vector, &incX);
        return this;
    }

    void Display()
    {
        for (int i = 0; i < GetSize(); i++)
        {
            printf("%0.3f ", _vector[i]);
        }
        printf("\r\n");
    }

    
};

