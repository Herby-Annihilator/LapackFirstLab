#pragma once

#include "Vector.h"
#include "Eigenvector.h"
#include "VectorIndexator.h"

class EigenvectorToVectorAdapter : public Vector
{
public:
    EigenvectorToVectorAdapter(Eigenvector* vector)
    {
        this->_size = vector->GetSize();
        this->_vector = new double[_size];
        this->_indexator = new VectorIndexator<double>(_vector);
        for (int i = 0; i < _size; i++)
        {
            this->Value(i)->Set(vector->Value(i)->Get().RealPart);
        }        
    }
};

