/*
 * MultiplicationException.h
 *
 *  Created on: Sep 10, 2015
 *      Author: orib
 */

#ifndef MULTIPLICATIONEXCEPTION_H_
#define MULTIPLICATIONEXCEPTION_H_


#include <stdexcept>

/**
 * Exception for wrong dimensions in multiplication.
 */
class MultiplicationException: public std::invalid_argument
{
public:
	/**
	 * Constructor
	 * @param msg - the message to throw.
	 */
    MultiplicationException(std::string const& msg) : std::invalid_argument(msg)
    {
    }
    /**
	* overload of exception's what.
	*/
    virtual const char* what() const noexcept
    {
        return "Cannot multiply matrices of different sizes.";
    }

};

#endif /* MULTIPLICATIONEXCEPTION_H_ */
