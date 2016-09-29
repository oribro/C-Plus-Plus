//
// Created by OriB on 06/09/2015.
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Complex.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "TraceException.h"
#include "AdditionException.h"
#include "MultiplicationException.h"
#include "SubtractionException.h"
#include "MatrixAllocException.h"
#include "MoveException.h"
#include "MatrixAssignmentException.h"


#define MULT "MULT"
#define SUM "SUM"
#define TAB "\t"

/**
 *  A generic matrix class.
 *  This class represents a matrix with a type that supports ‫‪ ‬‬ operations:
 *   ‫‪==,= ,* ,+= ,­-= ,­ -, << and the zero constructor.‬‬
 */
template <class T>
class Matrix
{
public:
	// The const iterator for the matrix is a const iterator for vector.
    typedef typename std::vector<T>::const_iterator VectorConstIterator;
    // A vector of threads for multithreading.
    typedef std::vector<std::thread> Threads;
    // Iterator for the threads vector.
    typedef typename std::vector<std::thread>::iterator ThreadsIterator;
/**
* Default constructor.
* Initiate a matrix of dimension 0 as null matrix.
* This constructor is used to construct a matrix object with no values.
* @return a copy of the constructed matrix.
*/
    // -------------------------------- Declarations -------------------------
    /**
     * Default constructor.
     * Initializes the matrix as 1x1 matrix with zero value.
     */
    Matrix();

    /**
     * Sets the corresponding static data member value to the value indicated
     * by indicator.
     * @param indicator - true for using parallel mode, false for using sequential mode.
     */
    static void setParallel(bool indicator);

    /**
     * Constructor that receives the matrix dimensions and initializes a matrix with
     * zero values.
     * @rows - the rows of the matrix.
     * @cols - the cols of the matrix.
     */
    Matrix(unsigned int rows, unsigned int cols);

    /**
     * Copy constructor.
     * @param other - the other matrix to copy.
     */
    Matrix(const Matrix<T>& other);

    /**
     * Move constructor.
     * @param other - the other matrix to move.
     */
    Matrix(Matrix<T> && other);

    /**
     * Constructor that initializes the matrix according to the const iterator of the class.
     * @param rows - the rows of the matrix.
     * @param cols - the cols of the matrix.
     * @param cells - the cells of the matrix to initialize to.
     */
    Matrix(unsigned int rows, unsigned int cols, const std::vector<T>& cells);

    /**
     * Destructor.
     */
    ~Matrix();

    /**
    * Operator for matrix assignment.
    * @param other the second matrix operand.
    * @return the assigned matrix. We change the object!
    * @throws invalid_argument if a dimension is 0.
    */
    Matrix<T>& operator=(const Matrix<T>& other);

    /**
    * Operator for matrix addition.
    * @param other the second matrix operand.
    * @return a copy matrix of the addition.
    * @throws invalid_argument if a dimension is 0.
    */
    const Matrix<T> operator+(const Matrix<T>& other) const;

    /**
    * Operator for matrix substraction.
    * @param other the second matrix operand.
    * @return a copy of the difference matrix.
    * @throws invalid_argument if a dimension is 0.
    */
    const Matrix<T> operator-(const Matrix<T>& other) const;


    /**
     * Operator for matrix multiplication.
     * @param other the second matrix operand.
     * @return a copy of the mult matrix.
     * @throws invalid_argument if a dimension is 0.
     */
    const Matrix<T> operator*(const Matrix<T>& other) const;

    /**
     * Operator for comparing matrices.
     * @param other - the matrix to compare.
     * @return true if the matrices are equal and false otherwise.
     */
    bool operator==(const Matrix<T>& other) const;

    /**
     * Operator for comparing matrices.
     * @param other - the matrix to compare.
     * @return true if the matrices are different and false otherwise.
     */
    bool operator!=(const Matrix<T>& other) const;

