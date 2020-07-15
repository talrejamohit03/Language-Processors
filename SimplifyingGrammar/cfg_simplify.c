#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int n=10;

void initialize(char G[26][n][10],int G_cnt[]){
	for(int i=0;i<26;i++){
		G_cnt[i]=0;
		for(int j=0;j<10;j++)
			strcpy(G[i][j],"");
	}
}

int present(char G[n][10],char x[10],int l){
	for(int i=0;i<l;i++){
		if(strcmp(x,G[i])==0)
			return 1;
	}
	return 1;
}

void print_grammer(char G[26][n][10],int G_cnt[],int s){
	printf("%c -> ",s+'A');
	for(int i=0;i<G_cnt[s];i++)
	{
		printf("%s ",G[s][i]);
		if(i!=G_cnt[s]-1)
			printf("| ");
	}
	printf("\n");
	
	for(int j=0;j<26;j++){
		if(j!=s&&G_cnt[j]>0){
			printf("%c -> ",j+'A');
			for(int i=0;i<G_cnt[j];i++)
			{
				printf("%s ",G[j][i]);
				if(i!=G_cnt[j]-1)
					printf("| ");
			}
			printf("\n");
		}
	}
}

int same(bool g[26],bool p[26]){
	for(int i=0;i<26;i++)
		if(g[i]!=p[i])
			return 0;
	return 1;
}

void copy(char G[26][n][10],int G_cnt[26],char t[26][n][10],int t_cnt[26]){
	initialize(G,G_cnt);
	for(int i=0;i<26;i++){
		G_cnt[i]=t_cnt[i];
		for(int j=0;j<t_cnt[i];j++)
			strcpy(G[i][j],t[i][j]);
	}
}

void rm_nongen(char G[26][n][10],int G_cnt[26],int s){
	bool gen[26],prev[26];
	for(int i=0;i<26;i++)
	{	
		gen[i]=0;prev[i]=0;
		for(int j=0;j<G_cnt[i];j++){
			int x=0;
			for(int k=0;k<strlen(G[i][j]);k++){
				if(!(G[i][j][k]>='A'&&G[i][j][k]<='Z'))
					x+=1;
			}
			if(x==strlen(G[i][j]))
			{	gen[i]=1;break;}
		}
	}
	
	while(same(gen,prev)!=1){
		for(int i=0;i<26;i++)
			prev[i]=gen[i];
		for(int i=0;i<26;i++)
		{	
			for(int j=0;j<G_cnt[i]&&(!gen[i]);j++){
				int x=0;
				for(int k=0;k<strlen(G[i][j]);k++){
					if(!(G[i][j][k]>='A'&&G[i][j][k]<='Z'))
						x+=1;
					else if(gen[G[i][j][k]-'A'])
						x+=1;
				}
				if(x==strlen(G[i][j]))
				{	gen[i]=1;break;}
			}
		}
	}
	
	char temp[26][n][10];
	int temp_cnt[26];
	initialize(temp,temp_cnt);
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<G_cnt[i]&&gen[i];j++){
			int x=0;
			for(int k=0;k<strlen(G[i][j]);k++){
				if(!(G[i][j][k]>='A'&&G[i][j][k]<='Z'))
					x+=1;
				else if(gen[G[i][j][k]-'A'])
					x+=1;
			}
			if(x==strlen(G[i][j]))
			{
				strcpy(temp[i][temp_cnt[i]],G[i][j]);
				temp_cnt[i]++;
			}
		}
	}
	copy(G,G_cnt,temp,temp_cnt);
}


void rm_nonreach(char G[26][n][10],int G_cnt[26],int s){
	bool reach[26],prev[26];
	for(int i=0;i<26;i++)
	{	
		reach[i]=0;prev[i]=0;
	}
	reach[s]=1;
	while(same(reach,prev)!=1){
		for(int i=0;i<26;i++)
			prev[i]=reach[i];
		for(int i=0;i<26;i++)
		{	
			for(int j=0;j<G_cnt[i]&&reach[i];j++){
				int x=0;
				for(int k=0;k<strlen(G[i][j]);k++){
					if(G[i][j][k]>='A'&&G[i][j][k]<='Z')
						reach[G[i][j][k]-'A']=1;
				}
			}
		}
	}
	
	char temp[26][n][10];
	int temp_cnt[26];
	initialize(temp,temp_cnt);
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<G_cnt[i]&&reach[i];j++){
			int x=0;
			for(int k=0;k<strlen(G[i][j]);k++){
				if(!(G[i][j][k]>='A'&&G[i][j][k]<='Z'))
					x+=1;
				else if(reach[G[i][j][k]-'A'])
					x+=1;
			}
			if(x==strlen(G[i][j]))
			{
				strcpy(temp[i][temp_cnt[i]],G[i][j]);
				temp_cnt[i]++;
			}
		}
	}
	copy(G,G_cnt,temp,temp_cnt);

}

void rm_useless(char G[26][n][10],int G_cnt[26],int s){
	rm_nongen(G,G_cnt,s);
	printf("After removing non generating symbols\n");
	print_grammer(G,G_cnt,s);
	rm_nonreach(G,G_cnt,s);
	printf("After removing non reachable symbols\n");
	print_grammer(G,G_cnt,s);
}


