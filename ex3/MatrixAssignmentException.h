/*
 * MatrixAssignmentException.h
 *
 *  Created on: Sep 10, 2015
 *      Author: orib
 */

#ifndef MATRIXASSIGNMENTEXCEPTION_H_
#define MATRIXASSIGNMENTEXCEPTION_H_

#include <stdexcept>

/**
 * Exception for bad matrix assignment (=) .
 */
class MatrixAssignmentException: public std::invalid_argument
{
public:
	/**
	 * Constructor
	 * @param msg - the message to throw.
	 */
	MatrixAssignmentException(std::string const& msg) : std::invalid_argument(msg)
    {
    }
	 /**
	 * overload of exception's what.
	 */
    virtual const char* what() const noexcept
    {
        return "Could not assign matrix.";
    }

};



#endif /* MATRIXASSIGNMENTEXCEPTION_H_ */
