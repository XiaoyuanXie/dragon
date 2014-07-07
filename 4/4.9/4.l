string [a-zA-Z]+

%%

[ ]			{ /*忽略*/ }
{string}	{	yylval = yytext; return STRING; }
\n|.		{ return yytext[0]; }
