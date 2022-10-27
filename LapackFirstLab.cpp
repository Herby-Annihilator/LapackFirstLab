using namespace std;

#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <iostream>
#include "MathFactory.h"
#include "MathHelper.h"
#include "EigenvectorToVectorAdapter.h"

void DemonstrateArithmeticOperations()
{
    const string MATRIX_A_FILE_NAME = "matrixA.txt";
    const string MATRIX_B_FILE_NAME = "matrixB.txt";
    const string VECTOR_C_FILE_NAME = "vectorC.txt";

    MathFactory factory;
    cout << "Чтение матрицы А из файла " << MATRIX_A_FILE_NAME << endl;
    Matrix* matrixA = factory.CreateMatrixFromFile(MATRIX_A_FILE_NAME);

    cout << "Чтение матрицы B из файла " << MATRIX_B_FILE_NAME << endl;
    Matrix* matrixB = factory.CreateMatrixFromFile(MATRIX_B_FILE_NAME);

    cout << "Чтение вектора C из файла " << VECTOR_C_FILE_NAME << endl;
    Vector* vectorC = factory.CreateVectorFromFile(VECTOR_C_FILE_NAME);

    Vector* tmpVector;
    Matrix* tmpMatrix;

    cout << "\\\\------------------------основной вывод----------------------//" << endl << endl;

    cout << endl << endl;
    cout << "Матрица А:" << endl << endl;
    matrixA->Display();
    cout << endl << endl;

    cout << "Матрица B:" << endl << endl;
    matrixB->Display();
    cout << endl << endl;

    cout << endl << endl << "Вектор C:" << endl << endl;
    vectorC->Display();
    cout << endl << endl;

    cout << "Результат умножения векотора C на 5:" << endl << endl;
    tmpVector = *vectorC * 5;
    tmpVector->Display();
    cout << endl << endl;

    cout << "Результат умножения матрицы А на вектор С:" << endl << endl;
    tmpVector = *matrixA * vectorC;
    tmpVector->Display();
    cout << endl << endl;

    cout << "Результат умножения матрицы А на матрицу В:" << endl << endl;
    tmpMatrix = *matrixA * matrixB;
    tmpMatrix->Display();
    cout << endl << endl;

    cout << "\\\\------------------------конец----------------------//" << endl << endl;
    /*delete matrixA;
    delete matrixB;
    delete tmpMatrix;
    delete vectorC;
    delete tmpVector;*/
}

void ComputeEigenvaluesAndEigenvectors()
{
    const string MATRIX_FILE_NAME = "matrix.txt";
    MathHelper helper;
    Vector* residuals;
    MathFactory factory;
    cout << "Чтение матрицы из файла " << MATRIX_FILE_NAME << endl;
    Matrix* matrixA = factory.CreateMatrixFromFile(MATRIX_FILE_NAME);

    cout << "\\\\------------------------основной вывод----------------------//" << endl << endl;

    cout << "Матрица:" << endl << endl;
    matrixA->Display();

    cout << "Расчет собственных чисел и векторов..." << endl << endl;
    vector<EigenvalueEigenvectorPair*>* result = matrixA->ComputeEigenvaluesAndEigenvectors();

    for (int i = 0; i < result->size(); i++)
    {
        cout << "Собственное число: " << result->at(i)->GetValue()->RealPart;
        if (result->at(i)->GetValue()->IsComplex())
        {
            cout << " +- i * " << result->at(i)->GetValue()->ImaginaryPart;
        }
        cout << endl;
        cout << "Правый собственный вектор:" << endl;
        cout << "[ ";
        for (int j = 0; j < result->at(i)->GetRightVector()->GetSize(); j++)
        {
            cout << result->at(i)->GetRightVector()->Value(j)->Get().RealPart;
            if (result->at(i)->GetRightVector()->Value(j)->Get().ImaginaryPart != 0)
            {
                cout << " +- i * " << result->at(i)->GetRightVector()->Value(j)->Get().ImaginaryPart;
            }
            cout << "; ";
        } 
        cout << "]";
        cout << endl;
        if (!result->at(i)->GetRightVector()->IsComplex())
        {
            residuals = helper.CalculateResiduals(matrixA,
                new EigenvectorToVectorAdapter(result->at(i)->GetRightVector()),
                result->at(i)->GetValue()->RealPart);
            cout << "Вектор невязок:" << endl;
            residuals->Display();
        }
        cout << endl << "Левый собственный вектор:" << endl;
        cout << "[ ";
        for (int j = 0; j < result->at(i)->GetLeftVector()->GetSize(); j++)
        {
            cout << result->at(i)->GetLeftVector()->Value(j)->Get().RealPart;
            if (result->at(i)->GetLeftVector()->Value(j)->Get().ImaginaryPart != 0)
            {
                cout << " +- i * " << result->at(i)->GetLeftVector()->Value(j)->Get().ImaginaryPart;
            }
            cout << "; ";
        }
        cout << "]";
        //if (!result->at(i)->GetLeftVector()->IsComplex())
        //{
        //    residuals = helper.CalculateResiduals(matrixA,
        //        new EigenvectorToVectorAdapter(result->at(i)->GetLeftVector()),
        //        result->at(i)->GetValue()->RealPart);
        //    cout << endl << "Вектор невязок:" << endl;
        //    residuals->Display();
        //}
        cout << endl << endl;
    }

    cout << "\\\\------------------------конец----------------------//" << endl << endl;

    //delete matrixA;
}

