digit [0-9]
%{
	#include<stdio.h>
	int num_lines = 0, num_chars = 0,num_numbers=0;
%}
 
%%
\n     ++num_lines;
.      ++num_chars;
(digit)*   {
		++num_numbers;
		}	
%%

int main(int argc , char* argv[]) {
	yyin = fopen(argv[1] , "r");
    yylex();
    printf("# of lines = %d, # of chars = %d, # of numbers = %d\n", num_lines, num_chars,num_numbers);
}
