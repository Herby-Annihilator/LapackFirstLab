#pragma once
class ComplexValue
{
public:
    double RealPart;
    double ImaginaryPart;
    ComplexValue(double realPart, double imaginaryPart)
    {
        RealPart = realPart;
        ImaginaryPart = imaginaryPart;
    }
    ComplexValue() : ComplexValue(0, 0)
    {
    }
};

