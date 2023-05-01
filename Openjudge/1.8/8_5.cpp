#include <iostream>
using namespace std;
int main()
{
    int a[5][5], n=5, i, j;
    for (i=0; i<5; i++)
        for (j=0; j<5; j++)
            cin >> a[i][j];
    bool flag = 0;
    int row, col;
    for (row=0; row<n; row++)
    {
        col = 0;
        for (j=1; j<n; j++)
        {
            if (a[row][j] > a[row][col])
                col = j;
        }
        flag = 1;
        for (i=0; i<n; i++)
        {
            if (a[i][col] < a[row][col])
            {
                flag = 0;
                break;
            }
        }
        if (flag) 
            break;
    }
    if (flag)
        cout << row+1 << " " << col+1 << " " << a[row][col] << endl;
    else
        cout << "not found" << endl;
    return 0;
}