#ifndef count_h
#define count_h
#include <bits/stdc++.h> //lol
using std::string;//lol*2
using std::stack;
std::map<char,long long int> var;
inline bool check_var(char x){
	if(x>='a'&&x<='z'||x>='A'&&x<='Z'){
		return true;
	}
	return false;
}
inline bool check_opa(char x){
	if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x=='&'||x=='|'||x=='^'){
		return true;
	}
	return false;
}
long long int connect(long long int a,char ch,long long int b){
	switch(ch){
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;//if b=0 -> nan inf
		case '%':
			return a%b;
		case '&':
			return bool(a&&b);
		case '|':
			return bool(a||b);
		case '^':
			return bool(a^b);
		default:
			std::cout<<"wrong"<<std::endl; 
	}
	return 0;
}
long long int num(string str){
	long long int cnt=0;
	bool flag=false;
	if(str[0]=='-'){
		flag=true;
	}
	for(int i=0;i<str.length();i++){
		if(str[i]=='-'){
			continue;
		}
		cnt=cnt*10+(str[i]-'0');
	}
	if(flag){
		cnt=-cnt;
	}
	return cnt;
}
long long int count(string str){
	if(str[str.size()-1]!=' '){
		str+=" ";
	}
	string temp;
	stack<long long int> st;
	for(int i=0;i<str.length();i++){
		if(check_opa(str[i])&&str[i+1]==' '){
			long long int a=st.top();
			st.pop();
			long long int b=st.top();
			st.pop();
			st.push(connect(b,str[i],a));
		}
		else if(str[i]==' '){
			if(check_var(str[i-1])){
				st.push(var[str[i-1]]);
				temp="";
			}
			else if(str[i-1]>='0'&&str[i-1]<='9'){
				st.push(num(temp));
				temp="";
			}
		}
		else{
			temp+=str[i];
		}
	} 
	return st.top();
}
#endif
