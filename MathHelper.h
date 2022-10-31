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
        double delta;
        for (int i = 0; i < result->GetSize(); i++)
        {
            delta = result->Value(i)->Get() - y->Value(i)->Get();
            result->Value(i)->Set(delta);
        }
        return result;
    }
};

