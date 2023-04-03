/*
    给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

    我在想，决定一个水桶装水的量是短板效应？
    所以这道题目其实就是很多个放在一起的水桶，如何区分这些水桶才是难点，说不定还有水桶底板距离桶顶的高度的这个需要考虑的，不过分成两步吧

    所以反正是需要两个指针的，一个指向左边隔板，一个指向右边隔板。右边指针从左往右移动，第一次碰到碰到下降的就可以将当前右板指向的下标减一
    将这个数设置为左板的，然后右板接着往右走，遇到降低的时候，下标减一得到的下标和左板相距的位置就是一个桶子了
    但是值得注意的是，这一下降，也是新桶子的左板子

    不对，上面没有考虑到指针指到桶底的情况所以一个桶子的情况应该是 ：变下降，变上升再变下降。
    需要保存的有左板，底板，右板
    再整个函数用来计算一个桶子的容量
    主方法用来找桶子吧

    怎么实现

    计算容量怎么算？在底板之前，高度差X
*/

#include<iostream>
#include<vector>

using std::cout;
using std::vector;

class Solution {
public:
    int computeCapacity(int left,int right,int mid,vector<int>&height) //对于给定左，底，右板的桶子计算容量
    {
        // int heightD = 0;
        // int i = left + 1;
        // int sum = 0;
        // while(i != mid)
        // {
        //     heightD = height[i-1]-height[i];//计算高度差
        //     sum = sum + heightD * (mid - i);
        //     i++;
        // }
        //先需要判断谁是短板

        int heightD = 0;
        int sum = 0;
        if(height[left] < height[right] )
        {
            int i = left + 1;

            while(i != mid)
            {
                heightD = height[i-1] - height[i];
                sum = sum + heightD * (mid - i);
                i++;
            }

            sum = sum * 2;
            sum = sum + (height[left] - height[mid]);
        }

        if(height[left] >= height[right])
        {
            int i = right - 1;

            while(i!= mid)
            {
                heightD = height[i] - height[i -1];
                sum = sum + heightD *(i - mid);
                i--;
            }

            sum = sum * 2;
            sum = sum + (height[right] - height[mid]);
        }

        return sum;
    }

    int trap(vector<int>& height) 
    {
        int left = 0,right = 0,mid = 0;//创建三个变量分别是左板，右板，底板的指针
        int light1 = 0;//指示判断大小的，如果是0对下降敏感，如果是1对上升敏感
        int light2 = 0;//指示2号，用来判断跟新左板还是右板，右板顺便把sum更新一下
        int sumCapacity = 0;//用来存储总容量

        int length = height.size();//保存数组的长度;
        for(int i = 0;i < length - 1; i++)
        {
            if(light1 == 0)
            {
                if(height[i] > height[i + 1])//出现下降，那么更新板子位置
                {
                    light1 = 1; //跟新指示
                    if(light2 == 0)//如果light2为0更新左板
                    {
                        light2 = (light2 + 1) % 2;//让light2徘徊于0，1
                        left = i;
                    } 
                    else if(light2 == 1)//如果light2为1更新右板,顺便计算总容量
                    {
                        // light2 = (light2 + 1) % 2;
                        right = i;
                        sumCapacity = sumCapacity + computeCapacity(left,right,mid,height);

                        //右板的同时也是左板
                        left = i;
                    }

                }
            }
            else if(light1 == 1)
            {
                if(height[i] < height[i + 1])//符合底板条件
                {
                    light1 = 0;
                    mid = i;
                }
            }

            if(i == height.size()-2 && height[i] < height[i + 1] ) //如果指针到倒数第二个的时候，刚好指向一个底板，又因为不会往下数了
            {//所以直接设置右板
                right = i + 1;
                sumCapacity = sumCapacity + computeCapacity(left,right,mid,height);
            }
        }

        return sumCapacity;
    }
};

int main()
{
    vector<int> v = {4,2,0,3,2,5};
    Solution s;
    cout<<s.trap(v);
    return 0;
}