#include<stdio.h>
int main()
{
    char c;
    int d=100,x=0,n=50;
    printf("数字是50吗?是填Y不是填N:");
    scanf("%c", &c);
    getchar();
    while (c!='Y')
    {
        printf("你猜的数字是否大于所显示的数字?是填D不是填X:");
        scanf("%c", &c);
        getchar();
        if (c=='D')
        {
            x=n;
            n=(x+d) / 2;
        }
        else
        {
            d=n;
            n=(x+d) / 2;
        }
        printf("数字是%d吗?是填Y不是填N:",n);
        scanf("%c", &c);
        getchar();
    }
    printf("结束\n");
}

