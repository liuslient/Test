#include<bits/stdc++.h>
using namespace std;
int stb[10][5] = {{1,3,0,3,1},{0,2,0,2,0},{1,2,1,1,1},{1,2,1,2,1},{0,3,1,2,0},{1,1,1,2,1},{1,1,1,3,1},{1,2,0,2,0},{1,3,1,3,1},{1,3,1,2,1}};
int odd(int a){
	return a%2; // 判断一个数是否为奇数 
} 
void draw(int a,int b,int size){
	if(stb[a][b] == 1){
		if(!odd(b)){
			cout << ' ';
			for(int j =0;j<size;j++){
				cout << '-';
			}
			cout << ' ';
		}
		else{
			cout << '|';
			for(int j=0;j<size;j++){
				cout << ' ';
			} 
			cout << ' ';
		}
	}
	if(stb[a][b] == 2){
		cout << ' ';
		for(int j=0;j<size;j++){
			cout << ' ';	
		}
		cout << '|';
	}
	if(stb[a][b] == 3){
		cout << '|';
		for(int j=0;j<size;j++){
			cout << ' ';	
		}
		cout << '|';
	}
	if(stb[a][b]  == 0){
		cout << ' ';
		for(int j=0;j<size;j++){
			cout << ' ';	
		}
		cout << ' ';
	}
	cout << ' '; 
}
int k;
string s;
int main(){
	cin >> k;
	cin >> s;

	for(int i = 0;i<5;i++){
		for(int j = 0;j < (!odd(i)?1:k);j++){
			for(int x= 0;x<s.length();x++){
				draw(s[x]-48,i,k);
			} 
			cout << endl;
		}
		
	} 
	
	return 0;
}
