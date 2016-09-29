/*
 * SubtractionException.h
 *
 *  Created on: Sep 10, 2015
 *      Author: orib
 */

#ifndef SUBTRACTIONEXCEPTION_H_
#define SUBTRACTIONEXCEPTION_H_


#include <stdexcept>

/**
 * Exception for wrong dimensions in substraction.
 */
class SubtractionException: public std::invalid_argument
{
public:
	/**
	 * Constructor
	 * @param msg - the message to throw.
	 */
    SubtractionException(std::string const& msg) : std::invalid_argument(msg)
    {
    }
    /**
	* overload of exception's what.
	*/
    virtual const char* what() const noexcept
    {
        return "Cannot subtract matrices of different sizes.";
    }

};

#endif /* SUBTRACTIONEXCEPTION_H_ */
