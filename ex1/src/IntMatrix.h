//
// Created by OriB on 23/08/2015.
//

#ifndef INTMATRIX_H
#define INTMATRIX_H

// IntMatrix.h

#include <iostream>
using namespace std;

// ---------------------- Macros -------------
#define SPACE " "


/**
 *  This class represents a matrix with int values and operations on matrices.
 *  The matrix itself is an array of arrays, and in each cell (the rows) we store
 *   an array (the columns).
 */

class IntMatrix
{
public:
    /**
     * Default constructor.
     * Initiate a matrix of dimension 0 as null matrix.
     * This constructor is used to construct a matrix object with no values.
     */
    IntMatrix();

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
    IntMatrix(int numOfRows, int numOfCols, int **matrix);

    /**
     * Copy constructor.
     * @param other - the object to copy.
     */
    IntMatrix(const IntMatrix &other);

    /**
     * Destructor
     */
    ~IntMatrix();

    /**
     * Operator for matrix assignment.
     * @param other the second matrix operand.
     * @return the assigned matrix. We change the object!
     */
    IntMatrix& operator=(const IntMatrix &other);
    /**
     * Operator for matrix addition.
     * @param other the second matrix operand.
     * @return a copy matrix of the addition.
     */
    IntMatrix operator+(const IntMatrix &other) const;

    /**
     * Operator for matrix addition.
     * @param other the second matrix operand.
     * @return a reference to the sum matrix. We change the object!
     */
    IntMatrix& operator+=(const IntMatrix &other);
    /**
     * Operator for matrix substraction.
     * @param other the second matrix operand.
     * @return a copy of the difference matrix.
     */
    IntMatrix operator-(const IntMatrix &other) const;
    /**
     * Operator for matrix substraction.
     * @param other the second matrix operand.
     * @return a reference to the difference matrix. We change the object!
     */
    IntMatrix& operator-=(const IntMatrix &other);
    /**
     * Operator for matrix multiplication.
     * @param other the second matrix operand.
     * @return a copy of the mult matrix.
     */
    IntMatrix operator*(const IntMatrix &other) const;
    /**
     * Operator for matrix multiplication.
     * @param other the second matrix operand.
     * @return a reference to the mult matrix. We change the object!
     */
    IntMatrix& operator*=(const IntMatrix &other);

    /**
     * Matrix transpose.
     * @return a copy of the transposed matrix.
     */
    IntMatrix trans() const;

    /**
     * Prints the matrix.
     * @param out - the object to write to.
     * @param matrix - the matrix to print.
     * @return reference to the printing object.
     */
    friend ostream& operator<<(ostream& out, const IntMatrix &matrix);

    /**
	* calculates the trace of the matrix.
	* @return the trace of the matrix.
	*/
    int trace() const;

    // ------------------------ Getters -------------------------

    /**
     * @return the matrix values.
     */
    int** getMatrix() const;

    /**
     * @return the rows of the matrix.
     */
    int getRows() const;

    /**
     * @return the cols of the matrix.
     */
    int getCols() const;



private:
    int **_pMatrix;   // Pointer to the matrix values.
    int _rows;  // The number of rows in the matrix.
    int _cols;  // The number of columns in the matrix.

    void _deleteMatrix();
};


#endif //INTMATRIX_H
