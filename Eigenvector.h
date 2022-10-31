#pragma once

#include "Indexator.h"
#include "VectorIndexator.h"
#include "ComplexValue.h"
#include <string>

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
        _values = new ComplexValue[size];
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

    void ThrowIfNotEqual(Eigenvector* other)
    {
        double eps = 0.000001;
        if (other == nullptr)
            throw std::invalid_argument("Input vector is null");
        if (other->GetSize() != this->GetSize())
            throw exception("Size is not equal");
        for (int i = 0; i < this->GetSize(); i++)
        {
            if (abs(abs(other->Value(i)->Get().RealPart) - abs(this->Value(i)->Get().RealPart)) > eps)
            {
                string message = "real part (";
                message.append(std::to_string(other->Value(i)->Get().RealPart) + ")");
                message.append(" is not equal to real part (");
                message.append(std::to_string(this->Value(i)->Get().RealPart) + ")");
                throw exception(message.c_str());
            }
            else if (abs(abs(other->Value(i)->Get().ImaginaryPart) - abs(this->Value(i)->Get().ImaginaryPart)) > eps)
            {
                string message = "imaginary part (";
                message.append(std::to_string(other->Value(i)->Get().ImaginaryPart) + ")");
                message.append(" is not equal to imaginary part (");
                message.append(std::to_string(this->Value(i)->Get().ImaginaryPart) + ")");
                throw exception(message.c_str());
            }
        }
    }

    ~Eigenvector()
    {
        delete _indexator;
        delete _values;
    }
};

