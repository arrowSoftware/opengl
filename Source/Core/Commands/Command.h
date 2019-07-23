#ifndef _COMMAND_H_
#define _COMMAND_H_

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
        //  Execute.
        // Description:
        //  Pure virtual function executes the command.
        // Parameters:
        //  None.
        // Returns:
        //  None.
        ////////////////////////////////////////////////////////////////////////
        virtual void Execute(void) = 0;
};

#endif // _COMMAND_H_
