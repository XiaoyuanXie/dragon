%{
	#include "stdio.h"
	LT, LE, EQ, NE, GT, GE,
	IF, THEN, ELSE, RELOP,
	ID, NUMBER, STRING;
	int yylval;
%}

delim			[ \t]
ws				{delim}+

%%

float			{printf("double");}
{ws}			{printf(" ");}
\n|.			{printf("%s", yytext);}

%%

int yywrap(void){
	return 1;
}

int main(void){
	yyin=stdin;
	return yylex();
}
