#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <memory>
#include "command.h"

namespace pdCalc {
class CommandManager
{
    class CommandManagerImpl;
    class UndoRedoStackStrategy;
    class UndoRedoListStrategyVector;
    class UndoRedoListStrategy;

public:
    enum class UndoRedoStrategy { ListStrategy, StackStrategy, ListStrategyVector };

    explicit CommandManager(UndoRedoStrategy st = UndoRedoStrategy::StackStrategy);
    ~CommandManager();

    size_t getUndoSize() const;
    size_t getRedoSize() const;

    void executeCommand(CommandPtr c);

    void undo();
    void redo();

private:
    CommandManager(const CommandManager&) = delete;
    CommandManager(CommandManager&& ) = delete;
    CommandManager& operator=(const CommandManager&) = delete;
    CommandManager& operator=(CommandManager&&) = delete;

    std::unique_ptr<CommandManagerImpl> pimpl_;
};
}


#endif // COMMANDMANAGER_H
