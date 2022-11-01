#pragma once
#include "Matrix.h"
#include <vector>




class TestMatrix
{
private:
    Matrix* _testMatrix;
    vector<EigenvalueEigenvectorPair*>* _pairs;
    int _size;

    void InitTestMatrix()
    {
        _size = 4;
        double* matrix = new double[_size * _size] 
        {
            -2, 2, 2, 2,
            -3, 3, 2, 2,
            -2, 0, 4, 2,
            -1, 0, 0, 5,
        };
        _testMatrix = Matrix::Create(matrix, _size, _size);
    }

    void InitExpectedEigenvaluesAndEigenvectors()
    {
        _pairs = new vector<EigenvalueEigenvectorPair*>();
        AddFirstPair();
        AddSecondPair();
        AddThirdPair();
        AddFourthPair();
    }

    void AddFirstPair()
    {
        EigenvalueEigenvectorPair* pair;
        Eigenvalue* value;
        Eigenvector* leftVector, * rightVector;
        ComplexValue* complex;

        value = new Eigenvalue(1, 0);

        leftVector = new Eigenvector(_size);
        complex = new ComplexValue(-0.707107, 0);
        leftVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.707107, 0);
        leftVector->Value(1)->Set(*complex);
        complex = new ComplexValue(0, 0);
        leftVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0, 0);
        leftVector->Value(3)->Set(*complex);

        rightVector = new Eigenvector(_size);
        complex = new ComplexValue(-0.730297, 0);
        rightVector->Value(0)->Set(*complex);
        complex = new ComplexValue(-0.547723, 0);
        rightVector->Value(1)->Set(*complex);
        complex = new ComplexValue(-0.365148, 0);
        rightVector->Value(2)->Set(*complex);
        complex = new ComplexValue(-0.182574, 0);
        rightVector->Value(3)->Set(*complex);

        pair = new EigenvalueEigenvectorPair(value, leftVector, rightVector);
        _pairs->push_back(pair);
    }

    void AddSecondPair()
    {
        EigenvalueEigenvectorPair* pair;
        Eigenvalue* value;
        Eigenvector* leftVector, * rightVector;
        ComplexValue* complex;

        value = new Eigenvalue(2, 0);

        leftVector = new Eigenvector(_size);
        complex = new ComplexValue(-0.408248, 0);
        leftVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.816497, 0);
        leftVector->Value(1)->Set(*complex);
        complex = new ComplexValue(-0.408248, 0);
        leftVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0.000000, 0);
        leftVector->Value(3)->Set(*complex);

        rightVector = new Eigenvector(_size);
        complex = new ComplexValue(0.625543, 0);
        rightVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.625543, 0);
        rightVector->Value(1)->Set(*complex);
        complex = new ComplexValue(0.417029, 0);
        rightVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0.208514, 0);
        rightVector->Value(3)->Set(*complex);

        pair = new EigenvalueEigenvectorPair(value, leftVector, rightVector);
        _pairs->push_back(pair);
    }

    void AddThirdPair()
    {
        EigenvalueEigenvectorPair* pair;
        Eigenvalue* value;
        Eigenvector* leftVector, * rightVector;
        ComplexValue* complex;

        value = new Eigenvalue(3, 0);

        leftVector = new Eigenvector(_size);
        complex = new ComplexValue(0.000000, 0);
        leftVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.408248, 0);
        leftVector->Value(1)->Set(*complex);
        complex = new ComplexValue(-0.816497, 0);
        leftVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0.408248, 0);
        leftVector->Value(3)->Set(*complex);

        rightVector = new Eigenvector(_size);
        complex = new ComplexValue(-0.554700, 0);
        rightVector->Value(0)->Set(*complex);
        complex = new ComplexValue(-0.554700, 0);
        rightVector->Value(1)->Set(*complex);
        complex = new ComplexValue(-0.554700, 0);
        rightVector->Value(2)->Set(*complex);
        complex = new ComplexValue(-0.277350, 0);
        rightVector->Value(3)->Set(*complex);

        pair = new EigenvalueEigenvectorPair(value, leftVector, rightVector);
        _pairs->push_back(pair);
    }

    void AddFourthPair()
    {
        EigenvalueEigenvectorPair* pair;
        Eigenvalue* value;
        Eigenvector* leftVector, * rightVector;
        ComplexValue* complex;

        value = new Eigenvalue(4, 0);

        leftVector = new Eigenvector(_size);
        complex = new ComplexValue(0.000000, 0);
        leftVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.000000, 0);
        leftVector->Value(1)->Set(*complex);
        complex = new ComplexValue(-0.447214, 0);
        leftVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0.894427, 0);
        leftVector->Value(3)->Set(*complex);

        rightVector = new Eigenvector(_size);
        complex = new ComplexValue(0.5, 0);
        rightVector->Value(0)->Set(*complex);
        complex = new ComplexValue(0.5, 0);
        rightVector->Value(1)->Set(*complex);
        complex = new ComplexValue(0.5, 0);
        rightVector->Value(2)->Set(*complex);
        complex = new ComplexValue(0.5, 0);
        rightVector->Value(3)->Set(*complex);

        pair = new EigenvalueEigenvectorPair(value, leftVector, rightVector);
        _pairs->push_back(pair);
    }

    void PrintExpectedResult()
    {
        cout << endl << "You expects the following:" << endl << endl;
        cout << "Eigenvalues: " << 1 << " " << 2 << " " << 3 << " " << 4 << endl << endl;
        for (int i = 0; i < _size; i++)
        {
            cout << "Eigenvalue: " << _pairs->at(i)->GetValue()->RealPart << endl;
            cout << "left vector: ";
            for (int j = 0; j < _pairs->at(i)->GetLeftVector()->GetSize(); j++)
            {
                cout << _pairs->at(i)->GetLeftVector()->Value(j)->Get().RealPart << " ";
            }
            cout << endl << "right vector: ";
            for (int j = 0; j < _pairs->at(i)->GetRightVector()->GetSize(); j++)
            {
                cout << _pairs->at(i)->GetRightVector()->Value(j)->Get().RealPart << " ";
            }
            cout << endl << endl;
        }
        cout << endl;
    }

