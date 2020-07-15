
%{ 
  /* Lex program for implementing desk calculator */
	#include "y.tab.h"
%} 
ALPHA [A-Za-z] 
DIGIT [0-9] 
%% 
"let "{ALPHA}({ALPHA}|{DIGIT})*			  { 
												char *var = yytext+4;
												let(var);
												
										  }
"display "{ALPHA}({ALPHA}|{DIGIT})*		  {		
												char *var = yytext + 8;
												double val = sym.vals[disp(var)];
												printf("%f\n",val);
										  }
{ALPHA}({ALPHA}|{DIGIT})*  				  {
											yylval = disp(yytext);
											return VAR; 
										  }
{DIGIT}+(\.{DIGIT}+)?              {yylval = atof(yytext); return NUM;}
[ \t]	;
">="	{return GE;}
"<="	{return LE;}
"!="	{return NE;}
"=="	{return EQ;}
.|\n       {return yytext[0];}
%% 
int yywrap(void){
	return 1;
} 
