#ifndef COMMANDREPOSITORY_H
#define COMMANDREPOSITORY_H

#include <memory>
#include <set>
#include "command.h"

namespace pdCalc {

class CommandRepository
{
    class CommandRepositoryImpl;
public:
    static CommandRepository& Instance();

    void registerCommand(const std::string& name, CommandPtr c);
    CommandPtr deregisterCommand(const std::string& name);

    size_t getNumberCommands() const;

    CommandPtr allocateCommand(const std::string& name) const;

    bool hasKey(const std::string& s) const;

    std::set<std::string> getAllCommandNames() const;

    void printHelp(const std::string& command, std::ostream&) const;

    void clearAllCommands();
private:
    CommandRepository();
    ~CommandRepository();

    CommandRepository(const CommandRepository&) = delete;
    CommandRepository(CommandRepository&&) = delete;
    CommandRepository& operator=(const CommandRepository&) = delete;
    CommandRepository& operator=(CommandRepository&&) = delete;

    std::unique_ptr<CommandRepositoryImpl> pimpl_;
};

}


#endif // COMMANDREPOSITORY_H
