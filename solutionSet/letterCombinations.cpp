/*
    如果学习n皇后的算法的话，使用for的
    那我打算怎么做才能遍历所有可能性？

    或者说我是打算在那个方面实现回溯？
    其实就是选择下一个字母这个方面。

    每个索引对应的数字有很多种不同的选择
    可以延展出很多分叉，这个怎么选择

    比如说，我传入23
    因为索引第一个是2，我找到2所对应的英文字母，然后呢？

    不如用for吧，反正每个数字对应的字母都是要输出出去的，在for里面回溯也挺好的

*/
#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;
using std::cout;



class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> ans;//答案的列表 
        vector<vector<string>> list;
        // 每个数字对应的列表。从2到9，干脆0到7得了，到时候用的时候- 2 就行

        list.insert(list.end(),{{'a','b','c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'}
        ,{'p','q','r','s'},{'t','u','v'},{'w','x','y','z'}});
        //需要的键位对应的二维数组已经构造完成现在要整递归的函数了
        string s;
        int index = 0;
        produceAns(digits,ans,list,s,index);
        return ans;
    }

    void produceAns(string digits,vector<string> &ans,vector<vector<string>> &list,string s,int index)
    {
        if(index >= digits.size())
        {
            ans.push_back(s);
            return ;
        }//如果索引超出digits数组自然就没有递归的必要了


        int number = digits[index] - 48;
        for(int i = 0;i < list[number - 2].size();i++)
        {
            s=s+list[number -2][i];//将对应的字符串压入到 用于输入的字符串中
            produceAns(digits,ans,list,s,index + 1);
            s.pop_back();
        }
    }
};

int main()
{
    string s = "23";
    Solution h;
    vector<string> ans = h.letterCombinations(s);
    for(int i = 0;i < ans.size();i++)
    {
        cout<<ans[i]<<",";
    }
    return 0;
}