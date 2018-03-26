%{
#include <stdlib.h>
#include <stdio.h>
#include "y.tab.h"
void yyerror(char*);
extern int yylval;
%}

%%

[ \t] ;

[0-9]+\.[0-9]+ { 
					yylval=2;
					return INTEGER;
 				}

[0-9]+ {
			yylval= 1;
			return INTEGER;
		}

[-+*/^%] {	
			return *yytext;
		 }

"==" {
		return *yytext;
	}

"(" {
	return *yytext;
	}

")" {
		return 0;
	}

\n  {	return *yytext;
	}
