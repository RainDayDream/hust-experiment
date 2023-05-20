import numpy as np
import pandas as pd
import csv


class Adaboost():
    def __init__(self, base):
        self.base = base

    # 初始化一些参数
    def init_args(self, datasets, labels, n_estimators=10, learning_rate=1.0):
        self.clf_num = n_estimators  # 分类器的个数
        self.learning_rate = learning_rate  # 移动步伐
        self.X = datasets  # 样本数据
        self.Y = labels  # 样本分类类别
        self.M, self.N = datasets.shape  # 样本的个数和特征数
        self.clf_sets = []  # 弱分类器数目和集合
        self.alpha = []  # alpha保存
        self.weights = np.ones((self.M, 1)) / self.M  # 初始化weights，1/m，共有m个
        self.w = np.mat(np.ones((self.N, 1)))
        self.b = 0

    # 决策树
    # 基于决策树桩构建弱分类器
    def decision_stump(self, features, labels, weights):
        feature_length = len(features)
        error = float('inf')
        threshold = 0.0
        features_min = min(features)
        features_max = max(features)
        length_step = (features_max - features_min) / self.learning_rate
        flag = 0
        result = None
        for i in range(1, int(length_step)):
            v = features_min + self.learning_rate * i
            array_pos = np.array([1 if features[k] > v else 0 for k in range(feature_length)])
            error_pos = sum([weights[k] for k in range(feature_length) if array_pos[k] != labels[k]])
            array_neg = np.array([0 if features[k] > v else 1 for k in range(feature_length)])
            error_nag = sum([weights[k] for k in range(feature_length) if array_neg[k] != labels[k]])

            if error_pos < error_nag:
                weight_error = error_pos
                cur_array = array_pos
                flag = 1  # 大于阈值赋值1
            else:
                weight_error = error_nag
                cur_array = array_neg
                flag = 0  # 小于阈值赋值1
            if weight_error < error:
                error = weight_error
                result = cur_array
                threshold = v
        return threshold, flag, error, result  # 返回阈值，阈值比较规则，错误率，判断结果

    # 找到最后的决定特征
    def final_stump(self, data, target, weights):
        feature_number = data.shape[1]
        min_error = float('inf')
        for i in range(feature_number):
            features = data[:, i]
            threshold, flag, error, result = self.decision_stump(features, target, weights)
            print('第', i, '个feature的stump_error = ', error)
            if error < min_error:
                min_error = error
                final_threshold = threshold
                final_flag = flag
                final_result = result
                final_feature = i
            if min_error == 0:
                break
        return final_feature, final_threshold, final_flag, min_error, final_result



