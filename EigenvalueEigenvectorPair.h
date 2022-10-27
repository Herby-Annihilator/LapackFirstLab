#pragma once

#include "Eigenvalue.h"
#include "Eigenvector.h"

class EigenvalueEigenvectorPair
{
private:
    
public:
    Eigenvalue* _value;
    Eigenvector* _leftVector;
    Eigenvector* _rightVector;
    EigenvalueEigenvectorPair()
    {
        
    }
    EigenvalueEigenvectorPair(Eigenvalue* value, Eigenvector* leftVector, Eigenvector* rightVector)
    {
        _value = value;
        _leftVector = leftVector;
        _rightVector = rightVector;
    }

    Eigenvalue* GetValue()
    {
        return _value;
    }
    Eigenvector* GetLeftVector()
    {
        return _leftVector;
    }
    Eigenvector* GetRightVector()
    {
        return _rightVector;
    }

    ~EigenvalueEigenvectorPair()
    {
        delete &_value;
        delete &_leftVector;
        delete &_rightVector;
    }
};