void add(char G[26][n][10],int G_cnt[26],char t[n][10],int t_cnt,int i){
	for(int j=0;j<t_cnt;j++){
		int x=G_cnt[i];
		if(present(G[i],t[j],G_cnt[i])==0)
		{	strcpy(G[i][x],t[j]);
			G_cnt[i]+=1;
		}
	}
}

void rm_unitproc(char G[26][n][10],int G_cnt[26]){
	char up[26][10];
	char t[26][n][10];
	int t_cnt[26];
	initialize(t,t_cnt);
	for(int i=0;i<26;i++){
		strcpy(up[i],"");
		for(int j=0;j<G_cnt[i];j++){
			if(strlen(G[i][j])==1&&(G[i][j][0]>='A'&&G[i][j][0]<='Z'))
				strcat(up[i],G[i][j]);	
			else{
				strcpy(t[i][t_cnt[i]],G[i][j]);
				t_cnt[i]++;
			}
		}
	}
	copy(G,G_cnt,t,t_cnt);
	char x[20]="";
	bool v[26];
	for(int i=0;i<26;i++){
		for(int k=0;k<26;k++)
			v[k]=0;
		strcpy(x,"");
		if(strlen(up[i])>0){
			int j=0;
			v[i]=1;
			strcpy(x,up[i]);
			while(j<strlen(x)){
				if(!v[x[j]-'A']){
					add(G,G_cnt,t[x[j]-'A'],t_cnt[x[j]-'A'],i);
					v[x[j]-'A']=1;
					strcat(x,up[x[j]-'A']);
				}
				j++;
			}
		}
	}
}

void add_end(char G[26][n][10],int G_cnt[26],int Gi,int Gj,int Gk){
	char x[10]="";
	int i=0,j=0;
	for(i=0;i<strlen(G[Gi][Gj]);i++){
		if(i!=Gk)
		{	x[j]=G[Gi][Gj][i];
			j++;
		}
	}
	x[i-1]='\0';
	//printf("x=%s\n",x);
	if(strlen(x)==0)
		return;
	i=G_cnt[Gi];
	if(present(G[Gi],x,G_cnt[Gi])==0){
		strcpy(G[Gi][i],x);
		G_cnt[Gi]+=1;
	}

}

int rm_nullproc(char G[26][n][10],int G_cnt[26],int s){
	bool nullable[26],prev[26];
	for(int i=0;i<26;i++)
	{	nullable[i]=0;prev[i]=0;}
	do{
		for(int i=0;i<26;i++)
			prev[i]=nullable[i];
		for(int i=0;i<26;i++){
			for(int j=0;j<G_cnt[i]&&nullable[i]==0;j++){
				int k=0;
				for(k=0;k<strlen(G[i][j]);k++){
					if(strcmp(G[i][j],"#")==0){
						nullable[i]=1;
						G_cnt[i]-=1;break;
					}
					else if(!(G[i][j][k]>='A'&&G[i][j][k]<='Z'))
						break;
					else if(nullable[G[i][j][k]-'A']==0)
						break;
				}
				if(k==strlen(G[i][j]))
					nullable[i]=1;
			}
		}
	}while(same(nullable,prev)!=1);
	
	printf("Nullable\n");
	int x=0;
	for(int i=0;i<26;i++)
		if(nullable[i]){ printf("%c",i+'A');x=1;}
	printf("\n");
	if(x==0)
		return 0;
	
	for(int i=0;i<26;i++){
		for(int j=0;j<G_cnt[i];j++){
			for(int k=0;k<strlen(G[i][j]);k++){
				int x=G[i][j][k]-'A';
				if(x>=0&&x<=25&&nullable[x]==1){
					//printf("adding %c to %c\n",x+'A',i+'A');
					add_end(G,G_cnt,i,j,k);
				}
			}
		}
	}
	if(nullable[s]==1)
		return 1;
	else
		return 0;
}

int main(){
	char G[26][n][10];
	int G_cnt[26],np;
	char S,str[100];
	
	initialize(G,G_cnt);
	
	printf("Enter start symbol : ");
	scanf("%c",&S);
	
	printf("Enter no of productions :");
	scanf("%d",&np);
	
	for(int i=0;i<np;i++){
		bzero(str,100);
		scanf("%s",str);
		char *y;
		y=strtok(str,"-");
		int v=str[0]-'A';
		char *tok=strtok(NULL,"|");
		tok++;
		int j=0;	
		while(tok){
			strcpy(G[v][j],tok);
			j++;
			tok=strtok(NULL,"|");
		}
		G_cnt[v]=j;
	}
	
	int s=S-'A';
	
	printf("After removing null productions\n");
	int flag=rm_nullproc(G,G_cnt,s);
	print_grammer(G,G_cnt,s);
	
	printf("After removing unit productions\n");
	rm_unitproc(G,G_cnt);
	print_grammer(G,G_cnt,s);
	
	rm_useless(G,G_cnt,s);
	printf("After removing useless symbols\n");
	print_grammer(G,G_cnt,s);
	
	if(flag==1){
		strcpy(G[s][G_cnt[s]],"#");
		G_cnt[s]+=1;
	}
	printf("Final Grammer\n");
	print_grammer(G,G_cnt,s);
	return 0;
}
