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

    Vector* _vectorB;
    Vector* _solutionVector;
    int _size;
    int _vectorsSize;

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

    void CompareMetricesAndThrowIfNotEqual(Matrix* first, Matrix* second, double eps)
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

    void CompareVectorsAndThrowIfNotEqual(Vector* first, Vector* second, double eps)
    {
        if (first == nullptr)
            throw invalid_argument("First vector is null!");
        if (second == nullptr)
            throw invalid_argument("Second vector is null!");
        if (first->GetSize() != second->GetSize())
        {
            string message = "First vector size (" + std::to_string(first->GetSize()) + ") not equal to second vector size ("
                + std::to_string(second->GetSize()) + ")";
            throw exception(message.c_str());
        }
        for (int i = 0; i < first->GetSize(); i++)
        {
            if (abs(abs(first->Value(i)->Get()) - abs(second->Value(i)->Get())) > eps)
            {
                string message = "first[" + std::to_string(i) + "] == (" +  std::to_string(first->Value(i)->Get())
                    + ") is not equal to second[" + std::to_string(i) + "] == ("
                    + std::to_string(second->Value(i)->Get()) + ")";
                throw exception(message.c_str());
            }
        }
    }

    void InitAMatrixForSolveByLUMethod()
    {
        double* matrix = new double[_vectorsSize * _vectorsSize]
        {
            2, -4, 2,
            4, 5, -3,
            -3, -4, 7,
        };
        _aMatrix = Matrix::Create(matrix, _vectorsSize, _vectorsSize);
    }
    void InitVectorBForSolveByLUMethod()
    {
        double* vector = new double[_vectorsSize]
        {
            5, 1, 0,
        };
        _vectorB = Vector::Create(vector, _vectorsSize);
    }
    void InitResultVectorForSolveByLUMethod()
    {
        double* vector = new double[_vectorsSize]
        {
            1.125, -0.625, 0.125,
        };
        _solutionVector = Vector::Create(vector, _vectorsSize);
    }

public:
    TestLu()
    {
        _size = 9;
        _vectorsSize = 3;
        _aMatrix = nullptr;
        _lMatrix = nullptr;
        _uMatrix = nullptr;
        _factorisedAMatrix = nullptr;
        _vectorB = nullptr;
        _solutionVector = nullptr;
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
        CompareMetricesAndThrowIfNotEqual(_lMatrix, _aMatrix->_lMatrix, eps);
        cout << "Done!" << endl << "Expected L matrix is: " << endl;
        _lMatrix->Display();
        cout << "Actual L matrix is: " << endl;
        _aMatrix->_lMatrix->Display();
        cout << "Comparing U matrices... ";
        CompareMetricesAndThrowIfNotEqual(_uMatrix, _aMatrix->_uMatrix, eps);
        cout << "Done!" << endl << "Expected U matrix is:" << endl;
        _uMatrix->Display();
        cout << "Actual U matrix is: " << endl;
        _aMatrix->_uMatrix->Display();
        cout << "Test successfuly completed!" << endl;
    }

    void SolveByLU_CheckResultVector_ShouldNotThrow()
    {
        cout << "Initializing test matrix... ";
        InitAMatrixForSolveByLUMethod();
        cout << "Done!" << endl;

        cout << "Initializing vector B... ";
        InitVectorBForSolveByLUMethod();
        cout << "Done!" << endl;

        cout << "Initializing result vector... ";
        InitResultVectorForSolveByLUMethod();
        cout << "Done!" << endl;

        cout << "Invoke SolveByLU method... ";
        Vector* result = _aMatrix->SolveByLU(_vectorB);
        cout << "Done!" << endl;

        cout << "Comparing expected and actual vectors...";
        CompareVectorsAndThrowIfNotEqual(_solutionVector, result, 0.1);
        cout << "Done!" << endl << "Expected vector is: ";
        _solutionVector->Display();
        cout << "Actual vector is: ";
        result->Display();

        cout << "Test successfuly completed!" << endl;
    }
};

