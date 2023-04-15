import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

import seaborn as sns
from matplotlib.colors import ListedColormap
from sklearn import neighbors, datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix
import numpy as np

# 获取数据集
iris = datasets.load_iris()
X = iris.data[:, -2:]
Y = iris.target

# 进行数据集的预处理
scaler = StandardScaler()
scaler.fit(X)
X0 = scaler.transform(X)
X_train, X_test, Y_train, Y_test = train_test_split(X0, Y, test_size=0.2, random_state=42)

# 生成（1，16）的数组，循环16次
K_range = range(1, 17)
K_error = []  # 用来存储每个K值的平均错误率
K_standard_deviation = []  # 用来存储每个K值的平均标准差

for K in K_range:
    knnModel = KNeighborsClassifier(n_neighbors=K)
    # 进行4折交叉验证
    arr = cross_val_score(knnModel, X_train, Y_train, cv=4, scoring='accuracy')

    # 计算平均错误率
    K_error.append(1 - arr.mean())
    # 计算标准差
    K_standard_deviation.append(np.std(arr))
plt.errorbar(K_range, K_error, yerr=K_standard_deviation)
plt.show()

# 获取K的最终优选，并赋值给n_neighbor
n_neighbor = K_error.index(min(K_error)) + 1
print("K的最终优选结果为" + str(K_error.index(min(K_error)) + 1))

# 用得到的K值进行训练
knn = KNeighborsClassifier(n_neighbors=n_neighbor)
knn.fit(X_train, Y_train)

# 获取预测结果,将其转化为混淆矩阵
Y_predict = knn.predict(X_test)
confusion = confusion_matrix(Y_test, Y_predict)
sns.heatmap(confusion, annot=True)
plt.show()

# 计算查准率、查全率、F1 值，以及宏查准率、宏查全率、宏F1 值；估计总体预测正确率。
P = []
R = []
parament = {}
for i in range(3):
    parament['P' + str(i)] = confusion[i, i] / (sum(confusion[:, i]))
    parament['R' + str(i)] = confusion[i, i] / (sum(confusion[i, :]))
    parament['F1_' + str(i)] = (2 * parament['P' + str(i)] * parament['R' + str(i)]) / \
                               (parament['P' + str(i)] + parament['R' + str(i)])
    P.append(parament['P' + str(i)])
    R.append(parament['R' + str(i)])
macro_P = np.mean(P)
macro_R = np.mean(R)
macro_F1 = (2 * macro_P * macro_R) / (macro_P + macro_R)

sum_right = 0
for i in range(3):
    sum_right += confusion[i, i]

accuracy = sum_right / np.sum(confusion)
print(accuracy)

# Create color maps
cmap_light = ListedColormap(["orange", "cyan", "cornflowerblue"])
cmap_bold = ["darkorange", "c", "darkblue"]

# 设置近邻数，设置特征空间采样步长
n_neighbors = n_neighbor
h = 0.02

# 因为上面已训练好了knn模型，就不在训练了，训练所用的数据集分别为：
# X_train,Y_train
x_min, x_max = X_train[:, 0].min() - 1, X_train[:, 0].max() + 1
y_min, y_max = X_train[:, 1].min() - 1, X_train[:, 1].max() + 1

xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

Z = knn.predict(np.c_[xx.ravel(), yy.ravel()])
Z = Z.reshape(xx.shape)

# put the result into a color plot
plt.figure(figsize=(8, 6))
plt.contourf(xx, yy, Z, cmap=cmap_light)

# D--绘制训练样本的散点图--Plot also the training points
sns.scatterplot(
    x=X_train[:, 0],
    y=X_train[:, 1],
    hue=iris.target_names[Y_train],
    palette=cmap_bold,  # 注意使用的颜色表
    alpha=1.0,
    edgecolor="black")

plt.xlim(xx.min(), xx.max())
plt.ylim(yy.min(), yy.max())
plt.xlim(xx.min(), xx.max())
plt.ylim(yy.min(), yy.max())

plt.title("鸢尾花三类别分类(近邻数k = %i, weights = '%s')"
          % (n_neighbors, "uniform"), size=16)
plt.xlabel(iris.feature_names[0], size=14)
plt.ylabel(iris.feature_names[1], size=14)

plt.savefig("uniform" + 'KNN分类.pdf')
plt.show()
