%{ 
	#include <stdio.h> 
	#include <stdlib.h> 
	#include <math.h>
	#include <string.h>
	#define YYSTYPE double
	struct symtable{
		char vars[10][20];
		double vals[10];
		int cnt;
	};
	struct symtable sym;
	int disp(char *str){
		for(int i=0;i<sym.cnt;i++){
			if(strcmp(str,sym.vars[i])==0)
				return i;
		}
	}
	void let(char *str){
		strcpy(sym.vars[sym.cnt],str);
		sym.vals[sym.cnt] = 0.0;
		sym.cnt++;
	}
%} 
%union{
	double n;
	char str[20];
}
%token NUM VAR GE LE NE EQ
%right '=' 
%left '+' '-'
%left '*' '/'
%right '@' 
%left UMINUS

%% 

S : E '\n'{printf("Result: %f\n",$$);}
  | VAR '=' E {sym.vals[(int)$1] = $3;}
  ;
E : E '+' T {$$ = $1+$3;}
  | E '-' T {$$ = $1-$3;} 
  | T {$$ = $1;}
  ; 
T : T '*' G {$$ = $1*$3;} 
  | T '/' G {$$ = $1/$3;} 
  | G  {$$ = $1;}
  ; 
G : F '@' G {$$ = $3;}
  | F {$$ = $1;}
  ; 
F : '('E')' {$$ = $2;}
  | '-' F %prec UMINUS{$$ = -$2;} 
  | NUM {$$ = $1;} 
  | VAR {$$ = sym.vals[(int)$1];}
  ; 

%% 

int main(){
	//yydebug = 1;
	yyparse(); 
	return 0; 
} 

