from sklearn import tree
from sklearn.datasets import load_iris
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.tree import plot_tree
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay
from sklearn.metrics import classification_report
import pydotplus

# 获取数据集
iris = load_iris()

# 特征
iris_feature = iris.data
# 标签
iris_label = iris.target
# 鸢尾花的名字
target_name = ['Setosa', 'Versicolor', 'Virginical']
# 数据集的划分
scaler = StandardScaler()
scaler.fit(iris_feature)
X0 = scaler.transform(iris_feature)
X_train, X_test, Y_train, Y_test = train_test_split(X0, iris_label, test_size=0.2, random_state=42)

# 模型的学习

tree1 = tree.DecisionTreeClassifier(max_depth=3)
tree2 = tree.DecisionTreeClassifier(max_depth=2)

tree1 = tree1.fit(X_train, Y_train)
tree2 = tree2.fit(X_test, Y_test)

# 可视化
plot_tree(tree1, filled=True)
plt.title(tree1)
plt.show()
plot_tree(tree2, filled=True)
plt.title(tree2)
plt.show()

# 重要性评分
importance1 = tree1.feature_importances_
importance2 = tree2.feature_importances_
print("第一棵树的重要性评分：")
print(importance1)
print("第二棵树的重要性评分：")
print(importance2)

# 基于测试集的分类树的评价

Y_predict1 = tree1.predict(X_test)
Y_predict2 = tree2.predict(X_test)

matrix1 = confusion_matrix(Y_predict1, Y_test)
matrix2 = confusion_matrix(Y_predict2, Y_test)

print("第一棵树的混淆矩阵如下：")
print(matrix1)
print("第二棵树的混淆矩阵如下：")
print(matrix2)

# 可视化混淆矩阵
display = ConfusionMatrixDisplay(confusion_matrix=matrix1,
                                 display_labels=target_name)
display.plot()
plt.title("matrix1")
plt.show()

display = ConfusionMatrixDisplay(confusion_matrix=matrix2,
                                 display_labels=target_name)
display.plot()
plt.title("matrix2")
plt.show()

# 基于混淆矩阵，估计每个类别的查准率、查全率、F1值，以及宏查准率、宏查全率、宏F1值；估计总体预测正确率

print("第一颗树的查准率、查全率、F1值，以及宏查准率、宏查全率、宏F1值,总体预测正确率如下：")
print(classification_report(Y_test, Y_predict1, target_names=target_name))
print("第二颗树的查准率、查全率、F1值，以及宏查准率、宏查全率、宏F1值,总体预测正确率如下：")
print(classification_report(Y_test, Y_predict2, target_names=target_name))

# 使用整个数据集学习上述两种不同深度的分类树, 可视化
CART1 = tree.DecisionTreeClassifier(max_depth=2)
CART2 = tree.DecisionTreeClassifier(max_depth=3)

CART1 = CART1.fit(iris_feature, iris_label)
CART2 = CART2.fit(iris_feature, iris_label)
plot_tree(CART1, filled=True)
plt.title(CART1)
plt.show()
plot_tree(CART2, filled=True)
plt.title(CART2)
plt.show()
