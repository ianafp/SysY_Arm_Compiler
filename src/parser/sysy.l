%option noyywrap
%option nounput
%option noinput
%option yylineno

%{
#include "sysy.tab.hpp"
#include <cstdlib>
#include <string>
#include "common/position.h"

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

/* 字符串 */
String \"([^\"\\]|\\.)*\"
%%
\n              { col_record = 0; }
{WhiteSpace}    { /* 忽略, 不做任何操作 */ col_record++; }
{LineComment}   { /* 忽略, 不做任何操作 */ }
{BlockComment}  { /* discard. */ }

"int"           {cur_pos.line = yylineno; cur_pos.column = col_record; return _int; col_record += 3;}
"void"          {cur_pos.line = yylineno; cur_pos.column = col_record; return _void; col_record += 4;}
"const"         {cur_pos.line = yylineno; cur_pos.column = col_record; return _const; col_record += 5;}
"if"            {cur_pos.line = yylineno; cur_pos.column = col_record; return _if; col_record += 2;}
"else"          {cur_pos.line = yylineno; cur_pos.column = col_record; return _else; col_record += 4;}
"while"         {cur_pos.line = yylineno; cur_pos.column = col_record; return _while; col_record += 5;}
"break"         {cur_pos.line = yylineno; cur_pos.column = col_record; return _break; col_record += 5;}
"continue"      {cur_pos.line = yylineno; cur_pos.column = col_record; return _continue; col_record += 8;}
"return"        {cur_pos.line = yylineno; cur_pos.column = col_record; return _return; col_record += 6;}

{Identifier}    { yylval.str_val = new string(yytext); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _identifier; col_record += yyleng; }

{Decimal}       { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _const_val; col_record += yyleng; }
{Octal}         { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _const_val; col_record += yyleng; }
{Hexadecimal}   { yylval.int_val = strtol(yytext, nullptr, 0); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _const_val; col_record += yyleng; }
{String} { yylval.str_val = new string(yytext); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _string; col_record += yyleng; }
">"             {cur_pos.line = yylineno; cur_pos.column = col_record; return _greater; col_record += 1;}
"<"             {cur_pos.line = yylineno; cur_pos.column = col_record; return _less; col_record += 1;}
">="            {cur_pos.line = yylineno; cur_pos.column = col_record; return _greater_equal; col_record += 2;}
"<="            {cur_pos.line = yylineno; cur_pos.column = col_record; return _less_equal; col_record += 2;}
"=="            {cur_pos.line = yylineno; cur_pos.column = col_record; return _equal; col_record += 2;}
"!="            {cur_pos.line = yylineno; cur_pos.column = col_record; return _nequal; col_record += 2;}

"&&"            {cur_pos.line = yylineno; cur_pos.column = col_record; return _logical_and; col_record += 2;}
"||"            {cur_pos.line = yylineno; cur_pos.column = col_record; return _logical_or; col_record += 2;}


\"[\s\S]*\"     { yylval.str_val = new string(yytext); cur_pos.line = yylineno; cur_pos.column = yylineno - yyleng + 1; return _string; col_record += yyleng; }

.               { return yytext[0]; col_record ++; }



%%

