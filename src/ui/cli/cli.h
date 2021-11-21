#ifndef CLI_H
#define CLI_H

#include "utilities/userinterface.h"
#include <string>
#include <memory>
#include <iostream>

namespace pdCalc {
class Cli : public UserInterface
{
    class CliImpl;
public:
    Cli(std::istream&, std::ostream&);
    ~Cli();

    void execute(bool suppressStartupMessage = false, bool echo = false);

private:
    void postMessage(const std::string& m) override;
    void stackChanged() override;

    Cli(const Cli&) = delete;
    Cli(Cli&&) = delete;
    Cli& operator=(const Cli&) = delete;
    Cli& operator=(Cli&&) = delete;

    std::unique_ptr<CliImpl> pimpl_;
};
}



#endif // CLI_H
