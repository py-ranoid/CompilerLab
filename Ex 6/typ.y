%{
#include <stdlib.h>
#include <stdio.h>
int yylex(void);
#include "y.tab.h"

int max(int a,int b)
{
	if(a>b)
	return a;
	return b;
}

%}

%token INTEGER

%%

program : line program
		| line

line:	expr '\n' { 
			if($1==0)
				printf("Boolean\n");
			else if($1==1)
				printf("Integer\n");
			else
				printf("Double\n");
 }

expr:
expr '+' mulex { $$ =max($1,$3); }
| expr '-' mulex{ $$ =max($1,$3); }
| mulex { $$ = $1; }

mulex:
mulex '*' term { $$ =max($1,$3); }
| mulex '/' term { $$ =max($1,$3); }
| mulex '==' term { $$ = 0; }
| term { $$ = $1; }

term:
'(' expr ')' { $$ = $2; }
| INTEGER { $$ = $1; }

%%

int yyerror(const char *s)
{
fprintf(stderr,"%s\n",s);
return 0;
}

int yywrap()
{
return(1);
}

int main(void)
{
yyparse();
return 0;
}

