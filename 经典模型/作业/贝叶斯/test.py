import pandas as pd
import numpy as np

data = pd.read_csv("西瓜.txt", delimiter=",")


class NaiveBayes:
    def __init__(self, dataSet: pd.DataFrame, targetClass):
        self.dataSet = dataSet
        self.targetClass = targetClass  # 所给训练集中的目标类别是什么
        self.attributeSet = {}  # 字典里储存了每一列的特征种类的列表
        self.contingentProbability = {}  # 字典里储存了每一个特征种类关于类别的条件概率
        self.targetClassAmount = {}  # 储存目标类别的数量
        self.attributeProbability = {}  # 字典里储存了每一个特征种类在这个种类中的概率

        self.addAttributeSet(self.dataSet)  # 调用函数初始化attributeSet字典
        self.countTargetClassAmount()  # 调用函数初始化targetClassAmount
        self.countAttributeProbability()  # 调用函数初始化attributeProbability
        self.initContingentProbability()    # 初始化类

    # 初始化特征种类字典(包括目标特征)
    def addAttributeSet(self, trainingSet: pd.DataFrame):

        # 给每个列的特征名字在字典中创建列表
        for i in trainingSet.columns:
            self.attributeSet[i] = []
            # 刚好这一列的列表创建成功
            # 在attributeSet中储存每一列的特征的种类
            for j in trainingSet[i]:
                if j not in self.attributeSet[i]:
                    self.attributeSet[i].append(j)

    # 计算每一个特征种类在这个种类中的概率
    def countAttributeProbability(self):

        for i in self.attributeSet:
            # 使用attributeSet得到每一个特征的种类
            for j in self.attributeSet[i]:
                amount = self.dataSet[self.dataSet[i] == j].shape[0]
                # 最后把概率赋值给它
                self.attributeProbability[j] = amount / self.dataSet[i].shape[0]

    # 计算目标类别的数量
    def countTargetClassAmount(self):
        for i in self.attributeSet[self.targetClass]:
            # 获取每一个目标类别的数量并保存
            self.targetClassAmount[i] = self.dataSet[self.dataSet[self.targetClass] == i].shape[0]

    # 初始化contingentProbability字典
    def initContingentProbability(self):

        # 将特征种类和条件概率进行排列组合

        # 这个for用来把尝试不同条件的条件概率
        for i in self.attributeSet[self.targetClass]:

            # 这个for用来取出数据集中所有的列,用于接下来的计算
            for j in self.dataSet.columns:

                # 如果等于目标类别就跳过
                if j == self.targetClass:
                    continue

                # 用for 遍历 其中的类别
                for k in self.attributeSet[j]:
                    # 然后计算条件概率
                    amount = \
                        self.dataSet[(self.dataSet[j] == k) & (self.dataSet[self.targetClass] == i)].shape[0]
                    # 计算条件概率
                    self.contingentProbability[str(k) + "|" + str(i)] \
                        = amount / self.targetClassAmount[i]

    # 现在每一个特征的类别都和目标特征组合在一起变成字典了，可以用来计算了
    def forPredict(self, *args):

        # 输入的是一个包含特征的元组，最后一个是目标类别
        targetClass = args[-1]

        # 创建字典保存不同类别
        probability = {}

        # 分别求不同类别的概率
        for i in self.attributeSet[targetClass]:

            # 通过给定的args来计算概率
            # 用for循环计算上半部分
            multiplicationOfContingentProbability = 1  # 分子左半部分，不包括最后面的
            multiplicationOfAttributeProbability = 1  # 分母
            for k in args:
                # 当k为目标类别的时候跳过
                if k == targetClass:
                    continue

                # 计算multiplicationOfContingentProbability
                multiplicationOfContingentProbability = \
                    multiplicationOfContingentProbability * \
                    self.contingentProbability[k + "|" + i]

                # 计算 下面那个
                multiplicationOfAttributeProbability = \
                    multiplicationOfAttributeProbability * \
                    self.attributeProbability[k]

            # 分子补上目标类别的概率
            up = multiplicationOfContingentProbability * self.attributeProbability[i]
            down = multiplicationOfAttributeProbability

            # 把概率储存到字典里面
            probability[i] = up / down

        # 比较不同类别的概率，输出概率最高的类别
        maxProbability = self.attributeSet[targetClass][0]
        maxP = probability[maxProbability]
        for i in probability:
            if probability[i] > probability[maxProbability]:
                maxProbability = i
                maxP = probability[i]

        print("概率最高的是:" + str(maxProbability) + ",值为：" + str(maxP) + str(args))

    def test(self):
        print(self.contingentProbability)
        print(self.attributeSet)


a = NaiveBayes(data, "好瓜")

a.forPredict('青绿', '蜷缩', '沉闷', '稍糊', '稍凹', '硬滑', "好瓜")

dataTest = data.iloc[:, : -1].values
for u in range(dataTest.shape[0]):
    lis = dataTest[u]
    lis = lis.tolist()
    lis.append("好瓜")
    b, c, d, e, f, g, h = lis
    a.forPredict(b, c, d, e, f, g, h)
