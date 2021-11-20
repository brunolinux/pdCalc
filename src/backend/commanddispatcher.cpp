#include "commanddispatcher.h"
#include "commandrepository.h"
#include "commandmanager.h"
#include "corecommand.h"
#include "utilities/exception.h"
#include "utilities/userinterface.h"

#include <sstream>
#include <regex>
#include <cassert>
#include <algorithm>
#include <fstream>

using std::string;
using std::ostringstream;
using std::unique_ptr;
using std::set;
using std::istringstream;

namespace pdCalc {

class CommandDispatcher::CommandDispatcherImpl
{
public:
    explicit CommandDispatcherImpl(UserInterface& ui);
    void executeCommand(const string& command);

private:

    void handleCommand(CommandPtr command);
    void printHelp() const;

    CommandManager manager_;
    UserInterface& ui_;
};

CommandDispatcher::CommandDispatcherImpl::CommandDispatcherImpl(UserInterface& ui)
    :ui_(ui)
{}


void CommandDispatcher::CommandDispatcherImpl::executeCommand(const string &command)
{
    if (command == "undo") {
        manager_.undo();
    } else if (command == "redo") {
        manager_.redo();
    } else if (command == "help") {
        printHelp();
    } else {
        auto c = CommandRepository::Instance().allocateCommand(command);
        if (!c) {
            ostringstream oss;
            oss << "Command " << command << " is not a known command";
            ui_.postMessage(oss.str());
        } else {
            handleCommand(std::move(c));
        }
    }

    return;
}

void CommandDispatcher::CommandDispatcherImpl::handleCommand(CommandPtr command)
{
    try {
        manager_.executeCommand(std::move(command));
    }  catch (Exception& e) {
        ui_.postMessage(e.what());
    }

    return;
}

void CommandDispatcher::CommandDispatcherImpl::printHelp() const
{
    ostringstream oss;
    set<string> allCommands = CommandRepository::Instance().getAllCommandNames();
    oss << "\n";
    oss << "undo: undo last operation\n"
        << "redo: redo last operation\n";

    for (const auto& i : allCommands)
    {
        CommandRepository::Instance().printHelp(i, oss);
        oss << "\n";
    }

    ui_.postMessage(oss.str());
}
}
