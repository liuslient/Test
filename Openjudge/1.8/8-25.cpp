#include<bits/stdc++.h> 
using namespace std;
int m[25][25];
bool m1[25][25];
char l[405];
int row,col,y,len,ans = 0;
void change(int n,int p){
	int s = p-4;
	while(p>=s){
		l[p] = n%2+0x30;
		n/=2;
		p--;
	}
}
bool pd(int x,int y){
	if(m1[x-1][y]&&m1[x][y-1]&&m1[x+1][y]&&m1[x][y+1]&&x-1>=0&&x+1<row&&y-1>=0&&y+1<col){
		return true;
	}else{
		return false;
	}
}
void fill(){
	int x = 0,y = 0;
	len*=5;
	while(ans!=len){
		if(pd(x,y)){
			m[x][y] = l[ans]-0x30;
			break;
		}
		while(!m1[x][y+1]&&y+1<col){
			m[x][y] = l[ans]-0x30;
			ans++;
			m1[x][y] = true;
			y++;
			if(ans == len){
				break;
			}
		}
		if(ans == len){
			break;
		}
		while(!m1[x+1][y]&&x+1<row){
			m[x][y] = l[ans]-0x30;
			ans++;
			m1[x][y] = true;
			x++;
			if(ans == len){
				break;
			}
		}
		if(ans == len){
			break;
		}
		while(!m1[x][y-1]&&y>0){
			m[x][y] = l[ans]-0x30;
			ans++;
			m1[x][y] = true;
			y--;
			if(ans == len){
				break;
			}
		}
		if(ans == len){
			break;
		}
		while(!m1[x-1][y]&&x>0){
			m[x][y] = l[ans]-0x30;
			ans++;
			m1[x][y] = true;
			x--;
			if(ans == len){
				break;
			}
		}
		if(ans == len){
			break;
		}
	}
}
int main(){
	int k[400] = {0};
	cin>>row>>col;
	while(1){
		char a = getchar();
		if(a == '\n'){
			break;
		}else{
			if(a == ' '){
				if(len == 0){
					continue;
				}
				k[len] = 0; 
			}else{
				k[len] = a-'A'+1;
			}
			len++;
		}
	} 
	int p = 4;
	for(int i = 0;i<len;i++){
		change(k[i],p);
		p+=5;
	}
	fill();
	for(int i = 0;i<row;i++){
		for(int j = 0;j<col;j++){
			cout<<m[i][j];
		}
	}
	return 0;
}
