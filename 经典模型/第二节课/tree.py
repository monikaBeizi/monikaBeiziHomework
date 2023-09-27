import numpy as np

dataset = [[0, 0, 0, 0, 'no'],
           [0, 0, 0, 1, 'no'],
           [0, 1, 0, 1, 'yes'],
           [0, 1, 1, 0, 'yes'],
           [0, 0, 0, 0, 'no'],
           [1, 0, 0, 0, 'no'],
           [1, 0, 0, 1, 'no'],
           [1, 1, 1, 1, 'yes'],
           [1, 0, 1, 2, 'yes'],
           [1, 0, 1, 2, 'yes'],
           [2, 0, 1, 2, 'yes'],
           [2, 0, 1, 1, 'yes'],
           [2, 1, 0, 1, 'yes'],
           [2, 1, 0, 2, 'yes'],
           [2, 0, 0, 0, 'no']]


# 划分子集

def split_dataset(date, feat_i, value):
    sub_dataset = []
    for x in date:
        if x[feat_i] == value:
            x_a = x[:feat_i]
            x_a.extend(x[feat_i + 1:])
            sub_dataset.append(x_a)
    return sub_dataset


# 计算熵
def calc_ent(data):
    n = len(data)
    # 统计各类别的样本数
    label_count = {}
    for x in data:
        label = x[-1]
        label_count[label] = label_count.get(label, 0) + 1
    ent = 0
    # 计算决策属性熵

    for lab in label_count:
        ent = ent - (label_count[lab] / n) * np.log2(label_count[lab] / n)
    return ent


# 选择使得信息增益最大的索引

def choose_best_feat(data):
    # 存熵的表
    ent_list = []

    # 此for 循环用来读取每一个特征列
    for i in range(len(data[0]) - 1):
        # 获得该特征i的特征值
        value = []
        # 用来存储特征值

        for j in range(len(data)):
            # 如果不存在就加到列表中来
            if data[j][i] not in value:
                value.append(data[j][i])

        # 划分子集
        after = []

        for j in value:
            after.append(split_dataset(data, i, j))

        # 计算熵
        ent = 0
        for leaf in after:
            ent += calc_ent(leaf)
        ent_list.append(ent)

    # 传递出最大信息增益的索引
    return ent_list.index(min(ent_list))


def create_tree(data, feat_labels):
    # 判断终止条件
    # 递归到所有样本属于一个类别，则该类别为叶子节点
    for x in data:
        determine = x[0][-1]
        for y in x:
            if y[-1] != determine:
                break
            if y == x[-1]:
                # 如果到最后一个也没有不等于第一个说明属于同一类别
                pass


    # 选择最优特征

    # 遍历最优特征的每一个特征值，拿到子集，

    return