    /**
     * Returns the transpose of the given matrix.
     * @return the matrix transpose.
     * @throws invalid_argument if a dimension is 0.
     */
    const Matrix<T> trans() const;

    /**
     * Returns the trace of the matrix.
     * @return the trace.
     * @throws invalid_argument if a dimension is 0.
     */
    const T trace() const;

    /**
     * Const operator for indexing the matrix.
     * @param row - the row to look for the value.
     * @param col - the col to look for the value.
     * @return The value at the given row and col, as const value
     * (read only).
     */
    const T& operator()(unsigned int row, unsigned int col) const;

    /**
	* Operator for indexing the matrix.
	* @param row - the row to look for the value.
	* @param col - the col to look for the value.
	* @return The value at the given row and col, as const value
	*/
    T& operator()(unsigned int row, unsigned int col);

    /**
	 * Prints the matrix.
	 * @param out - the object to write to.
	 * @param matrix - the matrix to print.
	 * @return reference to the printing object.
	 */
    template <typename K>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<K>& matrix);

    /**
     * @return the size of the rows of the matrix.
     */
    unsigned int rows() const;

    /**
     * @return the size of the columns of the matrix.
     */
    unsigned int cols() const;

    /**
     * @return true if the matrix is square, false otherwise.
     */
    bool isSquareMatrix() const;

    /**
     * This class represents a const iterator for the matrix.
     * The iterator iterates the matrix for read only purposes.
     */
    class const_iterator
    {
    public:
        /**
         * Constructor for the iterator.
         * @param it - the iterator of the matrix, sets by defult to be defaultly
         * constructed by vector constructor.
         */
        const_iterator(VectorConstIterator it = VectorConstIterator()) : _it(it)
        {
        }

        /**
         * Copy constructor.
         * @param other - the other iterator to copy.
         */
        const_iterator(const const_iterator& other)
        {
            _it = other._it;
        }

        /**
         * Assignment operator.
         * @param other the other iterator to assign.
         */
        const_iterator& operator=(const const_iterator& other)
        {
            _it = other._it;
            return *this;
        }

        /**
         * Dereference operator.
         * @return reference to the value the iterator points to.
         */
        const T& operator*()
        {
            return *_it;
        }
        /**
         * @returns the iterator.
         */
        T* operator->()
        {
            return _it;
        }
        /**
         *@return returns the incremented operator.
         */
        const_iterator& operator++()
        {
            ++_it;
            return *this;
        }
        /**
         * @return the operator before increment.
         */
        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            _it++;
            return tmp;
        }
        /**
         * @return reference to the operator after decrement.
         */
        const_iterator& operator--()
        {
            --_it;
            return *this;
        }
        /**
         * @return reference to the operator before decrement.
         */
        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            _it--;
            return tmp;
        }
        /**
         * @param other iterator to compare.
         * @return true if the operators are equal, false otherwise.
         */
        bool operator==(const_iterator const& other) const
        {
            return _it == other._it;
        }
        /**
         * @param other iterator to compare.
		 * @return false if the operators are equal, true otherwise.
		 */
        bool operator!=(const_iterator const& other) const
        {
            return _it != other._it;
        }
    private:
        // The iterator for the matrix.
        VectorConstIterator _it;
    };

    /**
     * @return iterator to the beginning of the matrix.
     */
    const_iterator begin() const
    {
        return const_iterator(_pMatrix.begin());
    }
    /**
     * @return iterator to the end of the matrix.
     */
    const_iterator end() const
    {
        return const_iterator(_pMatrix.end());
    }

