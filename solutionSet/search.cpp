#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int length = nums.size();
        for(int i =0;i<length ;i++)
        {
            if(nums[i] == target)
            {
                return i;
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;
    std::vector v ={1,2,3};
    std::cout<<s.search(v,4);
    return 0;
}