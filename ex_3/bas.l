%{
	#include<stdio.h>
	#include<string.h>
	int yylval;

	char temp_dt[20] , temp_name[20] , temp_val[20];
	int location = 1000 , temp_bytes;
	int status = 0;

	struct symbol_table{
		char var_name[20];
		char value[20];
		int location;
		char datatype[20];
		int bytes;
	}
%}

ROP (<=)|(==)|(>=)|(>)|(<)|(!=)

special_character (";"|","|"."|"{"|"}"|"["|"]"|"("|")")
bitwise_ops ("^"|"&"|"|"|"<<"|">>")
unary_ops ("-"|"++"|"--")
assignment_op ("=")
logical_ops ("&&"|"||"|"!")
arithmetic_ops ("+"|"-"|"*"|"/"|"%")
ar_as_ops ("+="|"-="|"*="|"/="|"%=")
function_calls ("printf"|"scanf"|"getch"|"clrscr"|"getch")

datatypes ("int"|"float"|"char"|"double"|"long")

keyword ("auto"|"break"|"static"|"else"|"if"|"else if"|"void"|"for"|"while"|)
digit [0-9]
single_comment ("//")
multi_comment ("/*")((.)|(\n))*("*/")
constant {digit}+("."){digit}+

preprocessor (#(.)*)

letter [A-Za-z]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+|-]?{digit}+)?
delim [ \t\n]
ws {delim}+
dec_delim [,]
final_line_delim [;]
mainfn {datatypes}?(main)

%%

{special_character} {printf("\n%s : Special character" , yytext);}
{preprocessor} {printf("\n%s : Preprocessor directive" , yytext);}
{mainfn} {printf("\n%s : Main encountered " , yytext);}
{datatypes} {printf("\n%s : Keyword detected" , yytext); }
{keyword} {printf("\n%s : Keyword detected" , yytext);}
{single_comment} {printf("\n%s : Single line comment" , yytext);}
{id} {printf("\n%s : ID" , yytext);}
{multi_comment} {printf("\n%s : Multi line comment" , yytext);}
{bitwise_ops} {printf("\n%s : bitwise_ops" , yytext);}
{unary_ops} {printf("\n%s : unary_ops" , yytext);}
{assignment_op} {printf("\n%s : assignment_op" , yytext);}
{logical_ops} {printf("\n%s : logical_ops" , yytext);}
{arithmetic_ops} {printf("\n%s : arithmetic_ops" , yytext);}
{ar_as_ops} {printf("\n%s : ar_as_ops" , yytext);}
{function_calls} {printf("\n%s : function_calls" , yytext);}
{constant} {printf("\n%s : constant" , yytext);}
{ws} {} 

%%

void get_dt(){
	strcpy(temp_dt , yytext);
	temp_bytes = 2;
	if(!strcmp(temp_dt , "int"))
		temp_bytes = 4;
	else if(!strcmp(temp_dt , "char"))
		temp_bytes = 1;
	status = 1;
}

void get_val(){

}

int main(int argc , char* argv[]) {
	yyin = fopen("test.txt" , "r");
    yylex();

}