void DemonstrateArithmeticOperationsWithLargeMatriciesAndVectors()
{
    int size;
    double minimum, maximum;
    cout << endl << "Введите размерность матрицы А и вектора С: ";
    cin >> size;
    cout << "Введите минимальное значение для элеметов: ";
    cin >> minimum;
    cout << "Введите максимальное значение для элеметов: ";
    cin >> maximum;
    Matrix* matrix = Matrix::CreateRandom(size, size, minimum, maximum);
    Vector* vector = Vector::CreateRandom(size, minimum, maximum);

    cout << endl << endl << "\\\\--------------------------генерация отчета------------------------//";

    cout << endl << endl << "Матрица А:" << endl << endl;
    matrix->Display();
    
    cout << endl << endl << "Вектор С:" << endl << endl;
    vector->Display();
    
    cout << endl << endl << "Введите число, на которое следует умножить вектор: ";
    double mult;
    cin >> mult;
    cout << endl << "Результат умножения вектора на " << mult << ":" << endl << endl;
    Vector* vectorMult = *vector * mult;
    vectorMult->Display();

    cout << endl << endl << "Результат умножения матрицы А на вектор В:" << endl << endl;
    vectorMult = *matrix * vector;
    vectorMult->Display();

    cout << endl << endl << "Генерация матрицы В:" << endl << endl;
    Matrix* matrixB = Matrix::CreateRandom(size, size, minimum, maximum);
    matrixB->Display();

    cout << endl << endl << "Результат умножения матицы А на матрицу В:" << endl << endl;
    Matrix* matrixMult = *matrix * matrixB;
    matrixMult->Display();

    cout << endl << endl << "\\\\--------------------------конец отчета------------------------//" << endl << endl;
}

int main() 
{
    setlocale(LC_ALL, "ru-RU");
    try
    {
        bool exit = false;
        int variant = 0;
        do
        {
            cout << "1 - Арифметические операции" 
                << endl 
                << "2 - Расчет собственных значений и векторов" 
                << endl 
                << "3 - Арифметика с рандомными матрицей и вектором указанного размера"
                << endl
                << "4 - Выход"
                << endl
                << "Ваш выбор: ";

            cin >> variant;  // и что, что не безопасно и так делать нельзя? Это же С++, чего вы хотели? Даже париться не буду.
            if (variant == 1) // ну да - костыль, а что поделать?)
            {
                DemonstrateArithmeticOperations();
            }
            else if (variant == 2)
            {
                ComputeEigenvaluesAndEigenvectors();
            }
            else if (variant == 3)
            {
                DemonstrateArithmeticOperationsWithLargeMatriciesAndVectors();
            }
            else if (variant == 4)
            {
                exit = true;
            }
            else
            {
                cout << "Повтори ввод!!!!!!!!" << endl;
            }
        } while (!exit);
    }
    catch (const std::exception& ex)
    {
        cout << endl << endl << "Exception: ";
        cout << ex.what();
        return 0;
    }
    return 0;
}