public:
    TestMatrix() {}

    void StartTest()
    {
        InitTestMatrix();
        cout << "Testing matrix:" << endl;
        _testMatrix->Display();
        cout << endl;        
        InitExpectedEigenvaluesAndEigenvectors();
        PrintExpectedResult();
        cout << "Starting of computing..." << endl;
        vector<EigenvalueEigenvectorPair*>* result = _testMatrix->ComputeEigenvaluesAndEigenvectors();
        cout << "Compairing...(you will get an exception if error will be occured)" << endl;
        if (result->size() != _size)
        {
            throw exception("Size of testMatrix is not equal to size of result");
        }
        cout << "Actuals are the following:" << endl;
        for (int i = 0; i < _size; i++)
        {
            _pairs->at(i)->GetValue()->ThrowIfNotEqual(result->at(i)->GetValue());
            cout << "Eigenvalue: " << _pairs->at(i)->GetValue()->RealPart << endl;

            _pairs->at(i)->GetLeftVector()->ThrowIfNotEqual(result->at(i)->GetLeftVector());
            cout << "left vector: ";
            for (int j = 0; j < result->at(i)->GetLeftVector()->GetSize(); j++)
            {
                cout << result->at(i)->GetLeftVector()->Value(j)->Get().RealPart << " ";
            }

            _pairs->at(i)->GetRightVector()->ThrowIfNotEqual(result->at(i)->GetRightVector());
            cout << endl << "right vector: ";
            for (int j = 0; j < result->at(i)->GetRightVector()->GetSize(); j++)
            {
                cout << result->at(i)->GetRightVector()->Value(j)->Get().RealPart << " ";
            }

            cout << endl << endl;
        }
        cout << "Success!" << endl;
    }
};

