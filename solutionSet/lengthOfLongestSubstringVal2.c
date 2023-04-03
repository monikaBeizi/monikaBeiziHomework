/*
    hash表的每个存加一的下标，这样尾指针可以直接定位到下一个的位置
    保存其最临时的窗口长度，每次出现不一样的时候记得归零之前与最大值比较
    那么循环的次数呢就是字符串的长度

    现在有个疑问就是他们之间的长度是头减尾吗
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int lengthOfLongestSubstring(char * s){
    //hash 和 滑块 
    //如果不在里面就在hash表里保存加一的下标（

    int lengthBetweenFR = 0,sum = 0;
    int length = strlen(s);
    int hash[255]={0};
    int i;
    int front = 0,rear = 0;
    for(i = 0;i < length;i++)
    {
        if(hash[s[front]] > 0)
        {
            //如果哈希表中存在头指针现在存的数据
            if(rear < hash[s[front]]) rear = hash[s[front]];
            hash[s[front]] = front + 1;
            lengthBetweenFR = fmax ( lengthBetweenFR , front - rear + 1);
        }
        else
        {
            hash[s[front]] = front + 1;
            lengthBetweenFR = fmax ( lengthBetweenFR , front - rear + 1);
        }
        front ++;
    }
    return lengthBetweenFR;
}

int main()
{
    char a[]= "alouzxilkaxkufsu";//这个跑不起来是因为if跑完之后就结束了，再也
    char s[]= "pwwkew";
    printf("%d",lengthOfLongestSubstring(a));
    return 0;
}

//没有考虑之前存在的字符在查重的时候会使尾指针往后调
//没有保证hash中只有滑块映射的值