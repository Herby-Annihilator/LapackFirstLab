#pragma once

#include "Indexator.h"
#include "VectorIndexator.h"
#include "Matrix.h"
#include "Random.h"
#include <stdio.h>

extern "C" {
    void dscal_(int* N, double* alpha, double* X, int* incX);
}

class Vector
{
    friend class Matrix;
protected:
    int _size = 0;
    double* _vector;
    VectorIndexator<double>* _indexator;
    Vector() : Vector(0)
    {

    }
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

    static Vector* Create(int size)
    {
        return Create(size, 0);
    }

    static Vector* Create(double* vector, int size)
    {
        Vector* result = new Vector(size);
        result->_vector = vector;
        return result;
    }

    static Vector* CreateRandom(int size)
    {
        Vector* result = new Vector(size);
        Random random;
        for (int i = 0; i < size; i++)
        {
            result->Value(i)->Set(random.Next());
        }
        return result;
    }

    static Vector* CreateRandom(int size, double minimum, double maximum)
    {
        Vector* result = new Vector(size);
        Random random;
        for (int i = 0; i < size; i++)
        {
            result->Value(i)->Set(random.Next(minimum, maximum));
        }
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
        Vector* result = Copy(this);
        double alpha = value;
        dscal_(&n, &alpha, result->_vector, &incX);
        return result;
    }

    void Display()
    {
        for (int i = 0; i < GetSize(); i++)
        {
            printf("%0.3f ", _vector[i]);
        }
        printf("\r\n");
    }

    static Vector* Copy(Vector* pattern)
    {
        Vector* result = Create(pattern->GetSize(), 0);
        for (int i = 0; i < pattern->GetSize(); i++)
        {
            result->Value(i)->Set(pattern->Value(i)->Get());
        }
        return result;
    }

    bool Equal(Vector* other)
    {
        if (other == nullptr)
            return false;
        if (other->GetSize() != this->GetSize())
            return false;
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (other->Value(i)->Get() != this->Value(i)->Get())
                return false;
        }
        return true;
    }

    void ThrowIfNotEqual(Vector* other)
    {
        if (other == nullptr)
            throw std::invalid_argument("Input vector is null");
        if (other->GetSize() != this->GetSize())
            throw exception("Size is not equal");
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (other->Value(i)->Get() != this->Value(i)->Get())
            {
                string message = "";
                message.append(std::to_string(other->Value(i)->Get()));
                message.append(" is not equal to ");
                message.append(std::to_string(this->Value(i)->Get()));
                throw exception(message.c_str());
            }  
        }
    }

    ~Vector()
    {
        delete[] _vector;
        delete _indexator;
    }
};

