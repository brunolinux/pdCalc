#ifndef TOKENIZERTEST_H
#define TOKENIZERTEST_H

#include <QTest>
#include <vector>
#include <string>

namespace pdCalc {
    class Tokenizer;
}

class TokenizerTest : public QObject
{
    Q_OBJECT
private slots:
    void testTokenizationFromString();
    void testTokenizationFromStream();

private:
    void assertTokenizerMatches(const std::vector<std::string>&, const pdCalc::Tokenizer&);
};

#endif // TOKENIZERTEST_H
