%{
	#include "stdio.h"
	int LT, LE, EQ, NE, GT, GE,
	IF, THEN, ELSE, RELOP,
	ID, NUMBER, STRING;
	int yylval;
%}

delim			[ \t]
ws				{delim}+
digit			[0-9]
letter			[A-Za-z]
id				{letter}({letter}|{digit})*

%%

float						{printf("double");}
{ws}						{printf(" ");}
[sS][eE][lL][eE][cC][tT]	{printf("select");}
[fF][rR][oO][mM]			{printf("from");}
[wW][hH][eE][rR][eE]		{printf("where");}
{id}						{printf("id: %s", yytext);}
\n|.						{printf("%s", yytext);}

%%

int yywrap(void){
	return 1;
}

int main(void){
	yyin=stdin;
	return yylex();
}
