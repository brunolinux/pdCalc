#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <functional>

namespace pdCalc {
class Command
{
public:
    virtual ~Command() {}

    void execute();

    void undo();

    Command* clone() const;

    const char* helpMessage() const;

protected:
    Command() {}
    Command(const Command&) {}

private:
    virtual void checkPreconditionsImpl() const;

    virtual void executeImpl() noexcept = 0;
    virtual void undoImpl() noexcept = 0;
    virtual Command* cloneImpl() const = 0;

    virtual const char* helpMessageImpl() const noexcept = 0;

    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;
    Command& operator=(Command&&) = delete;
};

class BinaryCommand : public Command
{
public:
    virtual ~BinaryCommand();

protected:
    void checkPreconditionsImpl() const override;

    BinaryCommand() {}
    BinaryCommand(const BinaryCommand&);

private:
    BinaryCommand(BinaryCommand&&) = delete;
    BinaryCommand& operator=(const BinaryCommand&) = delete;
    BinaryCommand& operator=(BinaryCommand&&) = delete;

    void executeImpl() noexcept override;
    void undoImpl() noexcept override;

    virtual double binaryOperation(double next, double top) const noexcept = 0;

    double top_;
    double next_;
};

class UnaryCommand : public Command
{
public:
    virtual ~UnaryCommand();

protected:
    void checkPreconditionsImpl() const override;

    UnaryCommand() {}
    UnaryCommand(const UnaryCommand&);

private:
    UnaryCommand(UnaryCommand&&) = delete;
    UnaryCommand& operator=(const UnaryCommand&) = delete;
    UnaryCommand& operator=(UnaryCommand&&) = delete;

    void executeImpl() noexcept override;
    void undoImpl() noexcept override;

    virtual double unaryOperation(double top) const noexcept = 0;

    double top_;
};


// This shows an entirely different design using function and lambdas.
class BinaryCommandAlternative final : public Command
{
    using BinaryCommandOp = double(double, double);
public:
    BinaryCommandAlternative(const std::string& help, std::function<BinaryCommandOp> f);
    ~BinaryCommandAlternative() = default;

private:
    BinaryCommandAlternative(BinaryCommandAlternative&&) = delete;
    BinaryCommandAlternative& operator=(const BinaryCommandAlternative&) = delete;
    BinaryCommandAlternative& operator=(BinaryCommandAlternative&&) = delete;

    // throws an exception if the stack size is less than two
    void checkPreconditionsImpl() const override;

    BinaryCommandAlternative(const BinaryCommandAlternative&);

    const char* helpMessageImpl() const noexcept override;

    // takes two elements from the stack, applies the binary operation
    // and returns the result to the stack
    void executeImpl() noexcept override;

    // drops the result and returns the original two numbers to the stack
    void undoImpl() noexcept override;

    BinaryCommandAlternative* cloneImpl() const override;

    double top_;
    double next_;
    std::string helpMsg_;
    std::function<BinaryCommandOp> command_;
};

using CommandPtr = std::unique_ptr<Command>;

template<typename T, typename... Args>
auto MakeCommandPtr(Args&&... args)
{
    return CommandPtr{new T{std::forward<Args>(args)...}};
}

inline auto MakeCommandPtr(Command* p)
{
    return CommandPtr{p};
}
}


#endif // COMMAND_H