private:
    unsigned int _rows;  // The number of rows in the matrix.
    unsigned int _cols;  // The number of columns in the matrix.
    std::vector<T> _pMatrix;   // Vector containing the matrix values.

    // Static variable to indicate the mode we use - parallel or sequential.
    static bool s_useParallel;

    /**
     * This is how we index the matrix. Every row is defined as a sequence of
     * values in the vector.
     * @param row - the row for the value.
     * @param col - the column for the value.
     * @return the position in the matrix which the value is found at.
     */
    inline unsigned int _matrixIndex(unsigned int row, unsigned int col) const
    {
        return (row * _cols) + col;
    }

    /**
     * Method for multiplying creating a line using multiplication in the parallel mode.
     * @param lineNumber - the line in the result matrix we currently compute.
     * @param multMatrix - the result matrix to be created.
     * @param firstM - the first matrix to multiply.
     * @param secondM - the second matrix to multiply.
     */
    static void _multLine(int lineNumber, Matrix<T>& multMatrix, const Matrix<T>& firstM,
                          const Matrix<T>& secondM);

    /**
     * Method for summing creating a line using summation in the parallel mode.
     * @param lineNumber - the line in the result matrix we currently compute.
     * @param multMatrix - the result matrix to be created.
     * @param firstM - the first matrix to multiply.
     * @param secondM - the second matrix to multiply.
     */
    static void _sumLine(int lineNumber, Matrix<T>& sumMatrix, const Matrix<T>& firstM,
                         const Matrix<T>& secondM);

    /**
     * Performs a parallel operation.
     * @param operation- an indicator to tell us which operation to perform (mult or sum).
     * @param resultMatrix - the result matrix to be created.
     * @param other - the other matrix to perform the action on.
     */
    void _parallelOperation(const std::string& operation, Matrix<T>& resultMatrix,
                            const Matrix<T>& other) const;
};

// ---------------------------------------- Implementations ------------------------------

/**
  * Sets the corresponding static data member value to the value indicated
  * by indicator.
  * @param indicator - true for using parallel mode, false for using sequential mode.
  */
template <class T>
bool Matrix<T>::s_useParallel = false;

template <class T>
inline void Matrix<T>::setParallel(bool indicator)
{
	// Print only if the indicator changes the state of the program.
    if (indicator != s_useParallel)
    {
        s_useParallel = indicator;
        if (indicator == true)
        {
            std::cout << "Generic Matrix mode changed to parallel mode" << std::endl;
        }
        else
        {
            std::cout << "Generic Matrix mode changed to non-parallel mode" << std::endl;
        }
    }
}

/**
* Default constructor.
* Initializes the matrix as 1x1 matrix with zero value.
* @throws MatrixAllocException if the memory could not be allocated.
*/
template <class T>
inline Matrix<T>::Matrix() : _rows(1), _cols(1)
{
	try
	{
		// The zero value of the type is the default constructed type.
		_pMatrix.push_back(T());
	}
	catch(std::bad_alloc& e)
	{
		throw MatrixAllocException();
	}
}

/**
* Constructor that receives the matrix dimensions and initializes a matrix with
* zero values.
* @rows - the rows of the matrix.
* @cols - the cols of the matrix.
* @throws MatrixAllocException if the memory could not be allocated.
*/
template <class T>
inline Matrix<T>::Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols)
{
	try
	{
    // Initialize the matrix with zero values.
		for (unsigned int i = 0; i < rows * cols; i++)
		{
			_pMatrix.push_back(T());
		}
	}
	catch(std::bad_alloc& e)
	{
		throw MatrixAllocException();
	}
}

/**
 * Copy constructor.
 * @param other - the other matrix to copy.
 */
template <typename T>
inline Matrix<T>::Matrix(const Matrix<T>& other) : _rows(other._rows), _cols(other._cols),
_pMatrix(other._pMatrix)
{
}

/**
* Move constructor.
* @param other - the other matrix to move.
* @throws MoveException if the matrix could not be moved.
*/
template <typename T>
inline Matrix<T>::Matrix(Matrix<T> && other) : _rows(other._rows), _cols(other._cols)
{
	try
	{
		_pMatrix = std::move(other._pMatrix);
	}
	catch(...)
	{
		throw MoveException();
	}
}

