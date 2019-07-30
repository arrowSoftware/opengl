////////////////////////////////////////////////////////////////////////////////
// File:
//
// Description:
//
// Methods:
//
// Fields:
//
// Modification History:
//    Date:        Who:            What:
//  07/25/2019  Tyler Gajewski    Initial Creation
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATION_EXCEPTION_HPP_
#define _APPLICATION_EXCEPTION_HPP_

// STL Includes.
#include <exception>
#include <string>

// This class is derived from std::runtime_error instead of std::exception so
// that an error msg can be passed to the constructor.
class ApplicationException : public std::runtime_error
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  ApplicationException.
        // Description:
        //  The constructor provides a method to pass a string into the
        //  exception so that a unique message can be displayed when an error
        //  occurs.
        // Parameters:
        //
        // Returns:
        //
        ////////////////////////////////////////////////////////////////////////
        ApplicationException(std::string const &argError) :
            std::runtime_error(argError)
        {};
};

#endif // _APPLICATION_EXCEPTION_HPP_
