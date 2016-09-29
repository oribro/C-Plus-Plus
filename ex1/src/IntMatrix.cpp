//
// Created by OriB on 24/08/2015.
//

// IntMatrix.cpp

// -------------- Includes -------------------
#include "IntMatrix.h"
#include <cassert>

using namespace std;


// --------------------------------------------------------------------------------------
// This file contains the implementation of the class IntMatrix.
// --------------------------------------------------------------------------------------


/**
* Default constructor.
* Initiate a matrix of dimension 0 as null matrix.
* This constructor is used to construct a matrix object with no values.
* @return a copy of the constructed matrix.
*/
IntMatrix::IntMatrix()
{
    _pMatrix = nullptr;
    _rows = 0;
    _cols = 0;
}
/**
* constructor.
* Initiate a matrix of size numOfRows X numOfCols.
* The matrix is represented as an array of rows, where each cell in
* the array of rows stores an array of columns, implemented in
* a semi dynamic manner.
* @param numOfRows - the number of rows.
* @param numOfCols - the number of columns.
* @param matrix - the values of the matrix.
* @return a copy of the constructed matrix.
*/
IntMatrix::IntMatrix(int numOfRows, int numOfCols, int **matrix)
{
    _rows = numOfRows;
    _cols = numOfCols;
    _pMatrix = matrix;
}


/**
 * Copy constructor.
 * @param other - the object to copy.
 */
IntMatrix::IntMatrix(const IntMatrix &other)
{
    _rows = other._rows;
    _cols = other._cols;
    _pMatrix = new int*[_rows];
    for (int i = 0; i < _rows; ++i)
    {
        _pMatrix[i] = new int[_cols];
        for (int j = 0; j < _cols; ++j)
        {
            _pMatrix[i][j] = other._pMatrix[i][j];
        }
    }
}
/**
* Destructor
*/
IntMatrix::~IntMatrix()
{
	_deleteMatrix();
}


/**
* Operator for matrix addition.
* @param other the second matrix operand.
* @return a copy matrix of the addition.
*/
IntMatrix IntMatrix::operator+(const IntMatrix &other) const
{
	assert(_rows == other._rows);
	assert(_cols == other._cols);
    // Create the left summand object.
    IntMatrix sumMatrix;
    sumMatrix._rows = _rows;
    sumMatrix._cols = _cols;
    sumMatrix._pMatrix = new int*[_rows];
    for (int i = 0; i < _rows; ++i)
    {
        sumMatrix._pMatrix[i] = new int[_cols];
        for (int j = 0; j < _cols; ++j)
        {
            sumMatrix._pMatrix[i][j] = _pMatrix[i][j] + other._pMatrix[i][j];
        }
    }
    return sumMatrix;
}
/**
 * Operator for matrix addition.
 * @param other the second matrix operand.
 * @return a reference to the sum matrix. We change the object!
 */
IntMatrix& IntMatrix::operator+=(const IntMatrix &other)
{
    *this = *this + other;
    return *this;
}
/**
* Operator for matrix substraction.
* @param other the second matrix operand.
* @return a copy of the difference matrix.
*/
IntMatrix IntMatrix::operator-(const IntMatrix &other) const
{
	assert(_rows == other._rows);
	assert(_cols == other._cols);
    IntMatrix minusMatrix;
    minusMatrix._rows = _rows;
    minusMatrix._cols = _cols;
    minusMatrix._pMatrix = new int*[_rows];
    for (int i = 0; i < _rows; ++i)
    {
        minusMatrix._pMatrix[i] = new int[_cols];
        for (int j = 0; j < _cols; ++j)
        {
            minusMatrix._pMatrix[i][j] = _pMatrix[i][j] - other._pMatrix[i][j];
        }
    }
    return minusMatrix;
}

/**
 * Operator for matrix substraction.
 * @param other the second matrix operand.
 * @return a reference to the difference matrix. We change the object!
 */
IntMatrix& IntMatrix::operator-=(const IntMatrix &other)
{
    *this = *this - other;
    return *this;
}

/**
 * Operator for matrix multiplication.
 * @param other the second matrix operand.
 * @return a copy of the mult matrix.
 */
