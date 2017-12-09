卡尔曼滤波在倒立摆中的应用
===================================
　　对于一个线性高斯系统，我们认为它内部的状态在时刻ｔ是服从于均值为ｎ维向量![pic]( http://latex.codecogs.com/gif.latex?\boldsymbol{\mu_t})，协方差为n×n维矩阵![pic]( http://latex.codecogs.com/gif.latex?\boldsymbol{\Sigma_t})的高斯分布。使用（１）式描述该系统
　　　　　　　　　　![pic]( http://latex.codecogs.com/gif.latex?x_t=Ax_{t-1}+Bu_t+\varepsilon_t) 　　　　               　　　　　　　　　　　　　　　（１）
　　其中![pic]( http://latex.codecogs.com/gif.latex?x_t) 是系统在 t 时刻的 n 维状态描述向量，A 是系统向下一时刻的n×n维状态转移矩阵，![pic]( http://latex.codecogs.com/gif.latex?u_t)是m维控制向量 ，B 是n×m维矩阵，![pic]( http://latex.codecogs.com/gif.latex?\varepsilon_t) 是系统的 n 维噪声向量，是一个高斯随机变量，所有元素均值为0，n×n维协方差矩阵为R 。
