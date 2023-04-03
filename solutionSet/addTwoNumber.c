#include<stdio.h>
#include<stdlib.h>
//不是说逆序储存吗
//逆序是指它存储的数字是逆序的
typedef struct ListNode{
    int val;
    struct ListNode *next;
}ListNode;

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2){
    //思路就是同时读取每一个节点的数字然后保存要进位的数字就行了
    
    //第一就是循环截至的时间
    //第二就是其中一个截至的时候怎么办
    //第三就是进位问题
    //给两个数字赋值，相加，替代，进位
    struct ListNode *h=l1;
    int num1,num2,num3,jude;
    jude=0;
    num3=0;//分别代表来自两个链表的值
    while(1)
    {

        if(jude==1)
        {
            num1=0;
            num2=l2->val;
        }
        else if (jude==2)
        {
            num1=l1->val;
            num2=0;
        }
        else if(jude == 0)
        {
            num1=l1->val;
            num2=l2->val;
        }
        // num1=num1+num2;
        // l1->val=num3;
        // num3=0;
        // if(num1>=10)
        // {
        //     num1=num1-10;
        //     num3++;
        // }
        // l1->val+=num1;
        num1=num1+num2+num3;
        num3=0;
        if(num1>=10)
        {
            num1=num1-10;
            num3++;
        }
        l1->val=num1;
        if(l1->next==NULL && l2->next!=NULL)
        {
            struct ListNode *p=(struct ListNode *)malloc(sizeof(struct ListNode));
            p->next=NULL;
            l1->next=p;
            jude=1;
        }
        else if(l2->next==NULL && l1->next!=NULL)
        {
            struct ListNode *p=(struct ListNode *)malloc(sizeof(struct ListNode));
            p->next=NULL;
            l2->next=p;
            jude=2;
        }
        else if(l1->next==NULL && l2->next==NULL)
        //什么时候截止？当然是指针没有下一个的时候
        //但现在好像因为赋值的问题导致
        {
            if(num3==1)
            {
                l1->next=(struct ListNode*)malloc(sizeof(struct ListNode));
                l1=l1->next;
                l1->val=1;
                l1->next=NULL;
            }
            return h;
        }
        l1=l1->next;
        l2=l2->next;
    }
}
void assignment(ListNode *p,int n)
{
    int a=0;

    for(int i= n;i<n+3;i++)
    {
        p->val=i;
        p->next=(ListNode *)malloc(sizeof(ListNode));
        if(a==2)
        {
            p->next=NULL;
            break;
        }
        a++;
        p=p->next;
    }
}
void assignmentTwo(ListNode *p,int *n,int num)
{
    for(int i=0;i<num;i++)
    {
        p->val=n[i];
        p->next=(ListNode *)malloc(sizeof(ListNode));
        if(i==num-1)
        {
            p->next=NULL;
            break;
        }
        p=p->next;
    }
}

void printList(ListNode *l1,int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d,",l1->val);
        l1=l1->next;
    }
}
int main()
{
    
    ListNode *next;
    next=(ListNode *)malloc(sizeof(ListNode));
    ListNode *h=next;
    ListNode *h2=(ListNode *)malloc(sizeof(ListNode));
    // for(int i= 6;i<9;i++)
    // {
    //     next->val=i;
    //     next->next=(ListNode *)malloc(sizeof(ListNode));
    //     next=next->next;
    // }
    // assignment(h,6);//6.7.8
    // assignment(h2,3);//3.4.5
    int arr1[]={9,9,9,9,9,9,9};
    int arr2[]={9,9,9,9};
    assignmentTwo(h,arr1,7);
    assignmentTwo(h2,arr2,4);
    addTwoNumbers(h,h2);
    printList(h,8);
    return 0;
}