IntMatrix IntMatrix::operator*(const IntMatrix &other) const
{
	assert(_cols == other._rows);
    IntMatrix multiplicationMatrix;
    multiplicationMatrix._rows = _rows;
    multiplicationMatrix._cols = other._cols;
    multiplicationMatrix._pMatrix = new int*[multiplicationMatrix._rows];
    for (int i = 0; i < multiplicationMatrix._rows; ++i)
    {
        multiplicationMatrix._pMatrix[i] = new int[multiplicationMatrix._cols];
        for (int j = 0; j < multiplicationMatrix._cols; ++j)
        {
        	// Multiply the first matrix row by the second matrix column.
        	multiplicationMatrix._pMatrix[i][j] = 0;
            for (int k = 0; k < _cols; ++k)
            {
                multiplicationMatrix._pMatrix[i][j] += _pMatrix[i][k] * other._pMatrix[k][j];
            }
        }

    }
    return multiplicationMatrix;
}

/**
* Operator for matrix multiplication.
* @param other the second matrix operand.
* @return a reference to the mult matrix. We change the object!
*/
IntMatrix& IntMatrix::operator*=(const IntMatrix &other)
{
    *this = *this * other;
    return *this;
}

/**
* Operator for matrix assignment.
* @param other the second matrix operand.
* @return the assigned matrix. We change the object!
*/
IntMatrix& IntMatrix::operator=(const IntMatrix &other)
{
    // We try to copy the same object, we don't want to lose the pointer.
    if (this == &other)
    {
        return *this;
    }
    // Delete the old matrix.
    _deleteMatrix();
    _rows = other._rows;
    _cols = other._cols;
    _pMatrix = new int*[_rows];
    for (int i = 0; i < _rows; ++i)
    {
        _pMatrix[i] = new int[_cols];
        for (int j = 0; j < _cols; ++j)
        {
            _pMatrix[i][j] = other._pMatrix[i][j];
        }
    }
    return *this;
}
/**
* Matrix transpose.
* @return a copy of the transposed matrix.
*/
IntMatrix IntMatrix::trans() const
{
    IntMatrix transMatrix;
    transMatrix._rows = _cols;
    transMatrix._cols = _rows;

    transMatrix._pMatrix = new int*[transMatrix._rows];
    for (int i = 0; i < transMatrix._rows; ++i)
    {

        transMatrix._pMatrix[i] = new int[transMatrix._cols];
        for (int j = 0; j < transMatrix._cols; ++j)
        {
        	// Substitute between cols and rows.
            transMatrix._pMatrix[i][j] = _pMatrix[j][i];
        }
    }
    return transMatrix;
}
/**
* Prints the matrix.
* @param out - the object to write to.
* @param matrix - the matrix to print.
* @return reference to the printing object.
*/
ostream& operator<<(ostream& out, const IntMatrix &matrix)
{
    int j;
    for (int i = 0; i < matrix._rows; i++)
    {
        for (j = 0; j < matrix._cols - 1; j++)
        {
            out << matrix._pMatrix[i][j] << SPACE;
        }
        out << matrix._pMatrix[i][j] << endl;
    }
    return out;
}
/**
* calculates the trace of the matrix.
* @return the trace of the matrix.
*/
int IntMatrix::trace() const
{
	assert(_rows == _cols);
    int mTrace = 0;
    for (int i = 0; i < _rows; i++)
    {
        mTrace += _pMatrix[i][i];
    }
    return mTrace;
}
/**
* @return the matrix values.
*/
int** IntMatrix::getMatrix() const
{
    return _pMatrix;
}
/**
* @return the rows of the matrix.
*/
int IntMatrix::getRows() const
{
    return _rows;
}
/**
* @return the cols of the matrix.
*/
int IntMatrix::getCols() const
{
    return _cols;
}

void IntMatrix::_deleteMatrix()
{
	for (int i = 0; i < _rows; ++i)
	{
		delete[] _pMatrix[i];
	}
	if (_pMatrix != nullptr)
	{
		delete[] _pMatrix;
	}
}


