#include <stdio.h>
void swap(int*pa,int*pb)//整形指针变量，存放变量地址
{
    int temp;10,
    temp = *pa;
    *pa = *pb;
    *pb = temp; 

}
int main()
{
int m, n;
printf("请输入你想交换的值：");
scanf("%d %d", &m, &n);

swap(&m, &n);

printf("交换后: m=%d, n=%d\n", m, n);
return 0;
}