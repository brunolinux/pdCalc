#include "appobserver.h"
#include "utilities/exception.h"
#include "utilities/userinterface.h"

using std::dynamic_pointer_cast;

namespace pdCalc {

CommandIssuedObserver::CommandIssuedObserver(CommandDispatcher& ce)
: Observer("CommandIssued")
, ce_(ce)
{ }

void CommandIssuedObserver::notifyImpl(std::shared_ptr<EventData> eventData)
{
    auto data = dynamic_pointer_cast<CommandData>(eventData);
    if(!data)
    {
        throw Exception("Could not convert CommandData to a command");
    }
    else
    {
        ce_.commandEntered( data->command() );
    }

    return;
}

StackUpdatedObserver::StackUpdatedObserver(UserInterface& ui)
: Observer("StackUpdated")
, ui_(ui)
{ }

void StackUpdatedObserver::notifyImpl(std::shared_ptr<EventData>)
{
    ui_.stackChanged();

    return;
}

}
