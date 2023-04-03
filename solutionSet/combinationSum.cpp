//每次输出的数组不相同，这个怎么解决？

//用回溯算法解决，一个数组用来存储某一个解
/*
    一个二维数组用来存储解的集合
    问题是怎么展开树

    如果用树来理解是十分容易的
    但和平常的树不同，平常的树的左子树和右子树并无区别。
    但这个回溯算法的树的形成却有所不同，他是分为两步，一步是读取当前指着的数组的数字，一步是将指针往后移动一下

    但真实的目的是找一个遍历所有的可能
    也就是如何延展出一个能触及所有可能的树，这样才会造出那个树，而不是为了造出这个树，才会莫名其妙地延展出所有可能

    所以，在每一次选择当前数字之前跳过这个数字是为了延展出所有不选择这个数字的结果

    为什么回溯有效？
    为什么，在函数结束后回溯有效？回溯会不会导致没有保存结果

    为什么会回溯？直接原因是改函数结束了，为什么结束了，第一种可能就是candidates减去索引所在的数为零，找到了。
    在加入到答案列表后返回了

    第二种可能就是代码跑完了，代码为什么会跑完了，第一种就是索引代表的数字已经大于那个数字了，所以自然会结束，
    第二种就是跑完了自己包含的函数，而这个函数被跑完了无非就是第一种可能，或者就是上面这个可能，又或者是跑完了属于这个函数的函数，往前
    无数个套娃，就是上面两种可能

    为什么感觉这两种函数结束的方式不同，第一种是找到了答案，第二种是到树的叶子节点了

*/
#include<iostream>
#include<vector>


using std::vector;


class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> combina;
        int idx = 0;
        dfs(candidates,combina,ans,target,idx);
        return ans;
    }

    void dfs(vector<int> & candidates,vector<int> &combina,vector<vector<int>>& ans,int target,int idx)
    {
        if(idx == candidates.size())
        {
            return;
        }
        if(target == 0 )
        {
            ans.emplace_back(combina);
            return ;
        }

        dfs(candidates,combina,ans,target,idx+1);

        if(target - candidates[idx] >=0)
        {
            combina.emplace_back(candidates[idx]);
            dfs(candidates,combina,ans,target - candidates[idx],idx);
            combina.pop_back();
        }
    }
};