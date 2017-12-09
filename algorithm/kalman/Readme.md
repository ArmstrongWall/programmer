卡尔曼滤波在倒立摆中的应用
===================================
　　对于一个线性高斯系统，我们认为它内部的状态在时刻ｔ是服从于均值为ｎ维向量![pic]( http://latex.codecogs.com/gif.latex?\boldsymbol{\mu_t})，
协方差为n×n维矩阵![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\Sigma_t})的高斯分布。而![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\overline{\mu_t}})和![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\overline{\Sigma_t}})为
系统的状态预测均值与协方差。使用(1)式描述该系统</br>　　　　　　　　　　　　　　　
![pic]( http://latex.codecogs.com/gif.latex?x_t=\boldsymbol{A_t}x_{t-1}+\boldsymbol{B_t}u_t+\boldsymbol{\varepsilon_t}) 　　　　               　　　　　　　　　　　　　　　(1)
</br>其中![pic]( http://latex.codecogs.com/gif.latex?x_t) 是系统在 t 时刻的 n 维状态描述向量，
A<sub>t</sub> 是系统向下一时刻的n×n维状态转移矩阵，![pic]( http://latex.codecogs.com/gif.latex?u_t)是m维控制向量，
B<sub>t</sub> 是n×m维矩阵，![pic]( http://latex.codecogs.com/gif.latex?\varepsilon_t) 是系统在 t 时刻的 n 维噪声向量，
是一个高斯随机变量，所有元素均值为0，n×n维协方差矩阵为R<sub>t</sub> 。
</br>![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\varepsilon_t}=\begin{pmatrix}\varepsilon_1\\\\\varepsilon_2\\\\\vdots\\\\\varepsilon_n\end{pmatrix}),
![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{R_t}=\begin{pmatrix}cov[\varepsilon_1,\varepsilon_1]&cov[\varepsilon_1,\varepsilon_2]&\cdots&cov[\varepsilon_1,\varepsilon_n]\\\\cov[\varepsilon_2,\varepsilon_1]&cov[\varepsilon_2,\varepsilon_2]&\cdots&cov[\varepsilon_2,\varepsilon_n]\\\\\vdots&\ddots&&\vdots\\\\cov[\varepsilon_n,\varepsilon_1]&cov[\varepsilon_n,\varepsilon_2]&\cdots&cov[\varepsilon_n,\varepsilon_n]\end{pmatrix})，
</br>　　使用(2)式去观测这个系统：
</br>　　　　　　　　　　　　　　　![pic]( http://latex.codecogs.com/gif.latex?z_t=\boldsymbol{C_t}x_{t}+\boldsymbol{\delta_t}) 　　　　　　　　　　　　　　　　　　　　           　   (2)    
</br>其中![pic]( http://latex.codecogs.com/gif.latex?z_t)是k维的状态观测向量，C<sub>t</sub>是k×n维矩阵，
![pic]( http://latex.codecogs.com/gif.latex?\delta_t) 是系统在 t 时刻的 n 维观测噪声向量，
是一个高斯随机变量，所有元素均值为0，n×n维协方差矩阵为Q<sub>t</sub> 。
</br>![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\delta_t}=\begin{pmatrix}\delta_1\\\\\delta_2\\\\\vdots\\\\\delta_k\end{pmatrix}),
![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{Q_t}=\begin{pmatrix}cov[\delta_1,\delta_1]&cov[\delta_1,\delta_2]&\cdots&cov[\delta_1,\delta_k]\\\\cov[\delta_2,\delta_1]&cov[\delta_2,\delta_2]&\cdots&cov[\delta_2,\delta_k]\\\\\vdots&\ddots&&\vdots\\\\cov[\delta_k,\delta_1]&cov[\delta_k,\delta_2]&\cdots&cov[\delta_k,\delta_k]\end{pmatrix})，
</br>
　　由《Probabilistic Robotics》<sup>[1]</sup>中,得到卡尔曼滤波的算法，
</br>　　![pic](1.png)
