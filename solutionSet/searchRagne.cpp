#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int length = nums.size();
        vector<int> v = {-1,-1};
        int j = 0;
        for(int i = 0;i < length;i++)
        {
            if(nums[i] == target)
            {
                if(j>1)
                {
                    v[1] = i;
                    continue;
                }
                v[j] = i;
                j++;
            }
        }
        if(v[0] >=0 && v[1] == -1)
        {
            v[1] =v [0];
        }
        return v;
    }
};
int main()
{
    Solution s;
    vector<int> v ={3,3,3};
    cout<<s.searchRange(v,3)[0];
    cout<<",";
    cout<<s.searchRange(v,3)[1];
    return 0;
}