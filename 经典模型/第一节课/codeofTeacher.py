import numpy as np


def file2matrix(filename):
    """
    函数说明：打开解析文件，对数据进行分类，
        1代表不喜欢，2代表魅力一般，3代表极具魅力

    Parameters:
        filename - 文件名

    Returns:
        returnMat - 特征矩阵
        classLabelVector - 分类label向量
    """
    # 打开文件
    with open(filename, 'r') as fr:
        # 读取文件所有内容
        arrayOflines = fr.readlines()

    # 得到文件行数
    numberOfLines = len(arrayOflines)
    # 返回的NumPy矩阵numberOfLines行，3列
    returnMat = np.zeros((numberOfLines, 3))
    # 创建分类标签向量
    classLabelVector = []
    # 行的索引值
    index = 0
    # 读取每一行
    for line in arrayOflines:
        # 去掉每一行首尾的空白符，例如'\n','\r','\t',' '
        line = line.strip()
        # 将每一行内容根据'\t'符进行切片,本例中一共有4列
        listFromLine = line.split('\t')
        # 加入字符串转float的代码
        # 将数据的前3列进行提取保存在returnMat特征矩阵中
        # returnMat[index,:] = listFromLine[0:3]
        returnMat[index, :] = [float(i) for i in listFromLine[:-1]]
        # 根据文本内容进行分类1：不喜欢；2：一般；3：喜欢
        if listFromLine[-1] == 'didntLike':
            classLabelVector.append(1)
        elif listFromLine[-1] == 'smallDoses':
            classLabelVector.append(2)
        elif listFromLine[-1] == 'largeDoses':
            classLabelVector.append(3)
        index += 1
    # 返回标签列向量以及特征矩阵
    return returnMat, np.array(classLabelVector)
