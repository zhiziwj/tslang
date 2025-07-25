#ifndef func_h
#define func_h
#include <bits/stdc++.h>
long long int rand_(int l,int r){
	return rand()%(r-l+1)+l;
}
inline void output_str(std::string str){
	std::cout<<str;
}
inline void output_num(long long int num){
	std::cout<<num;
}
long long int input(){
	long long int temp;
	std::cin>>temp;
	return temp;
}
#endif
