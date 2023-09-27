from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
import pandas as pd


data = pd.read_csv("datingTestSet.txt", delimiter="\t", header=None)
x = data.iloc[:, :3].values  # 特征列
y = data.iloc[:, -1].values  # 标签列

scaler = StandardScaler()
data = scaler.fit_transform(x)

x_train, x_test, y_train, y_test = train_test_split(data, y, test_size=0.2, random_state=0)

k, last_K = 0, 0

for i in range(1, 16):
    KNNModel = KNeighborsClassifier(n_neighbors=i)
    KNNModel.fit(x_train, y_train)

    train_score = KNNModel.score(x_train, y_train)
    test_score = KNNModel.score(x_test, y_test)
    print("模型的准确率：", test_score)

    if test_score > last_K:
        last_K = test_score
        k = i

KNN = KNeighborsClassifier(n_neighbors=k)
KNN.fit(x_train, y_train)

predictCategory = KNN.predict(x_test)

print(predictCategory)
