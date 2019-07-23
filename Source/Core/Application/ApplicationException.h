#ifndef _APPLICATION_EXCEPTION_H_
#define _APPLICATION_EXCEPTION_H_

#include <exception>
#include <string>

class ApplicationException : public std::runtime_error
{
    public:
        ApplicationException(std::string const &argError) :
            std::runtime_error(argError)
        {};
};

#endif // _APPLICATION_EXCEPTION_H_