/**
* Constructor that initializes the matrix according to the const iterator of the class.
* @param rows - the rows of the matrix.
* @param cols - the cols of the matrix.
* @param cells - the cells of the matrix to initialize to.
* @throws MatrixAllocException if the memory could not be allocated.
*/
template <class T>
inline Matrix<T>::Matrix(unsigned int rows, unsigned int cols,
						 const std::vector<T>& cells) : _rows(rows), _cols(cols)
{
	try
	{
		for (VectorConstIterator it = cells.begin(); it != cells.end(); ++it)
		{
			_pMatrix.push_back(*it);
		}
	}
    catch(std::bad_alloc& e)
	{
		throw MatrixAllocException();
	}
}

/**
 * Destructor.
 */
template <class T>
inline Matrix<T>::~Matrix()
{
}

 /**
  * Const operator for indexing the matrix.
  * @param row - the row to look for the value.
  * @param col - the col to look for the value.
  * @return The value at the given row and col, as const value
  * (read only).
  */
template <typename T>
inline const T& Matrix<T>::operator()(unsigned int row, unsigned int col) const
{
	return _pMatrix.at(_matrixIndex(row, col));
}

/**
* Operator for indexing the matrix.
* @param row - the row to look for the value.
* @param col - the col to look for the value.
* @return The value at the given row and col, as const value
*/
template <typename T>
inline T& Matrix<T>::operator()(unsigned int row, unsigned int col)
{
	return _pMatrix[_matrixIndex(row, col)];
}

/**
* Operator for matrix addition.
* @param other the second matrix operand.
* @return a copy matrix of the addition.
* @throws AdditionException if the dimensions are different.
*/
template <typename T>
inline const Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	if ((other._rows != other._cols) && (other._rows == 0 || other._cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}

	if(!((_rows == other._rows) && (_cols == other._cols)))
	{
		throw AdditionException("cannot addition matrices of different sizes.");
	}
	Matrix<T> sumMatrix = Matrix<T>(other._rows, other._cols);
	// use regular programming (serialized)
	if (!s_useParallel)
	{
		// Create the left summand object.
		for (unsigned int i = 0; i < sumMatrix._rows; ++i)
		{
			for (unsigned int j = 0; j < sumMatrix._cols; ++j)
			{
				sumMatrix(i, j) = (*this)(i, j) + other(i, j);
			}
		}
	}
		// Use multithreading (parallel).
	else
	{
		_parallelOperation(SUM, sumMatrix, other);
	}
	return sumMatrix;
}

/**
* Operator for matrix substraction.
* @param other the second matrix operand.
* @return a copy of the difference matrix.
* @throws SubtractionException if the dimensions are different.
*/
template <typename T>
inline const Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	if ((other._rows != other._cols) && (other._rows == 0 || other._cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}

	if(!((_rows == other._rows) && (_cols == other._cols)))
	{
		throw SubtractionException("Cannot subtract matrices of different sizes.");
	}
	// The result matrix.
	Matrix<T> minusMatrix = Matrix<T>(_rows, _cols);
	for (unsigned int i = 0; i < minusMatrix._rows; ++i)
	{
		for (unsigned int j = 0; j < minusMatrix._cols; ++j)
		{
			minusMatrix(i, j) = (*this)(i, j) - other(i, j);
		}
	}
	return minusMatrix;
}


/**
* Operator for matrix multiplication.
* @param other the second matrix operand.
* @return a copy of the mult matrix.
* @throws MultiplicationException if the dimensions are different.
*/
template <typename T>
inline const Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	if ((other._rows != other._cols) && (other._rows == 0 || other._cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}

	if(_cols != other._rows)
	{
		throw MultiplicationException("Cannot multiply matrices of different sizes.");
	}
	Matrix<T> multMatrix = Matrix<T>(_rows, other._cols);
	if (!s_useParallel)
	{
		for (unsigned int i = 0; i < multMatrix._rows; ++i)
		{
			for (unsigned int j = 0; j < multMatrix._cols; ++j)
			{
				// Multiply the first matrix row by the second matrix column.
				multMatrix(i, j) = T();
				for (unsigned int k = 0; k < _cols; ++k)
				{
					multMatrix(i, j) += ((*this)(i, k)) * (other(k, j));
				}
			}

		}
	}
	else
	{
		_parallelOperation(MULT, multMatrix, other);
	}
	return multMatrix;
}


