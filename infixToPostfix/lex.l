
%{ 
  /* Lex program for converting infix to postfix */
%} 
ALPHA [A-Z a-z] 
DIGIT [0-9] 

%% 
{ALPHA}({ALPHA}|{DIGIT})*  return ID; 
{DIGIT}+                   {yylval=atoi(yytext); return ID;} 
[\n \t]                    yyterminate(); 
.                          return yytext[0]; 
%% 

