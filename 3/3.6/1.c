%{

	#include <stdio.h>
	int yylval;

%}

delim	[ \t]
ws		{delim}+

%%



%%

int yywrap(void){
	return 1;
}

int main(void){
	yyin = stdin;
	return yylex();
}
