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
    bool isNum(const string&, double& d);
    void handleCommand(CommandPtr command);
    void printHelp() const;

    CommandManager manager_;
    UserInterface& ui_;
};

CommandDispatcher::CommandDispatcherImpl::CommandDispatcherImpl(UserInterface& ui)
: ui_(ui)
{ }

void CommandDispatcher::CommandDispatcherImpl::executeCommand(const string& command)
{
    // entry of a number simply goes onto the the stack
    double d;
    if( isNum(command, d) )
        manager_.executeCommand(MakeCommandPtr<EnterNumber>(d));
    else if(command == "undo")
        manager_.undo();
    else if(command == "redo")
        manager_.redo();
    else if(command == "help")
        printHelp();
    else if(command.size() > 6 && command.substr(0, 5) == "proc:")
    {
        auto filename = command.substr(5, command.size() - 5);
        // handleCommand( MakeCommandPtr<StoredProcedure>(ui_, filename) );
    }
    else
    {
        auto c = CommandRepository::Instance().allocateCommand(command);
        if(!c)
        {
            ostringstream oss;
            oss << "Command " << command << " is not a known command";
            ui_.postMessage( oss.str() );
        }
        else handleCommand( std::move(c) );
    }

    return;
}

void CommandDispatcher::CommandDispatcherImpl::handleCommand(CommandPtr c)
{
    try
    {
        manager_.executeCommand( std::move(c) );
    }
    catch(Exception& e)
    {
        ui_.postMessage( e.what() );
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

    for(auto i : allCommands)
    {
        CommandRepository::Instance().printHelp(i, oss);
        oss << "\n";
    }

    ui_.postMessage( oss.str() );

}

// uses a C++11 regular expression to check if this is a valid double number
// if so, converts it into one and returns it
bool CommandDispatcher::CommandDispatcherImpl::isNum(const string& s, double& d)
{
     if(s == "+" || s == "-") return false;

     std::regex dpRegex("((\\+|-)?[[:digit:]]*)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
     bool isNumber{ std::regex_match(s, dpRegex) };

     if(isNumber)
     {
         d = std::stod(s);
     }

     return isNumber;
}

void CommandDispatcher::commandEntered(const std::string& command)
{
    pimpl_->executeCommand(command);

    return;
}

CommandDispatcher::CommandDispatcher(UserInterface& ui)
{
    pimpl_ = std::make_unique<CommandDispatcherImpl>(ui);
}

CommandDispatcher::~CommandDispatcher()
{ }

}
