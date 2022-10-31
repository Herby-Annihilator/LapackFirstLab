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

    void ThrowIfNotEqual(ComplexValue* other)
    {
        double eps = 0.000001;
        if (other == nullptr)
            throw std::invalid_argument("Input is null");
        string message = "";
        if (abs(abs(other->RealPart) - abs(this->RealPart)) > eps)
        {
            message.append("real part (");
            message.append(std::to_string(RealPart));
            message.append(") is not equal to real part(");
            message.append(std::to_string(other->RealPart) + ")");
            throw exception(message.c_str());
        }
        if (abs(abs(other->ImaginaryPart) - abs(this->ImaginaryPart)) > eps)
        {
            message.append("imaginary part(" 
                + std::to_string(ImaginaryPart) 
                + ") is not equal to imaginary part (" 
                + std::to_string(other->ImaginaryPart) 
                + ")");
            throw exception(message.c_str());
        }       
    }
};

