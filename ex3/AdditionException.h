/*
 * AdditionException.h
 *
 *  Created on: Sep 9, 2015
 *      Author: orib
 */

#ifndef ADDITIONEXCEPTION_H_
#define ADDITIONEXCEPTION_H_

#include <stdexcept>

/**
 * Exception for wrong dimensions in addition.
 */
class AdditionException: public std::invalid_argument
{
public:
	/**
	 * Constructor
	 * @param msg - the message to throw.
	 */
    AdditionException(std::string const& msg) : std::invalid_argument(msg)
    {
    }
    /**
     * overload of exception's what.
     */
    virtual const char* what() const noexcept
    {
        return "cannot addition matrices of different sizes.";
    }

};
#endif /* ADDITIONEXCEPTION_H_ */
