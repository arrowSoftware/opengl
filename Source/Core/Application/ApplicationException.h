#ifndef _APPLICATION_EXCEPTION_H_
#define _APPLICATION_EXCEPTION_H_

#include <exception>
#include <string>

class ApplicationException : public std::runtime_error
{
    public:
        ApplicationException(std::string const &error) :
            std::runtime_error(error)
        {};
};

#endif // _APPLICATION_EXCEPTION_H_
