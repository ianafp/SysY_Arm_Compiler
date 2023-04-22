%option noyywrap
%option nounput
%option noinput
%option yylineno

%{

#include <cstdlib>
#include <string>

// 因为 Flex 会用到 Bison 中关于 token 的定义
// 所以需要 include Bison 生成的头文件
#include "sysy.tab.hpp"
#include "headers/position.h"

pos_t cur_pos;
int col_record = 1;

using namespace std;

%}

/* 空白符和注释 */
WhiteSpace    [ \t\n\r]*
LineComment   "//".*
/* add the block comment, here we do this by convert a DFA to regular expression */
/* be careful about '\* -> * character' or '*' -> zero or more */
BlockComment  "/*"([^*]*\*)([^*/][^*]*\*)*"/"

/* 标识符 */
Identifier    [a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
Decimal       [1-9][0-9]*
Octal         0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

%%
\n              { col_record = 0; }
{WhiteSpace}    { /* 忽略, 不做任何操作 */ col_record++; }
{LineComment}   { /* 忽略, 不做任何操作 */ }
{BlockComment}  { /* discard. */ }

"int"           { cur_pos.line = yylineno; cur_pos.column = col_record; return INT; col_record += 3; }
"return"        { cur_pos.line = yylineno; cur_pos.column = col_record; return RETURN; col_record += 5; }

{Identifier}    { yylval.str_val = new string(yytext); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return IDENT; col_record += yyleng; }

{Decimal}       { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return INT_CONST; col_record += yyleng; }
{Octal}         { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return INT_CONST; col_record += yyleng; }
{Hexadecimal}   { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return INT_CONST; col_record += yyleng; }

.               { return yytext[0]; col_record ++; } // here we use yytext[0] to discard the '\0' at the tail of the c string.

%%
