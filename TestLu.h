#pragma once
#include <iostream>

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
                if (i < j)
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

    void ThrowIfNotEqual(Matrix* first, Matrix* second, double eps)
    {
        string message = "";
        if (second == nullptr)
            throw std::invalid_argument("Input matrix is null");
        if (first->GetRowsCount() != second->GetRowsCount())
        {
            message.append("This rows count ("
                + std::to_string(first->GetRowsCount())
                + ") is not equal to second rows count("
                + std::to_string(second->GetRowsCount())
                + ")");
            throw exception(message.c_str());
        }
        if (first->GetColsCount() != second->GetColsCount())
        {
            message.append("This cols count ("
                + std::to_string(first->GetColsCount())
                + ") is not equal to second cols count("
                + std::to_string(second->GetColsCount())
                + ")");
            throw exception(message.c_str());
        }
        for (int i = 0; i < first->GetRowsCount(); i++)
        {
            for (int j = 0; j < first->GetColsCount(); j++)
            {
                if (abs(abs(first->Value(i, j)->Get()) - abs(second->Value(i, j)->Get())) > eps)
                {
                    message.append("This["
                        + std::to_string(i)
                        + "]["
                        + std::to_string(j)
                        + "] == ("
                        + std::to_string(first->Value(i, j)->Get())
                        + ") is not equal to second["
                        + std::to_string(i)
                        + "]["
                        + std::to_string(j)
                        + "] == ("
                        + std::to_string(second->Value(i, j)->Get())
                        + ")");
                    throw exception(message.c_str());
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
        cout << "Initializing test matrix... ";
        InitAMatrix();
        cout << "Done!" << endl;
        cout << "Initializing factorised matrix... ";
        InitFactorisedAMtrix();
        cout << "Done!" << endl;
        cout << "Initializing L and U matrices... ";
        InitLUMatrices();
        cout << "Done!" << endl;
        cout << "Getting LU-factorization... ";
        _aMatrix->GetLuFactorization();
        cout << "Done!" << endl;
        double eps = 0.1;
        cout << "Comparing L matrices... ";
        ThrowIfNotEqual(_lMatrix, _aMatrix->_lMatrix, eps);
        cout << "Done!" << endl << "Expected L matrix is: " << endl;
        _lMatrix->Display();
        cout << "Actual L matrix is: " << endl;
        _aMatrix->_lMatrix->Display();
        cout << "Comparing U matrices... ";
        ThrowIfNotEqual(_uMatrix, _aMatrix->_uMatrix, eps);
        cout << "Done!" << endl << "Expected U matrix is:" << endl;
        _uMatrix->Display();
        cout << "Actual U matrix is: " << endl;
        _aMatrix->_uMatrix->Display();
        cout << "Test successfuly completed!" << endl;
    }
};

