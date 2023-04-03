/*
    现在有两种思路，一种是寻找该算法与kmp算法相关的点，另一种是通过寻找元素类型与最高字串长度的关系来解题
    为什么自己认为与kmp算法有关，遍历，重复两个关键词？
    kmp是用来找目标字符串与原串是否有相同的字串，并且找到其位置
    将其算法的时间复杂度降低到线性。
    但本题目可以将其套入到这一模板吗
    但很显然，这个题目的遍历时在每一个中找到其中是否有相同的项

    很明显，最长的字符串的长度肯定是小于等于它的种类的数目的
    而且很明显的就是，如果大于等于二那么肯定最长字符数是大于等于二的，因为
    不可能不接触
    
    而且最长的子串肯定是建立在低一级的子串之上的所以可以在遍历的时候找的最低一级的子串，也就是长度为二的
    子串然后每遍历一次就逐渐增加子串的级数，排除掉不能增加的低级子串

    ->（13）另外单独创建一个数组来储存每个低级子串对应的位置。那假设我现在找到了【2，5，7】这三处，然后在一次遍历后第二处没有了
    那么怎么删除掉第二处？1.用链表来保存，删除和遍历都很简单。2.用串来保存，但串的删除我是没有写过的，而且申请的话还得申请一个不知道多大的。
    3.用c自带的数组来保存，同样要面对删除和转移和申请。


*/
#include<stdio.h>
#include<stdlib.h>

typedef struct listNode{
    int val;
    struct ListNode *next;
}listNode;

listNode *initListNode(void)//初始化链表
{
    listNode *p=(listNode *)malloc(sizeof(listNode));
    p->val=0;
    p->next=NULL;
    return p;
}

void assignmentTwo(listNode *p,int *n,int num)//用于给一个没有赋值的链表头头赋上传入数组的值。
{
    for(int i=0;i<num;i++)
    {
        p->val=n[i];
        p->next=(listNode *)malloc(sizeof(listNode));
        if(i==num-1)
        {
            p->next=NULL;
            break;
        }
        p=p->next;
    }
}

void printList(listNode *l1,int n)//打印链表中n个元素
{
    for(int i=0;i<n;i++)
    {
        printf("%d,",l1->val);
        l1=l1->next;
    }
}

void printListToNULL(listNode *p)//打印链表元素直到next指向null
{
    while(p->next!=NULL)
    {
        printf("%d,",p->val);
        p=p->next;
    }
}

void assignmentForOne(listNode *p,int n)//给一个链表后面添加上指定的int类型n
{
    listNode *p1=(listNode *)malloc(sizeof(listNode));
    p1->val=n;
    p1->next=NULL;
    p->next=p1;   
}

void deleteListNode(listNode *p1,listNode *p2)//该删除是赋值后节点，删除然后指向大后节点这样就可以在不知道上一个节点的情况下删除了
{
    p1->next = p2->next;
}

int lengthOfLongestSubstring(char *s)
{
    //所以首先是遍历后看有多少个元素？不过在这之前先要获得长度
    int i = 0,length = 0;//length是整个字符串的长度
    while(1)
    {
        if(s[i]=='\0')
        {
            length = i;
            break;
        }
        i++;
    }

    //寻找低级子串
    listNode *p;
    int lengthOfListNode = 0;
    p=initListNode();
    char a=s[0];
    for(i = 0;i <length;i++)//反正一定是有一个的所以就不处理最开始的那个了
    {
        if(a!=s[i])
        {
            a=s[i];
            assignmentForOne(p,i);
            lengthOfListNode++;
        }
        //如果一个都没有找到呢，不对，肯定是有一个的，下一个可以返回一的值
        //所以如果是s2这种情况怎么处理，我考虑过没有。在哪一个环节处理，可以跳跃过吗
    }
    if(lengthOfListNode == 0)
    {
        return 1;
    }

    //基于子串不断提高等级直到不能提高
    int lengthOfListNodeForloop = lengthOfListNode;//用于暂存改变值，不改变某次for循环的次数
    listNode *p1=p;//用于在链表p中跳跃的节点
    int level = 1;//等级
    listNode *p2=p;//用于判断
    int j;
    while(1)
    {
        for(i = 0;i <lengthOfListNode++;i++)
        {
            //查看前头的，查看后头的如果前头或者后头到达串头或者串尾了就停止
            /*
            这次决定链表是否删除？
            那就要考虑循环中最后几个情况：删除仅剩一个的链表；什么时候循环截至；删除的实现
            */

           //现在检查该节点之前,建立在可以访问
           if(p1->val-1>=0 && p1->val+level<=length-1)
           {
            if(s[p1->val]==s[p1->val-1] && s[p1->val]==s[p1->val+level])
            {
                if(i==0)
                {
                    p=p->next;
                    lengthOfListNodeForloop--;
                    p1=p1->next;//该进入下一次的循环了
                    continue;
                }
                for(j = 0;j <i-1;i++)
                {
                    p2=p2->next;
                }
                deleteListNode(p2,p1);
                lengthOfListNodeForloop--;
                p1=p1->next;
                continue;
            }
            if(s[p1->val]!=s[p1->val-1])
            {
               p1->val=p1->val-1; //如果不同将子串向前扩充一位，相同则跳到elseif
            }else if (s[p1->val]!=s[p1->val+level])//总之就是一次循环只能扩充一位
            {
                //这个只是逻辑上向后，但讲实话level加一的话就代表他的长度加一了，所以这个循环没有啥用   
            }
            p1=p1->next;
           }
           if(p1->val-1 < 0 && p1->val+level <= length-1)
           {
            if(s[p1->val]==s[p1->val+level])
            {
                if(i==0)
                {
                    p=p->next;
                    lengthOfListNodeForloop--;
                    p1=p1->next;//该进入下一次的循环了
                    continue;
                }
                for(j = 0;j <i-1;i++)
                {
                    p2=p2->next;
                }
                deleteListNode(p2,p1);
                lengthOfListNodeForloop--;
                p1=p1->next;
                continue;
            }
            p1=p1->next;
           }
           if(p1->val-1 >= 0 && p1->val+level > length-1)
           {
            if(s[p1->val]==s[p1->val-1])
            {
                if(i==0)
                {
                    p=p->next;
                    lengthOfListNodeForloop--;
                    p1=p1->next;//该进入下一次的循环了
                    continue;
                }
                for(j = 0;j <i-1;i++)
                {
                    p2=p2->next;
                }
                deleteListNode(p2,p1);
                lengthOfListNodeForloop--;
                p1=p1->next;
                continue;
            }
            if(s[p1->val]!=s[p1->val-1])
            {
               p1->val=p1->val-1; //如果不同将子串向前扩充一位，相同则跳到elseif
            }
            p1=p1->next;
           }

           lengthOfListNode=lengthOfListNodeForloop;
           level++;
        }
    }
}

int main()
{
   return 0;
}