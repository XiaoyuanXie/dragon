%{
#include <ctype.h>
#ifndef YYSTYPE
#define YYSTYPE char*
#endif
%}

%token STRING

%%

lines :	lines S '\n'
	  |	'\n'
	  |	/* empty */
	  | error '\n'	{ yyerrok; }
	  ;
	
S	  :	STRING	{ int i; 
				  for(i = 0;i < strlen($1)/2; ++i)
					if($1[i] != $1[strlen($1)-1-i])
						break;
				  if(i < strlen($1)/2)
					printf("不是回文\n");
				  else
					printf("是回文\n");
				}
	  ;

%%
#include "lex.yy.c"

int main(){
	yyin = stdin;
	return yyparse();
}

void yyerror(){
	return;
}
int yywrap(){
	return 1;
}
