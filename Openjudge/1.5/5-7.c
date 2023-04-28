#include<stdio.h>
int main()
{
    int i,n,jin,yin,tong,jin_s=0,yin_s=0,tong_s=0,sum=0;
    scanf("%d",&n);
    for (i = 0; i < n; i++)
    {
        scanf("%d %d %d",&jin,&yin,&tong);
        jin_s+=jin;
        yin_s+=yin;
        tong_s+=tong;
        sum=jin_s+yin_s+tong_s;
    }
    printf("%d %d %d %d",jin_s,yin_s,tong_s,sum);
}