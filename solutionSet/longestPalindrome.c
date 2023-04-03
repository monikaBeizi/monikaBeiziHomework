/*

    用动态规划来解题

    一个子串是否是回文可以化成
    p[i,j] = p[i + 1,j -1 ] ^ s[i] == s[j] ;
    或者当i - j +1 = 2，则看两者是否相等，i == j则说明，回文就是这个字符

    hash用二维的数组来储存已经求过回味的子串

    不对，前面的只是其中的一个步骤而已最长的回文返回的是，那我找完之后的怎么储存呢
    也就是说假如确定了，我该储存在哪储存最大的就行了，用max，再多创两个变量来就行了

    要多设一个函数吗，还是在题目给的函数里写？这个取决于我如何递归，还有递归函数只能返回一个值，能返回出来的也就只有一个值。
    

    所以现在先写出暴力的递归，递归是遍历所有可能性一边的，递归是检查所有可能是否是回文并且保存的，能在hash里面保存长度吗
    不行，还是不知到怎么把答案返回出来，我可以用递归确认所有的子串是否为回文，但我怎么在一次次的递归中找到最长的那个

    不行，只能最后在查一次表来找到最大的那个数，每次变换储存那个变换的数就行了
    
    也就是说递归看这个子串是否是回文，主函数遍历所有可能的子串？
    不对，我之前就遍历过了，是否可以在某处截至了？（算了，这个等真正跑起来再慢慢调吧）


*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char * strCut(char * arr,int i,int j)
{
    char * arr1 = (char *)malloc(( j - i +2)*sizeof(char));
    int p;
    for(p = 0; p < j - i + 1; p ++)
    {
        arr1[p] = arr[p+i];
        if(p == j - i )
        {
            arr1[p+1] ='\0';
        }
    }
    return arr1;
}


int judgePalindrom(int i,int j,int **hash,char *s)
{
    int jugde;

    if(hash[i][j] > 0)
    {
        return hash[i][j];
    }

    if((j - i)== 0 )
    return 1;
    
    if((j - i)== 1 )
    {
        if(s[i] == s[j] )
        return 1;
        else
        return 0;
    }

    if((j - i) > 1)//可以用那个逻辑短路的算法
    {
        jugde = ((s[i] == s[j]) && judgePalindrom(i + 1,j - 1,hash,s));
    }
    hash[i][j] =  jugde;
    return jugde;
}

char * longestPalindrome(char * s){
    int length = strlen(s);
    int **hash = (int **)malloc(length *sizeof(int *));
    for(int i = 0; i < length ;i++)
    {
        hash[i] = (int *)malloc(length*sizeof(int ));
    }
    //创建hash表

    //接下来是遍历表
    int i,j;
    int max = 0;
    int mi =0 ,mj = 0 ;
    for(i = 0;i < length;i++)
    {
        for(j = 0 + i;j < length;j++)
        {
            if(judgePalindrom(i,j,hash,s)) 
            {
                if(j - i > max)
                {
                    max = j -i;
                    mi=i;
                    mj=j;
                }
            }
        }
    }
    
    return strCut(s,mi,mj);
}


/*
    没有布尔类型，函数用1，和0来代替
    没有全局变量，函数和传递的参数超过我的预期
    如果return的是int类型的数据就不好调用，感觉还有优化的空间
*/
int main()
{
    char *s = "babada";
    char *s1 = longestPalindrome(s);
    printf("%s\n",s1);
    printf("%s,",s1);
    return 0;
}