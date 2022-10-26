#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "Random.h"
#include "MatrixIndexator.h"
#include "Indexator.h"
#include "Vector.h"
#include "EigenvalueEigenvectorPair.h"
#define MATR double*
#define VEC double*
#define IN
#define OUT


extern "C" {
    void dgemm_(char* TransA, char* TransB, int* M, int* N,
        int* K, double* alpha, IN MATR A,
        int* lda, IN MATR B, int* ldb,
        double* beta, OUT MATR C, int* ldc);

    void dgemv_(char* TRANS, int* M, int* N, double* ALPHA, IN MATR A, int* LDA,
        IN VEC X, int* INCX, double* BETA, OUT MATR Y, int* INCY);

    void dgeev_(char* JOBVL, char* JOBVR, int* N, IN OUT MATR A, int* LDA, OUT VEC WR,
        OUT VEC WI, OUT MATR VL, int* LDVL, OUT MATR VR,
        int* LDVR, OUT VEC WORK, int* LWORK, int* INFO);
}

class Vector;

class Matrix
{
private:
    int _rowsCount;
    int _colsCount;
    double* _matrix;
    MatrixIndexator<double>* _indexator;
    Matrix(int rowsCount, int colsCount)
    {
        _rowsCount = rowsCount;
        _colsCount = colsCount;
        _matrix = new double[rowsCount * colsCount];
        _indexator = new MatrixIndexator<double>(_matrix, _colsCount);
    }

    static void TransposeSquare(Matrix* matrix)
    {
        if (matrix->GetColsCount() != matrix->GetRowsCount())
        {
            throw std::invalid_argument("The matrix is not a square matrix");
        }
        else
        {
            double tmp, tmp1;
            for (int i = 0; i < matrix->GetRowsCount(); i++)
            {
                for (int j = i + 1; j < matrix->GetColsCount(); j++)
                {
                    tmp = matrix->Value(j, i)->Get();
                    tmp1 = matrix->Value(i, j)->Get();

                    matrix->Value(j, i)->Set(tmp1);
                    matrix->Value(i, j)->Set(tmp);

                    tmp = matrix->Value(j, i)->Get();
                    tmp1 = matrix->Value(i, j)->Get();
                }
            }
        }
    }

public:

    int GetRowsCount()
    {
        return _rowsCount;
    }

    int GetColsCount()
    {
        return _colsCount;
    }

    Indexator<double>* Value(int row, int col)
    {
        if (_indexator == nullptr)
            _indexator = new MatrixIndexator<double>(_matrix, _colsCount);
        _indexator->CurrentRow = row;
        _indexator->CurrentColumn = col;
        return _indexator;
    }

    static Matrix* Create(int rowsCount, int colsCount, double value)
    {
        Matrix* matrix = new Matrix(rowsCount, colsCount);
        matrix->FillBy(value);
        return matrix;
    }

    static Matrix* Create(int rowsCount, int colsCount)
    {
        return Create(rowsCount, colsCount, 0);
    }

    static Matrix* CreateIdentity(int rows)
    {
        Matrix* matrix = Create(rows, rows);
        for (int i = 0; i < rows; i++)
        {
            matrix->Value(i, i)->Set(1);
        }
    }

