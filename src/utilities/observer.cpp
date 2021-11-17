#include "observer.h"
#include "publisher.h"

using std::shared_ptr;
#include <iostream>

namespace pdCalc {

Observer::Observer(const std::string &name)
    :observerName_(name)
{
}

Observer::~Observer()
{}

void Observer::notify(std::shared_ptr<EventData> d)
{
    notifyImpl(d);
    return;
}
}
