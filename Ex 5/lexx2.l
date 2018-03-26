%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
void yyerror(char*);
%}
%%
[ \t]+ ;
[0-9a-zA-Z]+ {
strcpy(yylval.a_variable,yytext);
return INTEGE;}
[-+*/^%] {
return *yytext;}
"(" {return *yytext;}
")" {return *yytext;}
"||" {return *yytext;}
"&&" {return *yytext;}
\n {
return *yytext;}
