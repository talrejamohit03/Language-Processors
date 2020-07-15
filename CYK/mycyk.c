//CYK algorithm implementation to check whether it can be derived from the grammar in CNF input to the program

#include<stdio.h>
#include<string.h>

#define MAX 20
char grammar[MAX][MAX];
int main(){
	/*
	char s[]="abcdegfh";
	char s2[]="cde";
	char *sub=strstr(s,s2);
	printf("%s\n",sub);
	*/
	printf("Enter #productions: ");
	int p;
	scanf("%d",&p);
	printf("Enter grammar: \n");
	for(int i=0;i<p;i++)
		scanf("\n%s",&grammar[i]);
		//fgets(grammar[i],MAX,stdin);
	char check[MAX];
	printf("Enter string: \n");
	//fgets(check,MAX,stdin);
	scanf("\n%s",&check);
	//printf("%s is entered string\n",check);
	int n=strlen(check);
	char X[n][n][MAX];
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++)
			X[i][j][0]='\0';
	}
	
	
	for(int i=0;i<n;i++){
		char curr=check[i];
		//printf("%c ",check[i]);
		for(int j=0;j<p;j++){
			char *alpha=strstr(grammar[j],"->");
			int k=2;
			while(k<strlen(alpha)){
				if(alpha[k]==curr && (k==strlen(alpha)-1||alpha[k+1]=='|')){
					strncat(X[i][i],&grammar[j][0],1);
				}
				k++;
			}
		}
	}
	for(int len=2;len<=n;len++){
		for(int i=0;i<(n-len+1);i++){
			int j=i+len-1;
			for(int k=i;k<=j;k++){
				for(int it1=0;it1<strlen(X[i][k]);it1++){
					char ser[3];
					ser[2]='\0';
					ser[0]=X[i][k][it1];
					for(int it2=0;it2<strlen(X[k+1][j]);it2++){
						ser[1]=X[k+1][j][it2];
						for(int g=0;g<p;g++){
							if(strstr(grammar[g],ser)!=NULL){
								strncat(X[i][j],&grammar[g][0],1);
								/*
								int h=0;
								for(h;h<strlen(X[i][j]);h++){
									if(X[i][j][h] == grammar[g][0])
										break;
								}
								if(h==strlen(X[i][j]))
									strncat(X[i][j],&grammar[g][0],1);
								*/
							}
						}
						
					}
				}
			}
		}
	}
	if(strstr(X[0][n-1],"S")!=NULL)
		printf("This string belongs to the grammar\n");
	else
		printf("This string does not belong to the grammar\n");
	int cnt=0;
	for(int i=0;i<strlen(X[0][n-1]);i++){
		if(X[0][n-1][i]=='S')
			cnt++;
	}
	printf("number of non-identical derivations = %d\n",cnt);
	for(int len=1;len<=n;len++){
		for(int i=0;i<(n-len+1);i++){
			int j=i+len-1;
			if(strcmp(X[i][j],"\0")!=0)
				printf("%s ",X[i][j]);
			else
				printf("    ");
		}
		printf("\n");
	}
	return 0;
}
