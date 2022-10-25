#pragma once

#include"ComplexValue.h"

class Eigenvalue : public ComplexValue
{
public:
    Eigenvalue(double realPart, double imaginaryPart) : ComplexValue(realPart, imaginaryPart)
    {
        
    }

    Eigenvalue() : ComplexValue(0, 0)
    {
        
    }

    bool IsComplex()
    {
        return ImaginaryPart != 0;
    }
};

