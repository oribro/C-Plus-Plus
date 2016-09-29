/*
 * MatrixAllocException.h
 *
 *  Created on: Sep 10, 2015
 *      Author: orib
 */

#ifndef MATRIXALLOCEXCEPTION_H_
#define MATRIXALLOCEXCEPTION_H_

#include <stdexcept>

/**
 * Exception for error in memory allocation for matrix.
 */
class MatrixAllocException: public std::bad_alloc
{
public:

	 /**
	 * overload of exception's what.
	 */
    virtual const char* what() const noexcept
    {
        return "Error in allocating memory for matrix.";
    }

};



#endif /* MATRIXALLOCEXCEPTION_H_ */
