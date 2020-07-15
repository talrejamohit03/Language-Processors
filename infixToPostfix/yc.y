%{ 
	#include <stdio.h> 
	#include <stdlib.h> 
%} 

%token ID 
%left '+' '-'
%left '*' '/'
%right '@' 
%left UMINUS

%% 

S : E 
E : E'+'{A1();}T{A2();} 
| E'-'{A1();}T{A2();} 
| T 
; 
T : T'*'{A1();}G{A2();} 
| T'/'{A1();}G{A2();} 
| G 
; 
G : F'@'{A1();}G{A2();}
| F
; 
F : '('E{A2();}')'
| '-'F %prec UMINUS{printf("um");} 
| ID{A3();} 
; 

%% 

#include"lex.yy.c" 
char st[100]; //stack of operators
int top=0; 

int main(){ 
	printf("Enter infix expression: "); 
	yyparse(); 
	printf("\n"); 
	return 0; 
} 
A1(){ 
	st[top++]=yytext[0]; 
} 

A2(){ 
	printf("%c", st[--top]); 
} 

A3(){ 
	printf("%c", yytext[0]); 
} 

