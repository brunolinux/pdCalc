#ifndef STACK_H
#define STACK_H

#include "utilities/publisher.h"
#include <vector>
#include <memory>
#include <string>

namespace pdCalc {
class StackEventData : public EventData
{
public:
    enum class ErrorConditions { Empty, TooFewArguments };
    explicit StackEventData(ErrorConditions e) : err_(e) {}

    static const char* Message(ErrorConditions ec);
    const char* message() const;
    ErrorConditions error() const { return err_; }

private:
    ErrorConditions err_;
};

class Stack : private Publisher
{
    class StackImpl;
public:
    static Stack& Instance();

    void push(double, bool suppressChangeEvent = false);
    double pop(bool suppressChangeEvent = false);
    void swapTop();

    // returns first min(n, stackSize) elements of the stack with the top of stack at position 0
    std::vector<double> getElements(size_t n) const;
    void getElements(size_t n, std::vector<double>&) const;

    using Publisher::attach;
    using Publisher::detach;

    // these are just needed for testing
    size_t size() const;
    void clear();

    static const std::string StackChanged;
    static const std::string StackError;

private:
    Stack();
    ~Stack();
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack& operator=(const Stack&&) = delete;

    std::unique_ptr<StackImpl> pimpl_;
};
}


#endif // STACK_H
