//
// Created by OriB on 25/08/2015.
//

// ------------------------ Includes --------------
#include <iostream>
#include <string>
#include <sstream>
#include "IntMatrix.h"

// ---------------------- Macros ---------------------

#define INDEX_ADD 1
#define INDEX_SUB 2
#define INDEX_MUL 3
#define INDEX_TRANS 4
#define INDEX_TRACE 5
#define STRING_ADD "add"
#define STRING_SUB "sub"
#define STRING_MUL "mul"
#define STRING_TRANS "trans"
#define STRING_TRACE "trace"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define ZERO_MATRIX 0
#define COMMA ','
#define DOT "."
#define BINARY_NUM_OF_MATRICES 3
#define UNARY_NUM_OF_MATRICES 2
#define BINARY_RESULT_MATRIX 2
#define UNARY_RESULT_MATRIX 1
#define FIRST_MATRIX 0
#define SECOND_MATRIX 1

using namespace std;

/**
 * This program is the driver of the matrix program. It asks for input from the user
 * and performs an operation on matrices according to that input.
 */


// ------------------------------- Implementation ---------

/**
 * Asks for matrice dimension and values from the user and create a matrix object
 * out of them.
 * @return a pointer to the matrix object that was created on the heap.
 */
static IntMatrix* createMatrix()
{
    int numOfRows;
    int numOfCols;
    cout << "number of rows:";
    cin >> numOfRows;
    cout << "number of columns:";
    cin >> numOfCols;
    cout << "Now insert the values of the matrix, row by row." << endl;
    cout << "After each cell add the char ',' (including after the last cell of a row)."
    << endl;
    cout << "Each row should be in a separate line." << endl;
    int **matrix = new int*[numOfRows];
    string line;
    for (int i = 0; i < numOfRows; i++)
    {
        cin >> line;
        // Object to help in splitting the line by commas.
        istringstream splitter(line);
        matrix[i] = new int[numOfCols];
        for (int j = 0; j < numOfCols; j++)
        {
        	// Split the line by commas and parse the resulted strings into integers.
        	// We assume the input is in the right format.
            string number;
            getline(splitter, number, COMMA);
            istringstream converter(number);
            converter >> matrix[i][j];
        }
    }
    // Create the new matrix object on the heap.
    IntMatrix *newMatrix = new IntMatrix(numOfRows, numOfCols, matrix);
    return newMatrix;
}

/**
 * Helper method to print the matrices.
 * @param matrix - the matrix to print.
 */
static void matrixPrinterHelper(IntMatrix& matrix)
{
    cout << endl;
    cout << matrix;
    cout << endl;
    // Special case of 0x0 matrix.
    if (matrix.getRows() == ZERO_MATRIX && matrix.getCols() == ZERO_MATRIX)
    {
    	cout << endl;
    }
}

/**
 * Prints the matrices after the operation has been performed.
 * If the last matrice in the array points to null, that means we do not expect
 * to print the result matrix.
 * @param matrixArr - the array of matrices to print.
 * @param length - the number of matrices we would like to print.
 */
static void matrixPrinter(IntMatrix* matrixArr[], int length)
{

    cout << "--------" << endl;
    if (length == BINARY_NUM_OF_MATRICES)
    {
        cout << "Got first matrix:" << endl;
        matrixPrinterHelper(*matrixArr[FIRST_MATRIX]);
        cout << "--------" << endl;
        cout << "Got second matrix:" << endl;
        matrixPrinterHelper(*matrixArr[SECOND_MATRIX]);
        // Assuming the dimensions were legal and the operation could be performed.
        if ((*matrixArr[BINARY_RESULT_MATRIX]).getMatrix() != nullptr)
        {
            cout << "==========" << endl;
            cout << "Resulted matrix:" << endl;
            matrixPrinterHelper(*matrixArr[BINARY_RESULT_MATRIX]);
        }
    }
    if (length == UNARY_NUM_OF_MATRICES)
    {
        cout << "got matrix:" << endl;
        matrixPrinterHelper(*matrixArr[FIRST_MATRIX]);
        // There exists a result matrix (we are not in trace).
        if ((*matrixArr[UNARY_RESULT_MATRIX]).getMatrix() != nullptr)
        {
            cout << "==========" << endl;
            cout << "Resulted matrix:" << endl;
            matrixPrinterHelper(*matrixArr[UNARY_RESULT_MATRIX]);
        }
    }
}

/**
 * Takes care of the cases where the dimensions are illegal by printing a matching
 * message, freeing resources and throwing an exception to the main method.
 * @param matrixArr - the array of matrices that caused the exception.
 * @param operation - the name of the operation to perform.
 */
