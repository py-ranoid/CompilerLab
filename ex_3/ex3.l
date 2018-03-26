
digit [0-9]
letter [A-Za-z]
ppd #include

%{
    #include<stdio.h>
    int line = 0, characters = 0, numbers = 0, var = 0, include = 0, func = 0, unary=0, strlit = 0;
%}

%%
("using"[" "]*"namespace"[" "]*"std"[" "]*;)  printf("\nScope: <%s> ",yytext);

(("int"|"float"|"char"|"long")[" "]*) printf("\nData type: <%s> ",yytext);

(("if"|"while"|"else"|"return"|"true"|"false")[" "]*) printf("\nKeyword: <%s> ",yytext);

(([" "]*"\""[a-zA-Z0-9 ]*"\"")|("\'"[a-zA-Z0-9]"\'"[" "]*);*) {
                                strlit++;
                                printf("\nstring literal: <%s> ",yytext);
}

([a-zA-Z]+[(][a-zA-Z0-9,\" ]*[)]) {
                                func++;
                                printf("\nFunction call: <%s> ",yytext);
}

("#include"<[a-zA-Z]+>) {
                                include++;
                                printf("\ninclude: <%s> ",yytext);
}
([0-9]+[^a-zA-Z\n,;]*) {
                                numbers++;
                                printf("\nNumber: <%s> ",yytext);
}
([a-zA-Z]+[0-9]*[" "]*(=|;|" "|,|\))) {
                                var++;
                                printf("\nIdentifier: <");
                                for (int i =0; i<yyleng-1; i++)
                                printf("%c",yytext[i]);
                                printf(">");
}
("++"|"--") {
                                unary++;
                                printf("\nUnary Operator : <%s> ",yytext);
}
(>=|<=|>|<|!=) {
                                unary++;
                                printf("\nRelational Operator : %s ",yytext);
}
. {
    printf("");
}

%%

int main(int argc, char *argv[]){
    yyin = fopen( argv[1], "r");
    yylex();
    printf("\n ________________________ \n");
    fclose(yyin);
    return 0;
}