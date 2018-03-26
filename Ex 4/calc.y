%{
#include <stdlib.h>
#include <stdio.h>
int yylex(void);
#include "y.tab.h"
%}

%token INTEGER
%%
program:
line program
| line

line:
expr '\n' { printf(“%d\n",$1); }

expr:
expr '+' mulex { $$ = $1 + $3; }
| expr '-' mulex{ $$ = $1 -$3; }
| mulex { $$ = $1; }

mulex:
mulex '*' modx { $$ = $1 * $3; }
| mulex '/' modx { $$ = $1 / $3; }
| mulex '%' modx {$$ = $1 % $3; }
| modx { $$ = $1; }

modx:
modx '^' bool1 {$$ = pow($1,$3);}
| bool1 { $$ = $1;}

bool1:
bool1 '||' bool2 {$$ = ($1||$3);}
| bool2	{$$=$1;} 

bool2:
bool2 '&&' term {$$ = ($1&&$3);}
| term {$$ = $1;}

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

