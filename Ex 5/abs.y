%{
#include <stdlib.h>
#include <stdio.h>
int yylex(void);
#include "y.tab.h"


struct node
{
	struct node* left;
    struct node* right;
    char ar[10];
};

struct node* newNode(char* data) 
{
  struct node* node = (struct node*) malloc(sizeof(struct node));
  strcpy(node->ar,data);
  node->left = NULL;
  node->right = NULL;  
  return(node);
}

struct node* make2(struct node*a,struct node*b,char* data)
{
	struct node* node = (struct node*) malloc(sizeof(struct node));
  strcpy(node->ar,data);
  node->left = a;
  node->right = b;  
  return(node);
}

void print(struct node *a)
{
	printf("%s ",a->ar);
	printf("\t\t");
	if(a->left!=NULL)
	{
	printf("%s ",a->left->ar);
	}
	else
	printf("NULL ");

	printf("\t\t");
	if(a->right!=NULL)
	{
	printf("%s ",a->right->ar);
	}
		else
	printf("NULL ");

	printf("\n");	

	if(a->left!=NULL)
	{
		print(a->left);
	}
	if(a->right!=NULL)
	{
		print(a->right);
	}

		
}

%}
%union
{
	char a_variable[10];
	struct node* tree2;
}
%token<a_variable>INTEGE
%type<tree2> expr mulex modx bool1 bool2 term

%%
program:
line program
| line
line:
expr '\n' { printf ("Node \t Left Child \t Right Child\n"); print($1); }
expr:
expr '+' mulex { $$=make2($1,$3,"+");}
| expr '-' mulex{ $$=make2($1,$3,"-");}
| mulex { $$ = $1; }
mulex:
mulex '*' modx { $$=make2($1,$3,"*");}
| mulex '/' modx { $$=make2($1,$3,"/");}
| mulex '%' modx { $$=make2($1,$3,"%");}
| modx { $$ = $1; }
modx:
modx '^' bool1 { $$=make2($1,$3,"^");}
| bool1 { $$ = $1;}
bool1:
bool1 '||' bool2 { $$=make2($1,$3,"||");}
| bool2	{$$=$1;} 
bool2:
bool2 '&&' term { $$=make2($1,$3,"&&");}
| term {$$ = $1;}
term:
'(' expr ')' { $$ = $2; }
| INTEGE { 
$$ = newNode($1); }

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

