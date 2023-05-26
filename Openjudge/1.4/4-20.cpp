#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    double a, b, c, x1, x2, bb, fourac, twoa;
    cin >> a >> b >> c;
    bb = b*b;
    fourac = 4*a*c;
    twoa = -b/(a*2);
    if (b == 0) twoa = 0;
    if (bb == fourac) {
        cout << fixed << setprecision(5) << "x1=x2=" << twoa << endl;
    }
    else if (bb > fourac) {
        x1 =  (-b + sqrt(b*b-4*a*c))/(2*a);
        x2 =  (-b - sqrt(b*b-4*a*c))/(2*a);
        cout << fixed << setprecision(5) << "x1=" << x1 << ";x2="
             << fixed << setprecision(5)<< x2 << endl;
    }
    else {
        cout << fixed << setprecision(5) << "x1=" << twoa << "+"
             << fixed << setprecision(5)<< sqrt(fourac-bb)/(a*2) << "i;x2="
             << fixed << setprecision(5) << twoa << "-"
             << fixed << setprecision(5) << sqrt(fourac-bb)/(a*2) << "i" << endl;
    }
    return 0;
}



/*
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
int main()
{
    double a,b,c;
    cin>>a>>b>>c;
    if (b*b<4*a*c)
    {
        cout<<"x1="<<fixed<<setprecision(5)<<-b / (2*a)<<"+"<<sqrt(4*a*c-b*b) / (2*a)<<"i"<<";";
        cout<<"x2="<<fixed<<setprecision(5)<<-b / (2*a)<<"-"<<sqrt(4*a*c-b*b) / (2*a)<<"i";
    }
    if (b*b>4*a*c)
    {
        cout<<"x1="<<fixed<<setprecision(5)<<(-1*b+sqrt(b*b-4*a*c))/(2*a)<<";";
        cout<<"x2="<<fixed<<setprecision(5)<<(-1*b-sqrt(b*b-4*a*c))/(2*a);
    }
    if (b*b==4*a*c)
    {
        cout<<"x1=x2="<<fixed<<setprecision(5)<<(-1*b+sqrt(b*b-4*a*c))/(2*a);
    }
    

}
*/