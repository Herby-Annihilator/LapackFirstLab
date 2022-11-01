#pragma once

#include "Matrix.h"

class Matrix;

class TestLu
{
private:
    Matrix* _aMatrix;
    Matrix* _factorisedAMatrix;
    Matrix* _lMatrix;
    Matrix* _uMatrix;
    int _size;

    void InitAMatrix()
    {
        double* matrix = new double[_size * _size] 
        {
            1.0,  1.2,  1.4,  1.6,  1.8,  2.0,  2.2, 2.4,  2.6,
            1.2,  1.0,  1.2,  1.4,  1.6,  1.8,  2.0,  2.2,  2.4,
            1.4,  1.2,  1.0,  1.2,  1.4,  1.6,  1.8,  2.0,  2.2,
            1.6,  1.4,  1.2,  1.0,  1.2,  1.4,  1.6,  1.8,  2.0,
            1.8,  1.6,  1.4,  1.2,  1.0,  1.2,  1.4,  1.6,  1.8,
            2.0,  1.8,  1.6,  1.4,  1.2,  1.0,  1.2,  1.4,  1.6,
            2.2,  2.0,  1.8,  1.6,  1.4,  1.2,  1.0,  1.2,  1.4,
            2.4,  2.2,  2.0,  1.8,  1.6,  1.4,  1.2,  1.0,  1.2,
            2.6,  2.4,  2.2,  2.0,  1.8,  1.6,  1.4,  1.2,  1.0,
        }; 
        _aMatrix = Matrix::Create(matrix, _size, _size);
    }

    void InitFactorisedAMtrix()
    {
        double* matrix = new double[_size * _size]
        {
            2.6,   2.4,  2.2,  2.0,  1.8,  1.6,  1.4,  1.2,  1.0,
            0.4,   0.3,  0.6,  0.8,  1.1,  1.4,  1.7,  1.9,  2.2,
            0.5,  -0.4,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4,  2.8,
            0.5,  -0.3,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,  2.4,
            0.6,  -0.3,  0.0,  0.0,  0.4,  0.8,  1.2,  1.6,  2.0,
            0.7,  -0.2,  0.0,  0.0,  0.0,  0.4,  0.8,  1.2,  1.6,
            0.8,  -0.2,  0.0,  0.0,  0.0,  0.0,  0.4,  0.8,  1.2,
            0.8,  -0.1,  0.0,  0.0,  0.0,  0.0,  0.0,  0.4,  0.8,
            0.9,  -0.1,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.4,
        };
        _factorisedAMatrix = Matrix::Create(matrix, _size, _size);
    }

    void InitLUMatrices()
    {
        if (_factorisedAMatrix == nullptr)
            throw std::invalid_argument("_factorisedAMatrix is null");
        _lMatrix = Matrix::Create(_size, _size);
        _uMatrix = Matrix::Create(_size, _size);
        for (int i = 0; i < _factorisedAMatrix->GetRowsCount(); i++)
        {
            for (int j = 0; j < _factorisedAMatrix->GetColsCount(); j++)
            {
                if (i >= j)
                {
                    _uMatrix->Value(i, j)->Set(_factorisedAMatrix->Value(i, j)->Get());
                }
                else
                {
                    _lMatrix->Value(i, j)->Set(_factorisedAMatrix->Value(i, j)->Get());
                }
            }
        }
    }
public:
    TestLu()
    {
        _size = 9;
        _aMatrix = nullptr;
        _lMatrix = nullptr;
        _uMatrix = nullptr;
        _factorisedAMatrix = nullptr;
    }

    void GetLuFactorization_CheckMatrices_ShouldNotThrow()
    {
        InitAMatrix();
        InitFactorisedAMtrix();
        InitLUMatrices();
    }
};