/**
* Operator for matrix assignment.
* @param other the second matrix operand.
* @return the assigned matrix. We change the object!
* @throws AssignmentException if could not assign matrix.
*/
template <typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	if ((other._rows != other._cols) && (other._rows == 0 || other._cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	// We try to copy the same object, we don't want to lose the pointer.
	if (this == &other)
	{
		return *this;
	}
	try
	{
		_rows = other._rows;
		_cols = other._cols;
		_pMatrix = other._pMatrix;
	}
	catch(...)
	{
		throw MatrixAssignmentException("Could not assign matrix.");
	}
	return *this;
}

/**
  * Operator for comparing matrices.
  * @param other - the matrix to compare.
  * @return true if the matrices are equal and false otherwise.
  */
template <typename T>
inline bool Matrix<T>::operator==(const Matrix<T>& other) const
{
	// The matrices are from different dimensions and cant be equal.
	if(!((_rows == other._rows) && (_cols == other._cols)))
	{
		return false;
	}

	return _pMatrix == other._pMatrix;
}

/**
 * Operator for comparing matrices.
 * @param other - the matrix to compare.
 * @return true if the matrices are different and false otherwise.
 */
template <typename T>
inline bool Matrix<T>::operator!=(const Matrix<T>& other) const
{
	return !(*this == other);
}

/**
* Matrix transpose.
* @return a copy of the transposed matrix.
*/
template <typename T>
inline const Matrix<T> Matrix<T>::trans() const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	Matrix<T> transMatrix;
	transMatrix._rows = _cols;
	transMatrix._cols = _rows;
	transMatrix._pMatrix.resize(transMatrix._rows * transMatrix._cols);
	for (unsigned int i = 0; i < transMatrix._rows; ++i)
	{
		for (unsigned int j = 0; j < transMatrix._cols; ++j)
		{
			// Substitute between cols and rows.
			transMatrix(i, j) = (*this)(j, i);
		}
	}

	return transMatrix;
}

/**
 * Specialization method for matrix complex transpose.
 * @return a copy of the transposed matrix.
*/
template <>
inline const Matrix<Complex> Matrix<Complex>::trans() const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	Matrix<Complex> conjugateM;
	conjugateM._rows = _cols;
	conjugateM._cols = _rows;
	conjugateM._pMatrix.resize(conjugateM._rows * conjugateM._cols);
	for (unsigned int i = 0; i < conjugateM._rows; ++i)
	{
		for (unsigned int j = 0; j < conjugateM._cols; ++j)
		{
			// Change the values to their conjugates.
			conjugateM(i, j) = ((*this)(j, i)).conj();
		}
	}
	return conjugateM;
}
/**
* Prints the matrix.
* @param out - the object to write to.
* @param matrix - the matrix to print.
* @return reference to the printing object.
*/
template <typename K>
inline std::ostream& operator<<(std::ostream& out, const Matrix<K>& matrix)
{
	unsigned int j;
	for (unsigned int i = 0; i < matrix._rows; i++)
	{
		for (j = 0; j < matrix._cols; j++)
		{
			out << matrix(i, j) << TAB;
		}
		out << std::endl;
	}
	return out;
}
/**
* calculates the trace of the matrix.
* @return the trace of the matrix.
* @throws TraceException if the matrix isn't square.
*/
template <typename T>
inline const T Matrix<T>::trace() const
{
	if ((_rows != _cols) && (_rows == 0 || _cols == 0))
	{
		throw std::invalid_argument("Matrix with dimension 0 is illegal.");
	}
	if(_rows != _cols)
	{
		throw TraceException("Matrix isn't square");
	}
	T mTrace = T();
	for (unsigned int i = 0; i < _rows; i++)
	{
		mTrace += (*this)(i, i);
	}
	return mTrace;
}

