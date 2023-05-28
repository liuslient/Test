#include<iostream>
#include<math.h>
#include<algorithm>

using namespace std;
int main()
{
    int n, m, i, x, y, mid, target;
    int a[100000]; 
    cin >> n;
    for (i=0; i<n; i++) cin >> a[i];
    cin >> m;
    for (i=0; i<m; i++){
        cin >> target;
        x = 0;
        y = n-1;
        while ((y-x) > 1){
            mid = (y-x) / 2 + x;
            if (a[mid] == target){
                x = y = mid;
            }
            else{
                if (a[mid] > target)
                    y = mid;
                else
                    x = mid;
            }
        }
        if (x == y) cout << a[x] << endl;
        else {
            if ((target-a[x]) <= (a[y]-target))
                cout << a[x] << endl;
            else
                cout << a[y] << endl;
        }
    }
}

/*
int main()
{
    int n,m,i,j;
    cin>>n;
    int a[n+10];
    for ( i = 0; i < n; i++)
    {
        cin>>a[n];
    }
    cin>>m;
    while(m--)
    {
        int x;
        cin>>x;
        int L=0,R=n-1;
        int ans=-1;
        while (L<=R)
        {
            int mid=(L+R)/2;
            if (a[mid]==x)
            {
                ans=mid;
                break;
            }
            else if (a[mid]>x)
            {
                R=mid-1;
            }
            else
            {
                L=mid+1;
            }
        }
        if (ans!=-1) cout<<a[ans]<<endl;
        else
        {
            if (R==-1) cout<<a[L]<<endl;
            else if (L==n)
            {
                cout<<a[R]<<endl;
            }
            else{
                if(x-a[R]<=a[L]-x)
                {
                    cout<<a[R]<<endl;
                }
                else
                {
                    cout<<a[L]<<endl;
                }
            }
        } 
    }
}
*/