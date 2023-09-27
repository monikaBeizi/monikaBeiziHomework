import numpy as np
import pandas as pd

data = pd.read_csv("西瓜.txt", delimiter=',', )


def division(dataToDivide):
    # 打乱DataFrame的行
    shuffled_data = dataToDivide.sample(frac=1, random_state=42)

    # 划分数据集为8:2
    train_ratio = 0.8
    validation_ratio = 0.2

    train_size = int(train_ratio * len(shuffled_data))
    train_data = shuffled_data.iloc[:train_size, :]
    validation_data = shuffled_data.iloc[train_size:, :]

    print(train_size)
    return train_data, validation_data


a, b = division(data)
