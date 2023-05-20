#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n%4==0)
    {
        if (n% 100 == 0 && n % 400 != 0)
		{
			printf("N");
		}
		else if (n % 3200 == 0)
		{
			printf("N");
		}
		else
		{
			printf("Y");
        }
        
    }
    else
    {
        cout<<"N";
    }
    
}