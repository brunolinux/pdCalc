#ifndef COMMANDMANAGERTEST_H
#define COMMANDMANAGERTEST_H

#include <QTest>
#include "backend/commandmanager.h"

class CommandManagerTest : public QObject
{
    Q_OBJECT
private slots:
    void testExecuteStackStrategy();
    void testUndoStackStrategy();
    void testRedoStackStrategy();
    void testRedoStackFlushStackStrategy();
    void testResourceCleanupStackStrategy();
    void ignoreErrorStackStrategy();

    void testExecuteListStrategy();
    void testUndoListStrategy();
    void testRedoListStrategy();
    void testRedoStackFlushListStrategy();
    void testResourceCleanupListStrategy();
    void ignoreErrorListStrategy();

    void testExecuteListStrategyVector();
    void testUndoListStrategyVector();
    void testRedoListStrategyVector();
    void testRedoStackFlushListStrategyVector();
    void testResourceCleanupListStrategyVector();
    void ignoreErrorListStrategyVector();

private:
    void testExecute(pdCalc::CommandManager::UndoRedoStrategy);
    void testUndo(pdCalc::CommandManager::UndoRedoStrategy);
    void testRedo(pdCalc::CommandManager::UndoRedoStrategy);
    void testRedoStackFlush(pdCalc::CommandManager::UndoRedoStrategy);
    void testResourceCleanup(pdCalc::CommandManager::UndoRedoStrategy);
    void ignoreError(pdCalc::CommandManager::UndoRedoStrategy);
};

#endif // COMMANDMANAGERTEST_H
