//第一个难题就是如何知道该申请多大的数组能否在确认数组大小的时候就确认数组的下标
//为了方便循环从第二个字符开始.
//那么怎么设计循环有两种循环，一种是竖直往下的，一种是斜向上的.用一个数来表示状态，每次一种状态截至就改变这个数
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
char * convert(char * s, int numRows){
    int ni[20];
    int nj[20];
    int i,j,iForArr,jForArr,k;//,j用来指向
    int iForArrDate,jForArrDate; 
    k=0;//用来表示循环时竖行的还是斜行的
    int length = strlen(s);
    int countForNumRows;
    for(i=0;i<length;i++)
    {
        if(i==0)
        {
            iForArr = 0;
            jForArr = 0;
            iForArrDate = 0;
            jForArrDate = 0;
            ni[iForArr] =iForArrDate;
            nj[jForArr] =jForArrDate;
            iForArr++;
            jForArr++;
            k=0;
            countForNumRows = numRows -1;
        }
        if( i > 0 && k == 0)
        {
            iForArrDate++;
            ni[iForArr] = iForArrDate;
            nj[jForArr] = jForArrDate;
            jForArr++;
            iForArr++;
            countForNumRows--;
            if(countForNumRows == 0)
            {
                countForNumRows = numRows - 1;
                k = 1;
                continue;
            }
        }
        else if( i > 0 && k == 1)
        {
            iForArrDate--;
            jForArrDate++;
            ni[iForArr] = iForArrDate;
            nj[jForArr] = jForArrDate;
            iForArr++;
            jForArr++;
            countForNumRows--;
            if(countForNumRows == 0)
            {
                countForNumRows = numRows - 1;
                k = 0;
                continue;
            }
        }
    }

    //创建二维字符串数组行数已经给了，时numrows，列数是jforarrDate取最nj【jforarr-1】就行了
    char **TwoStr;
    TwoStr = (char **)malloc(numRows *sizeof(char *));
    for( i = 0; i< numRows;i++ )
    {
        TwoStr[i] = (char *)malloc(nj[iForArr -1] *sizeof(char));
        memset(TwoStr[i], 0, sizeof(char) * nj[iForArr - 1]);
    }


    //对初始化的二维指针赋值
    for(i = 0;i < length;i++)
    {
        TwoStr[ni[i]][nj[i]] = s[i];
    }
    //初始化一个新的字符串
    char *newString = (char *)malloc((length+1) * sizeof(char));
    newString[length] = '\0';
    int pointForNewString = 0;

    for( i = 0;i < numRows;i++)
    {
        for(j = 0;j <nj[jForArr - 1] + 1;j++)
        {
            if((TwoStr[i][j]))
            {
                newString[pointForNewString] = TwoStr[i][j];
                pointForNewString++;
            }
        }
        free (TwoStr[i]);
    }
    free(TwoStr);
    return newString;

    //重新申明一个新的字符串然后对其进行赋值
}
int main()
{
    printf("%s",convert("PAYPALISHIRING", 4));
    return 0;
}