#include <gtest/gtest.h>
#include <sstream>
#include "sysy.tab.hpp"
#include "sysy.lex.hpp"

class Lexer {
public:
    Lexer(std::istream& inputStream) : input_(inputStream), position_(0) {}

    int getNextToken() {
        int token = yylex();
        return token;
    }

private:
    std::istream& input_;
    size_t position_;
};

class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 在每个测试用例执行之前的设置操作
    }

    void TearDown() override {
        // 在每个测试用例执行之后的清理操作
    }
    void testTokenSequence(const std::string& inputText, const std::vector<int>& expectedTokens) {
        // std::istringstream inputStream(inputText);
        // Lexer lexer(inputStream);

        // for (const int& expectedToken : expectedTokens) {
        //     int token = lexer.getNextToken();
        //     ASSERT_EQ(token, expectedToken);
        // }
        
            // 将输入字符串加载到词法分析器中
        YY_BUFFER_STATE buffer = yy_scan_string(inputText.c_str());

        // 调用 yylex 进行词法分析
        for (const int& expectedToken : expectedTokens) {
            int token = yylex();
            ASSERT_EQ(token, expectedToken);
        }

        // 释放缓冲区
        yy_delete_buffer(buffer);
    }
};

TEST_F(LexerTest, BasicTokens) {
    std::string inputText = "int a = 10;";
    std::vector<int> expectedTokens = {
        _int,
        _identifier,
        '=',
        _const_val,
        ';',
    };

    testTokenSequence(inputText, expectedTokens);
}

TEST_F(LexerTest, StringLiteral) {
    std::string inputText = "s = \"Hello, World!\"; \"this is a string\"";
    std::vector<int> expectedTokens = {
        _identifier,
        '=',
        _string,
        ';',
        _string,
    };

    testTokenSequence(inputText, expectedTokens);
}

TEST_F(LexerTest, Keywords) {
    std::string inputText = "int void const if else while break continue return";
    std::vector<int> expectedTokens = {
        _int,
        _void,
        _const,
        _if,
        _else,
        _while,
        _break,
        _continue,
        _return,
    };

    testTokenSequence(inputText, expectedTokens);
}

TEST_F(LexerTest, Operators) {
    std::string inputText = "+ - * / % = == != < > <= >=";
    std::vector<int> expectedTokens = {
        '+',
        '-',
        '*',
        '/',
        '%',
        '=',
        _equal,
        _nequal,
        _less,
        _greater,
        _less_equal,
        _greater_equal,
    };

    testTokenSequence(inputText, expectedTokens);
}

TEST_F(LexerTest, Identifiers) {
    std::string inputText = "a b_var myVariable_123";
    std::vector<int> expectedTokens = {
        _identifier,
        _identifier,
        _identifier,
    };

    testTokenSequence(inputText, expectedTokens);
}

TEST_F(LexerTest, IntegerLiterals) {
    std::string inputText = "42 0x1A 075";
    std::vector<int> expectedTokens = {
        _const_val,
        _const_val,
        _const_val,
    };

    testTokenSequence(inputText, expectedTokens);
}