static void handleBadDimensions(IntMatrix* matrixArr[], string operation)
{
	// Binary operation handling.
	if ((operation.compare(STRING_ADD) == 0) || (operation.compare(STRING_SUB) == 0) ||
		(operation.compare(STRING_MUL) == 0))
	{
		matrixPrinter(matrixArr, BINARY_NUM_OF_MATRICES);
		cout << "Error: " << operation << " failed - different dimensions." << endl;
		delete matrixArr[FIRST_MATRIX];
		delete matrixArr[SECOND_MATRIX];
		throw exception();
	}
	// Unary operation handling.
	else if (operation.compare(STRING_TRACE) == 0)
	{
		cout << "Error: " << operation << " failed - The matrix isn't square." << endl;
		delete matrixArr[FIRST_MATRIX];
		throw exception();
	}
}

/**
 * Perform addition/substraction/multiplication of matrices according to the
 * user input.
 * @param operation - the name of the operation to perform.
 */
static void performBinaryOperation(string operation)
{
	// Create the matrices.
    cout << "Operation " << operation << " requires 2 operand matrices." << endl;
    cout << "Insert first matrix:" << endl;
    IntMatrix* pFirstMatrix = createMatrix();
    cout << "Insert second matrix:" << endl;
    IntMatrix* pSecondMatrix = createMatrix();
    IntMatrix resultMatrix;
    IntMatrix* matrixArr[BINARY_NUM_OF_MATRICES]
                         = {pFirstMatrix, pSecondMatrix, &resultMatrix};
    // The user asked to add matrices.
    if (operation.compare(STRING_ADD) == 0)
    {
    	 // Different dimensions, error.
    	if ((((*pFirstMatrix).getRows() != (*pSecondMatrix).getRows()) ||
    		((*pFirstMatrix).getCols() != (*pSecondMatrix).getCols())))
    	{
    		handleBadDimensions(matrixArr, operation);
    	}
        resultMatrix = (*pFirstMatrix) + (*pSecondMatrix);
    }
    // The user asked to substract matrices.
    else if (operation.compare(STRING_SUB) == 0)
    {
    	 // Different dimensions, error.
    	if ((((*pFirstMatrix).getRows() != (*pSecondMatrix).getRows()) ||
    		((*pFirstMatrix).getCols() != (*pSecondMatrix).getCols())))
    	{
    		handleBadDimensions(matrixArr, operation);
    	}
        resultMatrix = (*pFirstMatrix) - (*pSecondMatrix);
    }
    // The user asked to multiply matrices.
    else if (operation.compare(STRING_MUL) == 0)
    {
    	 // Different dimensions, error.
    	if((*pFirstMatrix).getCols() != (*pSecondMatrix).getRows())
    	{
    		handleBadDimensions(matrixArr, operation);
    	}
        resultMatrix = (*pFirstMatrix) * (*pSecondMatrix);
    }
    // Print the matrices before and after the operation.
    matrixPrinter(matrixArr, BINARY_NUM_OF_MATRICES);
    delete pFirstMatrix;
    delete pSecondMatrix;
}

/**
 * Perform transpose/trace of a matrix according to the
 * user input.
 * @param operation - the name of the operation to perform.
 */
static void performUnaryOperation(string operation)
{
    cout << "Operation " << operation << " requires 1 operand matrix." << endl;
    IntMatrix* pInputMatrix = createMatrix();
    IntMatrix resultMatrix;
    if (operation.compare(STRING_TRANS) == 0)
    {
        resultMatrix = (*pInputMatrix).trans();
    }
    IntMatrix* matrixArr[UNARY_NUM_OF_MATRICES] = {pInputMatrix, &resultMatrix};
    matrixPrinter(matrixArr, UNARY_NUM_OF_MATRICES);
    if (operation.compare(STRING_TRACE) == 0)
    {
        if ((*pInputMatrix).getRows() != (*pInputMatrix).getCols())
        {
        	handleBadDimensions(matrixArr, operation);
        }
        else
        {
            cout << "The matrix is square and its trace is "
            		<< (*pInputMatrix).trace() << endl;
        }
    }
    delete pInputMatrix;
}

/**
 *	Performs an operation according to user input.
 * @param choice - the choice of the user.
 */
static void performOperation(int choice)
{
    if (choice == INDEX_ADD)
    {
        performBinaryOperation(STRING_ADD);
    }
    else if (choice == INDEX_SUB)
    {
        performBinaryOperation(STRING_SUB);
    }
    else if (choice == INDEX_MUL)
    {
        performBinaryOperation(STRING_MUL);
    }
    else if (choice == INDEX_TRANS)
    {
        performUnaryOperation(STRING_TRANS);
    }
        // Trace
    else
    {
        performUnaryOperation(STRING_TRACE);
    }
}

/**
 * The main method of the program. Asks the user for matrix operation and
 * performs it.
 */
int main()
{
    int choice = 0;
    while (choice < INDEX_ADD || choice > INDEX_TRACE)
    {
        cout << "Choose operation:" << endl;
        cout << "1. add" << endl;
        cout << "2. sub" << endl;
        cout << "3. mul" << endl;
        cout << "4. trans" << endl;
        cout << "5. trace" << endl;
        cin >> choice;
    }
    // The choice is legal
    try
    {
        performOperation(choice);
    }
    // The input for the matrices wasn't legal.
    catch(const exception&)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
