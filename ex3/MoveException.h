/*
 * MoveException.h
 *
 *  Created on: Sep 10, 2015
 *      Author: orib
 */

#ifndef MOVEEXCEPTION_H_
#define MOVEEXCEPTION_H_


#include <exception>

/**
 * Exception for error in moving the matrix (move ctr).
 */
class MoveException: public std::exception
{
public:

	/**
	 * overload of exception's what.
	 */
    virtual const char* what() const noexcept
    {
        return "Could not move matrix.";
    }

};

#endif /* MOVEEXCEPTION_H_ */
