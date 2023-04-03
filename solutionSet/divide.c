#include<stdio.h>

int divide(int dividend,int divisor){
    //dividend 被除数，divisor除数
    int quotient = 0;
    int sign = 1;
    int sum = 0;

    //确定特别情况
    if(divisor == 0)
    {
        printf("The number of divisor can not be 0;");
        return 0;
    }

    if(dividend == 0)
    {
        return 0;
    }

    if(dividend == -2147483648)
    {
        if(divisor == 1)
        {
            return -2147483648;
        }

        if(divisor == -1)
        {
            return 2147483647;
        }
    }

    //首先确定商的符号
    if(((dividend > 0)&&(divisor > 0)) ||((dividend < 0) && (divisor)< 0) )
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }


    //确定符号后将数都变成正数

    if(dividend < 0 )
    {
        dividend =  -dividend;
    }
    if(divisor < 0 )
    {
        divisor = - divisor;
    }

    //开始计算商
    while(sum < dividend)
    {
        quotient ++;
        sum = sum + divisor;
    }
    if(sum > dividend)
    {
        quotient -- ;
    }
    if(sign < 0)
    {
        quotient =  - quotient;
    }
    return quotient;
}

int main()
{
    int a = 15,b = -7;
    int number = -2147483648;
    number = number * number;
    printf("%d \n",number);
    int num = 0;
    num = divide(3,3);
    printf("%d",num);
    return 0;
}