# 对数几率回归
    # 对数几率函数
    def sigmoid(self, z):
        return np.where(z >= 1, 1 / (1 + np.exp(-z)), np.exp(z) / (1 + np.exp(z)))

    # 损失函数
    def log_loss(self, data, label, w, b, weights):
        result = self.sigmoid(np.dot(data, w) + b)
        loss = label - result
        dw = np.dot(data.T, loss)
        db = np.sum(loss)
        # loss = np.squeeze(loss)
        return result, loss, dw, db

    # 对数几率回归训练模型
    def logic_train(self, data, label, weights, learning_rate=0.01, epochs=1000):
        w = np.ones((data.shape[1], 1))
        b = 0
        for i in range(epochs):
            result, loss, dw, db = self.log_loss(data, label, w, b, weights)
            w += learning_rate * dw
            b += learning_rate * db
        return w, b, loss, result

    # adaboost的调整
    # 计算alpha
    def _alpha(self, error):
        return 0.5 * np.log((1 - error) / error)

    # 规范化因子
    def _Z(self, weights, alpha, result):
        return sum([weights[i] * np.exp(-1 * alpha * self.Y[i] * result[i]) for i in range(self.M)])

    # 权值更新
    def _w(self, alpha, result, Z):
        for i in range(self.M):
            self.weights[i] = self.weights[i] * np.exp(-1 * alpha * self.Y[i] * result[i]) / Z

    # adaboost的训练
    def fit(self, data, target, n_estimators, learning_rate):
        self.init_args(data, target, n_estimators, learning_rate)
        if self.base == 1:
            for epoch in range(self.clf_num):
                print('---------------基分类器', epoch, ' is running--------------------')
                min_error, final_threshold, final_result = 100000, 0, None
                # 在众多特征中，选出误差最小的特征
                final_feature, final_threshold, final_flag, min_error, final_result = self.final_stump(data, target,self.weights)
                # 计算G(x)系数a
                print('error = ', min_error)
                a = self._alpha(min_error)
                self.alpha.append(a)
                # 记录分类器
                self.clf_sets.append((final_feature, final_threshold, final_flag))
                Z = self._Z(self.weights, a, final_result)
                # 权值更新
                self._w(a, final_result, Z)
        else:
            for epoch in range(self.clf_num):
                print('---------------基分类器', epoch, ' is running--------------------')
                weight, inter, loss, result = self.logic_train(data, target, self.weights, learning_rate, 1000)
                self.clf_sets.append((weight, inter))
                final_result = self.logic_predict(data, weight, inter)
                error = sum([self.weights[k] for k in range(len(final_result)) if final_result[k] != target[k]])
                print('error = ', error)
                a = self._alpha(error)
                self.alpha.append(a)
                Z = self._Z(self.weights, a, final_result)
                # 权值更新
                self._w(a, final_result, Z)

    #决策树的预测函数
    def judge_result(self, test, threshold, flag):
        len_test = len(test)
        if flag == 1:
            result = np.array([1 if test[i] > threshold else -1 for i in range(len_test)])
        else:
            result = np.array([-1 if test[i] > threshold else 1 for i in range(len_test)])
        return result

    #对数几率回归的预测函数
    def logic_predict(self, data, w, b):
        y_pre = self.sigmoid(np.dot(data, w) + b)
        for i in range(len(y_pre)):
            if y_pre[i] > 0.5:
                y_pre[i] = 1
            else:
                y_pre[i] = 0
        return y_pre

    #adaboost的预测函数
    def predict(self, test):
        len_test = test.shape[0]
        result = np.mat(np.zeros((len_test, 1)))
        if self.base == 1:
            for i in range(len(self.clf_sets)):
                feature, threshold, flag = self.clf_sets[i]
                test_feature = test[:, feature]
                y = self.judge_result(test_feature, threshold, flag)
                a = self.alpha[i]
                for j in range(len(y)):
                    result[j] += a * y[j]
            final_result = np.array([1 if result[i] > 0 else 0 for i in range(len_test)])
            return final_result
        else:
            testmatrix = np.mat(test)
            for i in range(len(self.clf_sets)):
                w, b = self.clf_sets[i]
                y = self.logic_predict(testmatrix, w, b)
                # print(y)
                # print(result)
                a = self.alpha[i]
                for j in range(len(y)):
                    result[j] += a * y[j]
            final_result = np.array([1 if result[i] > 0.5 else 0 for i in range(len_test)])
            return final_result

#十折交叉验证生成样本
def kfold_split(data, label, fold):
    number_data, number_feature = np.shape(data)
    test_len = number_data // 10
    train_len = number_data - test_len
    train_data = np.zeros((train_len, number_feature))
    test_data = np.zeros((test_len, number_feature))
    train_label = np.zeros((train_len, 1))
    test_label = np.zeros((test_len, 1))
    k = 0
    for i in range(9):
        if i + 1 == fold:
            test_data[:, :] = data[i * test_len:(i + 1) * test_len, :]
            test_label[:] = label[i * test_len:(i + 1) * test_len]
        else:
            train_data[k * test_len:(k + 1) * test_len, :] = data[i * test_len:(i + 1) * test_len, :]
            train_label[k * test_len:(k + 1) * test_len] = label[i * test_len:(i + 1) * test_len]
            k += 1
    return train_data, train_label, test_data, test_label, test_len

#数据预处理
def pre_solve(data):
    num_data, num_feature = np.shape(data)
    for i in range(num_feature):
        temp = data[:, i]
        min_temp = np.min(temp)
        max_temp = np.max(temp)
        for j in range(num_data):
            temp[j] = (temp[j] - min_temp) / (max_temp - min_temp)
        data[:, i] = temp
    return data


if __name__ == '__main__':
    data = np.array(pd.read_csv('data.csv'))
    target = np.array(pd.read_csv('targets.csv'))
    data = pre_solve(data)
    base_list = [1, 5, 10, 100]  # 基分类器个数
    base = 1  # 选择基分类器
    ada = Adaboost(base)
    learning_rate = 0.5
    for base_num in base_list:
        for fold in range(1, 10):
            train_data, train_label, test_data, test_label, test_len = kfold_split(data, target, fold)
            if base == 1:
                learning_rate = 0.005
            else:
                learning_rate = 0.005
            ada.fit(train_data, train_label, base_num, learning_rate)
            result = ada.predict(test_data)
            final_result = np.zeros((len(result), 2), dtype=np.int)
            final_result[:, 0] = np.linspace(test_len * (fold - 1) + 1, test_len * fold, test_len)
            final_result[:, 1] = result
            accuracy = sum([1 for k in range(len(test_label)) if result[k] == test_label[k]])
            accuracy /= len(test_label)
            # print("prediction:", result)
            print(base_num, "个基分类器,第", fold, "验证，正确率为", accuracy)
            np.savetxt('experiments/base%d_fold%d.csv' % (base_num, fold), final_result, fmt='%d', delimiter=',')


