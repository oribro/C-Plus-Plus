//
// Created by OriB on 07/09/2015.
//

#ifndef TRACEEXCEPTION_H
#define TRACEEXCEPTION_H

#include <stdexcept>

/**
 * Exception for wrong dimensions in trace.
 */
class TraceException: public std::invalid_argument
{
public:
	/**
	 * Constructor
	 * @param msg - the message to throw.
	 */
    TraceException(std::string const& msg) : std::invalid_argument(msg)
    {
    }
    /**
	* overload of exception's what.
	*/
    virtual const char* what() const noexcept
    {
        return "Matrix isn't square";
    }
};
#endif //TRACEEXCEPTION_H
