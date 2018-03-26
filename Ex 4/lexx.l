%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
void yyerror(char*);
%}

%%
[ \t]+ ;
[0-9]+ {yylval = atof(yytext); 
return INTEGER;}

[-+*/^%] {return *yytext;}
"(" {return *yytext;}
")" {return *yytext;}
"||" {return *yytext;}
"&&" {return *yytext;}
\n {return *yytext;}
