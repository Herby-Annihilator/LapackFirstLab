#pragma once
#include "Vector.h"
class MathHelper
{
public :
    MathHelper() {}

    Vector* CalculateResiduals(Matrix* matrix, Vector* vector, double eigenvalue)
    {
        Vector* result = *matrix * vector;
        Vector* y = *vector * eigenvalue;
        for (int i = 0; i < result->GetSize(); i++)
        {
            result->Value(i)->Set(result->Value(i)->Get() - y->Value(i)->Get());
        }
        return result;
    }
};