/**
* @return the rows of the matrix.
*/
template <typename T>
inline unsigned int Matrix<T>::rows() const
{
	return _rows;
}
/**
* @return the cols of the matrix.
*/
template <typename T>
unsigned int Matrix<T>::cols() const
{
	return _cols;
}

/**
* @return true if the matrix is square, false otherwise.
*/
template <typename T>
inline bool Matrix<T>::isSquareMatrix() const
{
	return (_rows == _cols);
}

/**
* Performs a parallel operation.
* @param operation- an indicator to tell us which operation to perform (mult or sum).
* @param resultMatrix - the result matrix to be created.
* @param other - the other matrix to perform the action on.
*/
template <typename T>
inline void Matrix<T>::_parallelOperation(const std::string& operation, Matrix<T>& resultMatrix,
										  const Matrix<T>& other) const
{
	// The threads for the matrix lines.
	Threads matrixRowsThreads(_rows);
	// Create threads for the matrix rows.
	if (operation.compare(SUM) == 0)
	{
		for (unsigned int i = 0; i < resultMatrix._rows; ++i)
		{
			matrixRowsThreads[i] = std::thread(&Matrix<T>::_sumLine, i,
													std::ref(resultMatrix),
													std::ref(*this), std::ref(other));
		}
	}
	else if (operation.compare(MULT) == 0)
	{
		for (unsigned int i = 0; i < resultMatrix._rows; ++i)
		{
			matrixRowsThreads[i] = std::thread(&Matrix<T>::_multLine, i,
													std::ref(resultMatrix), std::ref(*this),
													std::ref(other));
		}
	}

	// Wait for the threads to calculate the matrix lines.
	for (ThreadsIterator it = matrixRowsThreads.begin(); it != matrixRowsThreads.end(); ++it)
	{
		(*it).join();
	}
}

/**
* Method for multiplying creating a line using multiplication in the parallel mode.
* @param lineNumber - the line in the result matrix we currently compute.
* @param multMatrix - the result matrix to be created.
* @param firstM - the first matrix to multiply.
* @param secondM - the second matrix to multiply.
*/
std::mutex m;
template <typename T>
inline void Matrix<T>::_multLine(int lineNumber, Matrix<T>& multMatrix, const Matrix<T>& firstM,
								 const Matrix<T>& secondM)
{
	for (unsigned int j = 0; j < multMatrix._cols; ++j)
	{
		// Multiply the first matrix row by the second matrix column.
		multMatrix(lineNumber, j) = T();
		T tempCellVal = T();
		for (unsigned int k = 0; k < firstM._cols; ++k)
		{
			tempCellVal += (firstM(lineNumber, k)) * (secondM(k, j));
		}
		m.lock();
		multMatrix(lineNumber, j) = tempCellVal;
		m.unlock();
	}
}

/**
* Method for summing creating a line using summation in the parallel mode.
* @param lineNumber - the line in the result matrix we currently compute.
* @param multMatrix - the result matrix to be created.
* @param firstM - the first matrix to multiply.
* @param secondM - the second matrix to multiply.
*/
template <typename T>
inline void Matrix<T>::_sumLine(int lineNumber, Matrix<T>& sumMatrix, const Matrix<T>& firstM,
								const Matrix<T>& secondM)
{
	std::lock_guard<std::mutex> lk(m);
	for (unsigned int j = 0; j < sumMatrix._cols; ++j)
	{
		sumMatrix(lineNumber, j) = (firstM(lineNumber, j)) + (secondM(lineNumber, j));
	}
}






#endif //MATRIX_HPP
