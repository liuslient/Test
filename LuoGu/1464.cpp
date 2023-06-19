#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;
//歧义化搜索
long long rem[30][30][30]={0};

long long w(long long a,long long b,long long c){
    
    if(a<=0||b<=0||c<=0){
        return 1;
    }
    else if(a>20||b>20||c>20){
        return w(20,20,20);
    }
    else if(rem[a][b][c]){
        return rem[a][b][c];
    }
    else if(a<b&&b<c){
        return rem[a][b][c]=w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
    }
    else{
        return rem[a][b][c]=w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
    }

}

int main()
{
    long long a,b,c;
    while(1){
        cin>>a>>b>>c;
        if(a==-1&&b==-1&&c==-1){
            return 0;
        }
        cout<<"w("<<a<<", "<<b<<", "<<c<<") = "<<w(a,b,c)<<endl;
    }

    
}