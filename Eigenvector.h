#pragma once

#include "Indexator.h"
#include "VectorIndexator.h"
#include "ComplexValue.h"

class Eigenvector
{
    int _size;
    ComplexValue* _values;
    VectorIndexator<ComplexValue>* _indexator;

public:

    Eigenvector() : Eigenvector(0)
    {
        
    }

    Eigenvector(int size)
    {
        _size = size;
        _values = new ComplexValue(0, 0);
        _indexator = new VectorIndexator<ComplexValue>(_values);
    }
    int GetSize()
    {
        return _size;
    }

    bool IsComplex()
    {
        bool isComplex = false;
        for (int i = 0; i < GetSize(); i++)
        {
            if (_values[i].ImaginaryPart != 0)
            {
                isComplex = true;
                break;
            }
        }
        return isComplex;
    }

    Indexator<ComplexValue>* Value(int index)
    {
        if (_indexator == nullptr)
            _indexator = new VectorIndexator<ComplexValue>(_values);
        _indexator->CurrentIndex = index;
        return _indexator;
    }

    ~Eigenvector()
    {
        delete _indexator;
        delete _values;
    }
};

