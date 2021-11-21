#ifndef APPOBSERVER_H
#define APPOBSERVER_H

#include "utilities/observer.h"
#include "commanddispatcher.h"

namespace pdCalc {

class UserInterface;

class CommandIssuedObserver : public Observer
{
public:
    explicit CommandIssuedObserver(CommandDispatcher& ce);

private:
    void notifyImpl(std::shared_ptr<EventData>) override;

    CommandDispatcher& ce_;
};

class StackUpdatedObserver : public Observer
{
public:
    explicit StackUpdatedObserver(UserInterface& ui);

private:
    void notifyImpl(std::shared_ptr<EventData>) override;

    UserInterface& ui_;
};

}

#endif // APPOBSERVER_H