    static Matrix* CreateRandom(int rows, int cols)
    {
        Matrix* result = new Matrix(rows, cols);
        Random random;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result->Value(i, j)->Set(random.Next());
            }
        }
        return result;
    }

    static Matrix* CreateRandom(int rows, int cols, int minimum, int maximum)
    {
        Matrix* result = new Matrix(rows, cols);
        Random random;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                result->Value(i, j)->Set(random.Next(minimum, maximum));
            }
        }
        return result;
    }

    static Matrix* Copy(Matrix* pattern)
    {
        Matrix* result = new Matrix(pattern->GetRowsCount(), pattern->GetColsCount());
        for (int i = 0; i < pattern->GetRowsCount(); i++)
        {
            for (int j = 0; j < pattern->GetColsCount(); j++)
            {
                result->Value(i, j)->Set(pattern->Value(i, j)->Get());
            }
        }
        return result;
    }

    void FillBy(double value)
    {
        for (int i = 0; i < GetRowsCount(); i++)
        {
            for (int j = 0; j < GetColsCount(); j++)
            {
                Value(i, j)->Set(value);
            }
        }
    }

    void Display()
    {
        for (int i = 0; i < GetRowsCount(); i++)
        {
            for (int j = 0; j < GetColsCount(); j++)
            {
                printf("%0.3f ", Value(i, j)->Get());
            }
            printf("\r\n");
        }
    }

    Matrix* Multiply(Matrix* other)
    {
        Matrix* result = new Matrix(GetRowsCount(), other->GetColsCount());
        result->FillBy(1);
        char transA = 'T', transB = 'T';
        int m = GetRowsCount(), n = other->GetColsCount(), k = GetColsCount();
        double alpha = 1, beta = 0;
        int lda = GetRowsCount(), ldb = other->GetColsCount(), ldc = GetColsCount();
        dgemm_(&transA,
            &transB,
            &m,
            &n,
            &k,
            &alpha,
            _matrix,
            &lda,
            other->_matrix,
            &ldb,
            &beta,
            result->_matrix,
            &ldc);
        Transpose(result);
        return result;
    }

    Matrix* operator*(Matrix* other)
    {
        return Multiply(other);
    }

    Vector* operator*(Vector* vector)
    {
        char trans = 'N';
        int m = GetRowsCount(), n = GetColsCount(), lda = GetRowsCount(), incX = 1, incY = 1;
        double alpha = 1, beta = 1;
        Vector* result = Vector::Create(vector->GetSize(), 0);
        dgemv_(&trans,
            &m,
            &n,
            &alpha,
            _matrix,
            &lda,
            vector->_vector,
            &incX,
            &beta,
            result->_vector,
            &incY);
        return result;
    }

    vector<EigenvalueEigenvectorPair> ComputeEigenvaluesAndEigenvectors()
    {
        if (GetRowsCount() != GetColsCount())
        {
            throw std::invalid_argument("Matrix must be square");
        }
        Matrix* tmp = Copy(this);
        Transpose(tmp);
        char jobvl = 'V', jobvr = 'V';
        int n = GetRowsCount(), lda = n, ldvl = n, ldvr = n, lwork = 4 * n + 1, info = 0;
        vector<EigenvalueEigenvectorPair> answer;
        double* wr = new double[n], * wi = new double[n];
        double* vl = new double[ldvl * n], * vr = new double[ldvr * n];
        double* work = new double[lwork];
        dgeev_(&jobvl,
            &jobvr,
            &n,
            tmp->_matrix,
            &lda,
            wr,
            wi,
            vl,
            &ldvl,
            vr,
            &ldvr,
            work,
            &lwork,
            &info);
        if (info == 0)
        {
            lwork = work[0];
            if (lwork == -1)
            {
                throw std::exception("Some fuckin thing happend");
            }
            else
            {
                Eigenvector leftVector(n);
                Eigenvector rightVector(n);
                Eigenvalue value;
                ComplexValue leftComplex;
                ComplexValue rightComplex;
                
                for (int i = 0; i < n; i++)
                {
                    value.RealPart = wr[i];
                    value.ImaginaryPart = wi[i];
                    for (int j = 0; j < n; j++)
                    {
                        leftComplex.RealPart = *(vl + i * n + j);
                        rightComplex.RealPart = *(vr + i * n + j);
                        if (value.IsComplex())
                        {
                            // что-то с vl/vr надо сделать, я хуй его знаю
                        }
                        leftVector.Value(j)->Set(leftComplex);
                        rightVector.Value(j)->Set(rightComplex);
                    }
                    EigenvalueEigenvectorPair pair(value, leftVector, rightVector);
                    answer.push_back(pair);
                }
                
            }
        }
        else
        {
            if (info > 0)
            {
                throw std::exception("the QR algorithm failed to compute all the eigenvalues, and no eigenvectors have been computed; ");
            }
            else
            {
                string message = "the";
                message.append(std::to_string(info));
                message.append(" - th argument had an illegal value.");
                throw std::exception(message.c_str());
            }
        }
        delete tmp;
        return answer;
    }

    static void Transpose(Matrix* matrix)
    {
        if (matrix->GetRowsCount() == matrix->GetColsCount())
        {
            TransposeSquare(matrix);
        }
        else
        {
            Matrix* result = new Matrix(matrix->GetColsCount(), matrix->GetRowsCount());
            for (int i = 0; i < matrix->GetRowsCount(); i++)
            {
                for (int j = 0; j < matrix->GetColsCount(); j++)
                {
                    result->Value(j, i)->Set(matrix->Value(i, j)->Get());
                }
            }
            delete matrix;
            matrix = result;
        }
    }

    Matrix* Transpose()
    {
        Matrix* result = Copy(this);
        Transpose(result);
        return result;
    }
        
};

