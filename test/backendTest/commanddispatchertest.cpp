#include "commanddispatchertest.h"
#include "src/backend/commandrepository.h"
#include "src/backend/stack.h"
#include "utilities/userinterface.h"

#include <cmath>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::vector;
using std::ostringstream;
using std::string;

namespace  {

class TestInterface : public pdCalc::UserInterface
{
public:
    TestInterface() : lastMessage_{""} { }
    void postMessage(const string& m) override { lastMessage_ = m; }
    void stackChanged() override { }
    const string& getLastMessage() const { return lastMessage_; }

    double top() const;

private:
    string lastMessage_;
};

double TestInterface::top() const
{
    vector<double> v{ pdCalc::Stack::Instance().getElements(1) };
    return v.back();
}
}

void CommandDispatcherTest::testCommandDispatcher()
{

}
