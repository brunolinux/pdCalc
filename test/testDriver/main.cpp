#include <QtTest>
#include <iostream>
#include <QStringList>
#include <unordered_map>

#include "../utilitiesTest/publisherobservertest.h"
#include "../backendTest/stacktest.h"
#include "../backendTest/corecommandstest.h"
#include "../backendTest/commandrepositorytest.h"
#include "../backendTest/commandmanagertest.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    // I use QStringList instead of argv directly because the QStringList
    // argument to qExec is constant. API doc indicates that for the argv
    // version, it may alter argv making repeated calls to qExec unstable
    // with respect to the arguments.
    QStringList args;
    for(int i = 0; i < argc; ++i)
        args.append( QString{argv[i]} );

    std::unordered_map<std::string, int> passFail;

    PublisherObserverTest pot;
    passFail["PublisherObserverTest"] = QTest::qExec(&pot, args);

    StackTest st;
    passFail["StackTest"] = QTest::qExec(&st, args);

    CoreCommandsTest cct;
    passFail["CoreCommandsTest"] = QTest::qExec(&cct, args);

    CommandRepositoryTest crt;
    passFail["CommandRepositoryTest"] = QTest::qExec(&crt, args);

    CommandManagerTest cmt;
    passFail["CommandManagerTest"] = QTest::qExec(&cmt, args);

    cout << endl;
    int errors = 0;
    for(const auto& i : passFail)
    {
        errors += i.second;
        if(i.second != 0)
            cout << "Failed test in " << i.first << endl;
    }

    if(errors == 0)
        cout << "All tests passed" << endl;

    return 0;
}
