#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

#include <string>
#include <memory>
#include <set>

#include "command.h"

namespace pdCalc {

class UserInterface;

class CommandDispatcher
{
    class CommandDispatcherImpl;

public:
    explicit CommandDispatcher(UserInterface& ui);
    ~CommandDispatcher();

    void commandEntered(const std::string& command);

private:
    CommandDispatcher(const CommandDispatcher& ) = delete;
    CommandDispatcher(CommandDispatcher&& ) = delete;

    CommandDispatcher& operator= (const CommandDispatcher& ) = delete;
    CommandDispatcher& operator= (CommandDispatcher&& ) = delete;

    std::unique_ptr<CommandDispatcherImpl> pimpl_;
};

}


#endif // COMMANDDISPATCHER_H
