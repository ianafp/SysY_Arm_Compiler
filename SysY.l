%{
#include <stdio.h>
%}

%%
\/\/.*$ | \/\*[\s\S]*?\*\/ {return comment;}
\b int \b {return _int;}
\b bool \b {return _bool;}
\b void \b {return _void;}
\b const \b {return _const;}
\b if \b {return _if;}
\b else \b {return _else;}
\b while \b {return _while;}
\b break \b {return _break;}
\b continue \b {return _continue;}
\b return \b {return _return;}
\b main \b {return _main;}

\b [a-zA-Z_][a-zA-Z0-9_]* \b {return _identifier;}

 0  {;return _const_val;}
 0x[0-9a-fA-F]+ | 0X[0-9a-fA-F] \b {;return _const_val;}
 0[0-7]+  {;return _const_val;}
 [1-9]+[0-9]*  {;return _const_val;}

"(" {return _left_parenthesis;}
")" {return _right_parenthesis;}
"[" {return _left_square_bracket;}
"]" {return _right_square_bracket;}
"{" {return _left_curly_bracket;}
"}" {return _right_curly_bracket;}

"," {return _comma;}
";" {return _semicolon;}
\"[\s\S]*\" {return _string;}

\+ {return _add;}
\- {return _sub;}
\* {return _mul;}
\/ {return _div;}

">" {return _greater;}
"<" {return _less;}
">=" {return _greater_equal;}
"<=" {return _less_equal;}
"==" {return _equal;}

&& {return _logical_and;}
\|\| {return _logical_or;}
! {return _logical_not;}

\s
.




%%

