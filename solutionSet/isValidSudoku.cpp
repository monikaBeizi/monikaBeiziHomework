#include<vector>
#include"nums.h"

/*
用一个三维的向量来整一个哈希表
第一维用来表示行的哈希表，长度为九，每次扫描到就从零变为1
第二维就是列的哈希
第三维就是宫的
在给定的二维向量里，每次遍历每一行的数的时候，顺便给相应的列和哈希表整上
如果一旦发现三维中有一维，那就说明改数独违法

如何将二维数组上的每一个元素映射到三维这边呢
每一个元素的都有对应的行列，所以很好对应
那宫呢如何对应宫？
用if一个个去甄别？还是说用switch？
破案了，创建一个三维数组来单独储存，3，3，9
*/
using std::vector;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int vec[2][9][9]; //用来储存行列的
        int palace[3][3][9];//用来储存宫中出现的
        int num = 0;

        memset(vec,0,sizeof(vec));
        memset(palace,0,sizeof(palace));

        int i,j;
        for(i = 0;i < 9;i++)
        {
            for(j = 0;j < 9; j++)
            {
                char c = board[i][j]; 
                if(c != '.')//先判断是否是数字，不过话说一个是字符一个是整形，应该能比较吧
                {
                    num = c - '0' -1;
                    if(vec[0][i][num] == 0)
                    {
                        vec[0][i][num] = 1;//表明i行，值为num的数现在存在过了
                    }
                    else
                    {
                        return false;//因为不合法，返回
                    }

                    if(vec[1][j][num] == 0)
                    {
                        vec[1][j][num] = 1; //这一行代码表示这一列存在过
                    }
                    else
                    {
                        return false;
                    }

                    if(palace[i/3][j/3][num] == 0)//看看在第一个为i，第二个为j的第num数组中，是否之前被赋值过
                    {
                        palace[i/3][j/3][num] = 1;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};


//第一没有仔细了解哈希表中每个向量维度的意义
//忽略的字符串数字转换到整型数字的方法
//忘记了最后返回


int main()
{
    return 0;
}