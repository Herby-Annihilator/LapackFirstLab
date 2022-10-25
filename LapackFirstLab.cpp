using namespace std;
#include <iostream>
#include "Matrix.h"
#include "Vector.h"

int main() 
{
    Matrix show = Matrix::Create(3, 3, 0);
    for (int i = 0; i < show.GetRowsCount(); i++)
    {
        for (int j = 0; j < show.GetColsCount(); j++)
        {
            show.Value(i, j)->Set(i);
        }
    }
    printf("Matrix Show: \r\n");
    show.Display();

    Matrix matrixA = Matrix::Create(3, 3, 3);
    printf("Matrix A: \r\n");
    matrixA.Display();

    Matrix matrixB = Matrix::Create(3, 3, 4);
    printf("Matrix B: \r\n");
    matrixB.Display();

    Matrix* matrixC = show * &matrixB;
    printf("Matrix C: \r\n");
    matrixC->Display();

    Vector* vector = Vector::Create(5, 10);
    printf("Vector D: \r\n");
    vector->Display();
    printf("Vector D * 5: \r\n");
    Vector* vec = *vector * 5;
    vec->Display();
    return 0;
}