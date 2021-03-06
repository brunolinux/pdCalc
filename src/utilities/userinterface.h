#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "publisher.h"

namespace pdCalc {

class CommandData : public EventData
{
public:
    CommandData(const std::string& s) : command_(s) {}
    const std::string& command() const { return command_; }
private:
    std::string command_;
};

class UserInterface : protected Publisher
{
public:
    UserInterface() { registerEvent(CommandEntered); };
    virtual ~UserInterface() {}

    virtual void postMessage(const std::string& m) = 0;
    virtual void stackChanged() = 0;

    using Publisher::attach;
    using Publisher::detach;

    static const std::string CommandEntered;
};

}



#endif // USERINTERFACE_H
