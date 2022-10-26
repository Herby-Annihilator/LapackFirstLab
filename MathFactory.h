#pragma once

#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <fstream>

using namespace std;

class MathFactory
{
public:

    Matrix* CreateMatrixFromFile(string fileName)
    {
        int cols, rows;
        GetMatrixSizeFromFile(fileName, &rows, &cols);
        Matrix* matrix = Matrix::Create(rows, cols);
        ReadMatrixFromFile(fileName, matrix);
        return matrix;
    }


    Vector* CreateVectorFromFile(string fileName)
    {
        int count;
        GetVectorSizeFromFile(fileName, &count);
        Vector* vector = Vector::Create(count, 0);
        ReadVectorFromFile(fileName, vector);
        return vector;
    }

private:

    void GetMatrixSizeFromFile(string filename, int* rowCount, int* colCount)
    {
        string line;
        ifstream reader(filename);
        if (reader.is_open())
        {
            // получить количество строк
            int rowsCounter = 0; // счетчик для подсчета количества строк
            while (getline(reader, line))
            {
                rowsCounter++;
            }
            *rowCount = rowsCounter;
            // получить количество столбцов
            int colsCounter = 1; // чисел в строке всегда на 1 больше, чем пробелов
            int lineLenght = line.length(); // оптимизация
            for (int i = 0; i < lineLenght; i++)
            {
                if (line[i] == ' ')
                    colsCounter++;
            }
            *colCount = colsCounter;
        }
        reader.close();
    }

    /// <summary>
    /// Считывание матрицы из файла
    /// </summary>
    void ReadMatrixFromFile(string filename, Matrix* matrix)
    {
        ifstream reader(filename);
        string line, line1;
        // произвести запись данных в матрицу
        for (int i = 0; getline(reader, line); i++)
        {
            for (int k = 0, j = 0; j < matrix->GetColsCount(); k++, j++)
            {
                while (line[k] != ' ' && line[k] != '\0')
                {
                    line1 += line[k];
                    k++;
                }
                // запись данных
                matrix->Value(i, j)->Set(stod(line1));
                line1.clear();
            }
        }
        reader.close();
    }


    /// <summary>
    /// Получение размерности вектора
    /// </summary>
    void GetVectorSizeFromFile(string filename, int* count)
    {
        string line;
        ifstream reader(filename);
        if (reader.is_open())
        {
            int counter = 0; // чисел в строке всегда на 1 больше, чем пробелов
            for (int i = 0; getline(reader, line, ' '); i++)
            {
                counter++;
            }
            *count = counter;
        }
        reader.close();
    }

    /// <summary>
    /// Считывание вектора из файла
    /// </summary>
    void ReadVectorFromFile(string filename, Vector* vector)
    {
        ifstream reader(filename);
        string line;
        // произвести запись данных в матрицу		
        for (int i = 0; getline(reader, line, ' '); i++)
        {
            vector->Value(i)->Set(stod(line));
        }
        reader.close();
    }

};

