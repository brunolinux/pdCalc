#include <iostream>
#include <memory>
#include "ui/cli/cli.h"
#include "backend/commanddispatcher.h"
#include "backend/appobserver.h"
#include "backend/corecommand.h"
#include "backend/stack.h"

using namespace pdCalc;

using std::cout;
using std::endl;
using std::make_unique;

int main()
{
    Cli cli{std::cin, std::cout};

    CommandDispatcher ce{cli};

    RegisterCoreCommands(cli);

    cli.attach(UserInterface::CommandEntered, make_unique<CommandIssuedObserver>(ce));
    Stack::Instance().attach(Stack::StackChanged, make_unique<StackUpdatedObserver>(cli));

    cli.execute();
    return 0;
}
