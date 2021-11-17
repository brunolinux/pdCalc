#ifndef STACKTEST_H
#define STACKTEST_H

#include <QtTest>

class StackTest : public QObject
{
    Q_OBJECT
private slots:
    void testPushPop();
    void testSwapTop();
    void testErrors();
};

#endif // STACKTEST_H
