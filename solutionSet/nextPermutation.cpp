//31题
/*
    1.符合条件的数就是这个数后面就是存在一个数是大于它的，由这个条件可以推理出，它后面的数字是递增的，因为如果不是的，那么第一个符合条件的数字
    就不是它了。
    2.找到这个数之后，第二步就是找到它之后数中，大于他，但是是最小的那个，将他们两个交换位置。
    3.因为题目说是刚好大于这个数字的，该位数交换后，后面的位数还需要重新排序，保证是大于这个数组，但是是最小的那个，之前选择最小的
    交换也就是为了这个一目的。
*/
#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 2;
        while(i>=0 && nums[i]>=nums[i+1])
        {
            i--;
        }
        int temp  = -1;
        if(i >= 0)
        {
                for(int j =nums.size()-1;j>i;j--)
                {
                    if(nums[j]>nums[i] &&temp ==-1)
                    {
                        temp = j;
                        break;
                    }
                }
                swap(nums[i],nums[temp]);
        }
        //然后排序
    }
};
int main()
{
    vector<int> v ={1,2,3};
    Solution a;
    a.nextPermutation(v);
    for(int i = 0;i < 3; i++)
    {
        cout<<v[i];
    }
    cout<<"\n";


    return 0;

}