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
#ifndef SOURCE_CORE_COMMANDS_COMMAND_H_
#define SOURCE_CORE_COMMANDS_COMMAND_H_

class Command
{
    public:
        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  ~Command
        // Description:
        //  Virtual destructor.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual ~Command(void);

        ////////////////////////////////////////////////////////////////////////
        // Function:
        //  execute.
        // Description:
        //  Pure virtual function executes the command.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual void execute(void) = 0;
};

#endif // SOURCE_CORE_COMMANDS_COMMAND_H_
