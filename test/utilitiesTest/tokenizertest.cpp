#include "tokenizertest.h"
#include "src/utilities/tokenizer.h"
#include <iostream>
#include <sstream>

using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::ostringstream;
using std::istringstream;

void TokenizerTest::assertTokenizerMatches(const std::vector<string>& tokens, const pdCalc::Tokenizer& tokenizer)
{
    QCOMPARE( tokens.size(), tokenizer.nTokens() );

    auto j = tokens.begin();
    for(auto i : tokenizer)
    {
        QCOMPARE(i, *j);
        ++j;
    }

    for(size_t i = 0; i < tokenizer.nTokens(); ++i)
    {
        QCOMPARE(tokens[i], tokenizer[i]);
    }
}

void TokenizerTest::testTokenizationFromString()
{
    vector<string> tokens = {"7.3454", "8.21", "+", "dup", "dup", "*", "-", "4.35", "tan" };

    string str;
    for(size_t i = 0; i < tokens.size(); ++i)
    {
        str += tokens[i] + (i == 4 ? "\n" : " ");
    }

    pdCalc::Tokenizer tokenizer(str);

    assertTokenizerMatches(tokens, tokenizer);

    return;
}

void TokenizerTest::testTokenizationFromStream()
{
    vector<string> tokens = {"7.3454", "8.21", "sin", "dup", "dup", "/", "pow", "4.35", "arctan" "-18.4" "neg" "root"};

    ostringstream oss;
    for(size_t i = 0; i < tokens.size(); ++i)
    {
        oss << tokens[i] + (i % 3 == 0 ? "\n" : " ");
    }

    istringstream iss( oss.str() );

    pdCalc::Tokenizer tokenizer(iss);

    assertTokenizerMatches(tokens, tokenizer);

    return;
}
