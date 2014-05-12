%{
	#include "stdio.h"
	LT, LE, EQ, NE, GT, GE,
	IF, THEN, ELSE, RELOP,
	ID, NUMBER, STRING;
	int yylval;
%}

delim			[ \t]
ws				{delim}+
digit			[0-9]
letter			[A-Za-z]
id				_?({letter}|{digit})*
words1			[^aeiou]+{letter}*
words2			[aeiou]+{letter}*

%%

float			{printf("double");}
{ws}			{printf(" ");}
{words1}		{printf("%say", yytext);}
{words2}		{printf("%s%cay", yytext+1, yytext[0]);}
\n|.			{printf("%s", *yytext);}

%%

int yywrap(void){
	return 1;
}

int main(void){
	yyin=stdin;
	return yylex();
}
