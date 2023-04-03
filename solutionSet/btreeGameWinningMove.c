#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef int bool;

struct TreeNode* seekNode(int val,struct TreeNode *root){
    if(root == NULL){
        return NULL;
    }
    if(root->val == val)
    {
        return root;
    }

    struct TreeNode * res = seekNode( val,root -> left);
    if(res !=NULL){
        return res;
    }else{
        return seekNode(val,root -> right);
    }

}//用于寻找该树中某一特定的根节点



int theLengthOfTreeNode(struct TreeNode * p,int *sum){
    if(p == NULL){
        return -1;
    }
    (*sum)++;
    theLengthOfTreeNode(p->left,sum);
    theLengthOfTreeNode(p->right,sum);
    return 0;
}//用于求该树节点（包括该节点）子树的总数



bool btreeGameWinningMove(struct TreeNode *root,int n,int x){
    int *sum;//用函数储存的介质
    sum = (int *)malloc(sizeof(int));
    *sum = 0;
    int parent,leftchild, rightchild,self;
    int half = (n + 1)/2;

    struct TreeNode * selfp = seekNode(x,root);
    theLengthOfTreeNode(selfp,sum);
    self = *sum;

    //计算如果二手在父节点
    parent = n - self;
    if(parent >self){
        return 1;
    }

    //计算左子树
    *sum = 0;
    theLengthOfTreeNode(selfp->left,sum);
    leftchild = *sum;
    if(leftchild > self){
        return 1;
    }

    //计算右子树
    *sum = 0;
    theLengthOfTreeNode(selfp->right,sum);
    rightchild = *sum;
    if(rightchild > self){
        return 1;
    }
    

    return 0;
}
int main(){

    
    return 0;
}