'''
    Simple implementation of Kalman Filter dynamic visualization
'''

import numpy as np
import matplotlib.pyplot as plt


def gaussian_noise_generator(num):
    return np.random.normal(loc=0, scale=num, size=None)

# 过程误差协方差矩阵Q   过程噪声分布P(w) ~ N(0, Q)
Q = np.array([[0.1, 0],
              [0, 0.1]])

# 测量误差协方差矩阵R   测量噪声分布P(v) ~ N(0, R)
R = np.array([[1, 0],
              [0, 1]])

# 状态转移矩阵A
A = np.array([[1, 1],
              [0, 1]])

# 状态观测矩阵H
H = np.array([[1, 0],
              [0, 1]])

# 控制输入矩阵B
B = None

# 单位矩阵I
I = np.array([[1, 0],
              [0, 1]])

# 初始化状态(位置与速度)
X0 = np.array([[0],
               [1]])

# 初始化状态估计协方差矩阵P
P = np.array([[1, 0],
               [0, 1]])


if __name__ == "__main__":
    # ----------------------- 初始化 ---------------------------
    X_true = np.array(X0)
    X_posterior = np.array(X0)
    P_posterior = np.array(P)

    pos_true = []    # 位置
    spd_true = []    # 速度

    pos_measure = []
    spd_measure = []

    pos_priori_est = []
    spd_priori_est = []

    pos_posteriori_est = []
    spd_posteriori_est = []

    plt.ion()
    for i in range(30):
        # ============ 预测部分 ===============
        # ------------ 生成真实值 -------------
        # 生成过程噪声
        w = np.array([[gaussian_noise_generator(Q[0, 0])],
                      [gaussian_noise_generator(Q[1, 1])]])
        # 得到当前时刻状态          
        X_true = np.dot(A, X_true) + w
        pos_true.append(X_true[0, 0])
        spd_true.append(X_true[1, 0])

        # ------------ 生成观测值 -------------
        # 生成观测噪声
        v = np.array([[gaussian_noise_generator(R[0, 0])],
                      [gaussian_noise_generator(R[1, 1])]])
        # 得到当前时刻测量值
        Z_measure = np.dot(H, X_true) + v
        pos_measure.append(Z_measure[0, 0])
        spd_measure.append(Z_measure[1, 0])

        # ------------- 先验估计 ---------------
        X_priori = np.dot(A, X_posterior)
        P_priori = np.dot(np.dot(A, P_posterior), A.T) + Q
        pos_priori_est.append(X_priori[0, 0])
        spd_priori_est.append(X_priori[1, 0])

        # ============= 校正部分 ================
        # ------------- 计算卡尔曼增益
        k1 = np.dot(P_priori, H.T)
        k2 = np.dot(np.dot(H, P_priori), H.T) + R
        K = np.dot(k1, np.linalg.inv(k2))       # K=k1/k2

        # ------------- 后验估计 ---------------
        X_posterior = X_priori + np.dot(K, (Z_measure - np.dot(H, X_priori)))
        pos_posteriori_est.append(X_posterior[0, 0])
        spd_posteriori_est.append(X_posterior[1, 0])

        # ------------- 更新误差协方差矩阵P ---------------
        P_posterior = np.dot((I - np.dot(K, H)), P_priori)


        # ------------- 动态可视化 -----------------
        plt.figure(1)
        plt.xlabel('k')
        plt.title('position')
        plt.plot(pos_true, color=[0.46,0.53,0.6], linewidth=1)
        plt.plot(pos_measure, color=[0,0.75,1], linewidth=1)
        plt.plot(pos_priori_est, color=[1,0.65,0], linewidth=1)
        plt.plot(pos_posteriori_est, color=[1,0.4,0.7], linewidth=1)

        plt.figure(2)
        plt.xlabel('k')
        plt.title('speed')
        plt.plot(spd_true, color=[0.46,0.53,0.6], linewidth=1)
        plt.plot(spd_measure, color=[0,0.75,1], linewidth=1)
        plt.plot(spd_priori_est, color=[1,0.65,0], linewidth=1)
        plt.plot(spd_posteriori_est, color=[1,0.4,0.7], linewidth=1)

        plt.pause(0.1)

    plt.figure(1)
    plt.plot(pos_true, color=[0.46,0.53,0.6], label = 'position true', linewidth=1)
    plt.plot(pos_measure, color=[0,0.75,1], label = 'position measure', linewidth=1)
    plt.plot(pos_priori_est, color=[1,0.65,0], label = 'position priori estimate', linewidth=1)
    plt.plot(pos_posteriori_est, color=[1,0.4,0.7], label = 'position posteriori estimate', linewidth=1)
    plt.legend()

    plt.figure(2)
    plt.plot(spd_true,color=[0.46,0.53,0.6], label = 'speed true', linewidth=1)
    plt.plot(spd_measure, color=[0,0.75,1], label = 'speed measure', linewidth=1)
    plt.plot(spd_priori_est, color=[1,0.65,0], label = 'speed priori estimate', linewidth=1)
    plt.plot(spd_posteriori_est, color=[1,0.4,0.7], label = 'speed posteriori estimate', linewidth=1)
    plt.legend()


    plt.ioff()
    plt.show()
