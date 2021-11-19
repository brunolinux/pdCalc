#ifndef COMMANDREPOSITORYTEST_H
#define COMMANDREPOSITORYTEST_H

#include <QTest>

class CommandRepositoryTest : public QObject
{
    Q_OBJECT
private slots:
    void testRegister();
    void testDuplicateRegister();
    void testDeregister();
    void testAllocateCommand();
};

#endif // COMMANDREPOSITORYTEST_H
