//Simplifying grammar by removing useless productions, NULL productions, unit productions, immediate left recursion
/*
	Author: mohit_talreja
	NITW,CSE
*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>
#define MAX 20
char grammar[26][MAX][MAX];
int gcnt[26]={0};
int p;
void printGr(){
	for(int i=0;i<26;i++){
		if(gcnt[i]>0){
			printf("%c -> ", (i+'A'));
			for(int j = 0;j<gcnt[i]-1; j++){
				printf("%s | ", grammar[i][j]);
			}
			printf("%s\n",grammar[i][gcnt[i]-1]);
		}
	}
}
void printGrLeft(){
	for(int i=0;i<26;i++){
		if(gcnt[i]>0){
			printf("%c -> ", (i+'A'));
			for(int j = 0;j<gcnt[i]-1; j++){
				if(grammar[i][j][0] != i+'A')
					printf("%s | ", grammar[i][j]);
			}
			if(grammar[i][gcnt[i]-1][0] != i+'A')
				printf("%s\n",grammar[i][gcnt[i]-1]);
		}
	}
}
void delGr(char c){
	char ngrammar[26][MAX][MAX];
	int ngcnt[26] = {0};
	for(int i=0;i<26;i++){
		if(gcnt[i]>0){
			for(int j = 0; j < gcnt[i]; j++){
				int k = 0;
				while(k<strlen(grammar[i][j]) && grammar[i][j][k] != c)
					k++;
				if(k == strlen(grammar[i][j])){
					strcpy(ngrammar[i][ngcnt[i]++],grammar[i][j]);
				}
			}
		}
	}
	for(int i = 0;i < 26;i++){
		gcnt[i] = ngcnt[i];
		for(int j = 0;j<gcnt[i];j++){
			strcpy(grammar[i][j],ngrammar[i][j]);
		}
	}
}
void delGrHelp(bool newv[]){
	for(int i=0;i<26;i++){
		if(!newv[i] && gcnt[i] > 0){
			gcnt[i] = 0;
			delGr(i+'A');
			p--;
		}
	}
}
void genProd(int pos, char str[], int idx, bool bits[],int n){
	if(idx == strlen(str))
		return;
	int j = 0;
	char curr[MAX];
	for(int i=0;i<n;i++){
		if(bits[i])
			curr[j++] = str[i];
	}
	curr[j] = '\0';
	//printf("curr = %s \n",curr);
	if(strlen(curr) > 0 && strlen(curr) <= strlen(str)-1){
		int pres = 0;
		for(pres;pres<gcnt[pos];pres++){
			if(strcmp(grammar[pos][pres], curr)==0)
				break;
		}
		if(pres == gcnt[pos]){
			strcpy(grammar[pos][gcnt[pos]],curr);
			gcnt[pos]++;
		}
	}
	for(int i=idx+1;i<n;i++){
		if(!bits[i]){
			bits[i] = 1;
			genProd(pos,str,i,bits,n);
			bits[i] = 0;
		}
	}
}

void appendProd(int i, int j, int rep){
	strcpy(grammar[i][rep],grammar[j][0]);
	for(int k=1;k<gcnt[j];k++){
		strcpy(grammar[i][gcnt[i]++],grammar[j][k]);
	}
	
}
void remUnit(int i, bool vis[]){
	vis[i] = 1;
	int n = gcnt[i];
	for(int j=0;j<n;j++){
		if(strlen(grammar[i][j]) == 1 && isupper(grammar[i][j][0])){
			int k = grammar[i][j][0] - 'A';
			if(!vis[k])
				remUnit(k,vis);
			appendProd(i,k,j);
		}
	}
}

int findFillpos(){
	for(int i=0;i<26;i++){
		if(gcnt[i] == 0)
			return i;
	}
}
int main(){
	printf("Enter #productions: ");
	scanf("%d",&p);
	
	//bzero(grammar,MAX);

	for(int i=0;i<26;i++){
		for(int j=0;j<MAX;j++)
			grammar[i][j][0] = '\0';
	}
	
	bool nullable[26] = {0};
	
	printf("Enter grammar: \n");
	for(int i=0;i<p;i++){
		char str[MAX];
		scanf("%s",str);
		int idx = str[0] - 'A';
		char *tok = strtok(str,"->");
		tok = strtok(NULL,"|");
		tok++;
		int j = 0;
		while(tok!=NULL){
			//printf("%s\n",tok);
			strcpy(grammar[idx][j++],tok);
			if(strcmp(tok,"#") == 0){
				nullable[idx] = 1;
			}
			tok = strtok(NULL,"|");
		}
		gcnt[idx] = j;
		//printGr();
		
	}
	printGr();
	//removing non-generating symbols

	bool newv[26]={0}; //set of new non-terminals
	bool f = 1;
	printf("Removing non-generating:\n");
	while(f){
		f = 0;
		for(int i=0;i<26;i++){
			if(gcnt[i] == 0 || newv[i])
				continue;
			int k = 0;
			while(k < gcnt[i]){
				
				int j = 0;
				for(j; j < strlen(grammar[i][k]); j++){
					if(isupper(grammar[i][k][j]) && !newv[grammar[i][k][j]-'A'])
						break;
				}
				if(j==strlen(grammar[i][k])){
					f = 1;
					newv[i] = 1;
					//printf("%c is gen\n",(i+'A'));
					break;
				}
				k++;
			}
		}
	}
	delGrHelp(newv);
	printGr();

	//removing non-reachable symbols
	printf("Removing non-reachable:\n");
	f = 1;
	for(int i=0;i<26;i++)
		newv[i] = 0;
	newv['S'-'A'] = 1; //assuming start variable is given by S
	while(f){
		f = 0;
		for(int i=0;i<26;i++){
			if(!newv[i])
				continue;
			int k = 0;
			while(k < gcnt[i]){
				int j = 0;
				for(j; j < strlen(grammar[i][k]); j++){
					if(isupper(grammar[i][k][j])){
						if(!newv[grammar[i][k][j]-'A'])
							f = 1;
						newv[grammar[i][k][j]-'A'] = 1;
					}
				}
				k++;
			}
		}
	}
	delGrHelp(newv);
	printGr();
	
	printf("Removing Null productions:\n");
	f = 1;
	while(f){
		f = 0;
		for(int i=0;i<26;i++){
			if(nullable[i]){
				//printf("%c is nullable\n",(i+'A'));
				continue;
			}
				
			int k = 0;
			while(k < gcnt[i]){
				int j = 0;
				for(j; j < strlen(grammar[i][k]); j++){
					if(islower(grammar[i][k][j]) || (isupper(grammar[i][k][j]) && !nullable[grammar[i][k][j] - 'A']))
						break;
				}
				if(j==strlen(grammar[i][k])){
					f = 1;
					nullable[i] = 1;
					//printf("%c is nullable\n",(i+'A'));
					break;
				}
				k++;
			}
		}
	}
	for(int i=0;i<26;i++){
		if(!nullable[i]){
			continue;
		}
		int k = 0, it = gcnt[i];
		while(k < it){
			if(strcmp(grammar[i][k],"#") == 0){
				k++;
				continue;
			}
			int n = strlen(grammar[i][k]);
			bool bits[MAX] = {0};
			for(int j = 0; j < n; j++){
				if(islower(grammar[i][k][j]) || (isupper(grammar[i][k][j]) && !nullable[grammar[i][k][j] - 'A']))
					bits[j] = 1;
			}
			//printf("\n%s processing\n",grammar[i][k]);
			genProd(i, grammar[i][k], -1, bits, n);
			
			k++;
		}
	}
	delGr('#');
	printGr();
	printf("Removing Unit productions:\n");
	bool vis[26] = {0};
	for(int i=0;i<26;i++){
		if(!vis[i] && gcnt[i] > 0){
			remUnit(i,vis);
		}
	}
	printGr();
	printf("Removing immediate left recursion:\n");
	for(int i=0;i<26;i++){
		if(gcnt[i] == 0)
			continue;
		bool alpha[MAX]={0}, f = 0;
		for(int j=0;j<gcnt[i];j++){
			if(grammar[i][j][0] == i+'A'){
				alpha[j] = 1;
				f = 1;
			}
		}
		int dash = findFillpos();
		printf("dash for %c is %c\n",i+'A',dash+'A');
		for(int j=0;j<gcnt[i];j++){
			if(alpha[j]){
				int c = 1, c2 = 0;
				char newp[MAX];
				while(c<strlen(grammar[i][j]))
					newp[c2++] = grammar[i][j][c++];
				newp[c2++] = dash + 'A';
				newp[c2] = '\0';
				strcpy(grammar[dash][gcnt[dash]++],newp);
			}else{
				char str[2];
				str[0] = dash+'A';
				str[1] = '\0';
				strcat(grammar[i][j],str);
			}
		}
	}
	printGrLeft();
	return 0;
}
