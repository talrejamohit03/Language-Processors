
%{ 
  /* Lex program to encrypt words */
  #include<stdio.h>
  #include<stdlib.h>
  #define MAX 50
  char *special[] = {"hello", "my","name","is","mohit"};
  int nspec = 5, k = 3;
  FILE *out;
  void swap(char *i, char *j){
  		char tmp = *i;
  		*i = *j;
  		*j = tmp;
  }
  void reverse(char str[]){
  	  int i = 0, j = strlen(str)-1;
  	  while(i<j){
  	  		swap(&str[i],&str[j]);
  	  		i++;j--;
  	  }
  	  
  }
%} 
ALPHA [a-zA-Z] 
DIGIT [0-9] 

%% 
{ALPHA}+  				   {
							int f = 0;
							for(int i=0;i<nspec;i++){
								if(strcmp(yytext,special[i]) == 0)
									f = 1;
							}
							char oword[MAX];
							int j = 0, l = strlen(yytext);
							if(f){
								oword[j++] = yytext[l-1];
								oword[j++] = yytext[l-2];
								int i = 0;
								while(i<l-2)
									oword[j++] = yytext[i++];
								oword[j] = '\0';
								reverse(oword);
							}else{
								for(int i=0;i<l;i++){
									oword[i] = (char) (((int)yytext[i] + k)%256);
								}
								reverse(oword);
							}
							fprintf(out,"%s",oword);
								 
							} 
{DIGIT}+                   {
								int n = strlen(yytext);
								char oword[MAX];
								strcpy(oword,yytext);
								int l = 0, r = (n & 1)? (n/2 + 1) : (n/2);
								while(r<n){
									swap(&oword[l++],&oword[r++]);
								}
								fprintf(out,"%s",oword);
							} 
[\n \t]                    fprintf(out," ");
.                          ; 
%% 

FILE *yyin;
int main(){
	yyin = fopen("input.txt","r");
	out = fopen("output.txt","w");
	yylex();
}
