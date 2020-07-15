//lexical analyser to find keywords, identifiers, operators and separators in a c/c++ file

#include<bits/stdc++.h>
using namespace std;

void display(set<string> s){
	set<string>::iterator it;
	for(it=s.begin();it!=s.end();it++){
		cout<<*it<<" ";
	}
}
void display(set<char> s){
	set<char>::iterator it;
	for(it=s.begin();it!=s.end();it++){
		cout<<*it<<" ";
	}
}
int main(int argc, char *argv[]){
	ifstream fin;
	fin.open(argv[1]);
	set<string> keys;
	set<char> seps,ops;
	keys.insert("auto");
	keys.insert("break");
	keys.insert("case");
	keys.insert("char");
	keys.insert("const");
	keys.insert("continue");
	keys.insert("default");
	keys.insert("do");
	keys.insert("double");
	keys.insert("else");
	keys.insert("enum");
	keys.insert("extern");
	keys.insert("float");
	keys.insert("for");
	keys.insert("goto");
	keys.insert("if");
	keys.insert("int");
	keys.insert("long");
	keys.insert("register");
	keys.insert("return");
	keys.insert("short");
	keys.insert("signed");
	keys.insert("sizeof");
	keys.insert("static");
	keys.insert("struct");
	keys.insert("switch");
	keys.insert("typedef");
	keys.insert("union");
	keys.insert("unsigned");
	keys.insert("void");
	keys.insert("volatile");
	keys.insert("while");
	
	ops.insert('+');
	ops.insert('-');
	ops.insert('*');
	ops.insert('/');
	ops.insert('>');
	ops.insert('<');
	ops.insert('.');
	ops.insert('=');
	ops.insert('!');
	ops.insert('%');
	ops.insert(':');
	
	seps.insert('{');
	seps.insert(' ');
	seps.insert('}');
	seps.insert('(');
	seps.insert(')');
	seps.insert('[');
	seps.insert(']');
	seps.insert(';');
	seps.insert('\"');
	seps.insert('\'');
	seps.insert('\\');
	seps.insert('\n');
	seps.insert('\t');
	seps.insert(',');
	seps.insert('#');
	
	string word;
	set<string> ckeys,cops,ids;
	set<char> cseps;
	char ch;
	fin.get(ch);
	while(!fin.eof()){
		if(seps.find(ch)!=seps.end()){
			cseps.insert(ch);
			if(ch=='\"'){
				fin.get(ch);
				while(ch!='\"')
					fin.get(ch);
			}else if(ch=='\''){
				fin.get(ch);
				while(ch!='\'')
					fin.get(ch);
			}
			if(keys.find(word)!=keys.end()){
				ckeys.insert(word);
			}else{
				int i=0;
				for(i;i<word.length();i++){
					if(isalpha(word[i]))
						break;
				}
				if(i<word.length())
					ids.insert(word);
			}
			word="";
		}else if(ops.find(ch)!=ops.end()){
			string op;
			op.push_back(ch);
			fin.get(ch);
			if(!fin.eof() && ops.find(ch)!=ops.end()){
				op.push_back(ch);
			}
			cops.insert(op);
			if(keys.find(word)!=keys.end()){
				ckeys.insert(word);
			}else{
				int i=0;
				for(i;i<word.length();i++){
					if(isalpha(word[i]))
						break;
				}
				if(i<word.length())
					ids.insert(word);
			}
			word="";
			continue;
		}else{
			word.push_back(ch);
		}
		fin.get(ch);	
	}
	cout<<"Keywords: ";
	display(ckeys);
	cout<<"\n";
	cout<<"Operators: ";
	display(cops);
	cout<<"\n";
	cout<<"Separators: ";
	display(cseps);
	cout<<"\n";
	cout<<"Identifiers: ";
	display(ids);
	cout<<"\n";
	return 0;
}
