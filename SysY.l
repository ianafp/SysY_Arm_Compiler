%{
#include "y.tab.h"
#include <stdio.h>
%}

%%
\/\/.*$ | \/\*[\s\S]*?\*\/ {return comment;}

\bint\b {return _int;}
\bbool\b {return _bool;}
\bvoid\b {return _void;}
\bconst\b {return _const;}
\bif\b {return _if;}
\belse\b {return _else;}
\bwhile\b {return _while;}
\bbreak\b {return _break;}
\bcontinue\b {return _continue;}
\breturn\b {return _return;}
\bmain\b {return _main;}

\b[a-zA-Z_][a-zA-Z0-9_]*\b {return _identifier;}

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
\% {return _mod;}

">" {return _greater;}
"<" {return _less;}
">=" {return _greater_equal;}
"<=" {return _less_equal;}
"==" {return _equal;}
"!=" {return _nequal;}

&& {return _logical_and;}
\|\| {return _logical_or;}
! {return _logical_not;}

\s
.




%%

