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
</br>　　在倒立摆模型中，可以观测到状态量是角度![pic]( http://latex.codecogs.com/gif.latex?\theta)，角速度![pic]( http://latex.codecogs.com/gif.latex?\dot\theta)，接下来我们简化模型，
我们只需要去得到真实的角度和角速度，不要控制，控制姿态放到PID模型中。比如把这个倒立摆静置，然后去测量该系统的状态，
此时系统不受任何外力干扰，但是加速度计会受到机械振动的噪声干扰，陀螺仪会有零漂，温漂干扰，这些都是高斯噪声，那么怎么去描述这些
高斯噪声以求得R<sub>t</sub>和Q<sub>t</sub>，根据《Probabilistic Robotics》<sup>[2]</sup>，可以使用更高阶的状态量去表示观测状态量，
假设这个高阶量即角加速度服从高斯分布，这个有点难理解，想象一下倒立摆静置的情况下，它的观测的角度和角速度都在不断的跳变，这是因为
角加速度是个随机量，服从高斯分布，但是均值为0。设时间间隔为T，T很短，根据你的定时器的周期为10ms，系统线性，根据高中物理公式则有：
</br> 　　![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{x_t}=\begin{pmatrix}\theta_t\\\\\dot\theta_t\end{pmatrix}=\begin{pmatrix}1&T\\\\0&1\end{pmatrix}\begin{pmatrix}\theta_{t-1}\\\\\dot\theta_{t-1}\end{pmatrix}+\begin{pmatrix}\frac{1}{2}T^2\\\\T\end{pmatrix}\ddot\theta_{t-1})　　　　　　　　　　　　　　　　(3)
</br> 　　(3)式对应(1)式。可得：
</br> 　　![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{A_t}=\begin{pmatrix}1&T\\\\0&1\end{pmatrix}),
</br> 　　![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{B_t}=\boldsymbol{0}),
</br> 　　![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{R_t}=\begin{pmatrix}\frac{1}{4}T^4&\frac{1}{2}T^3\\\\\frac{1}{2}T^3&T^2\end{pmatrix}),
</br> 考虑观测模型：
</br> ![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{z_t}=\begin{pmatrix}\theta_t\\\\\dot\theta_t\end{pmatrix}=\begin{pmatrix}1&0\\\\0&1\end{pmatrix}\begin{pmatrix}\theta_{t}\\\\\dot\theta_{t}\end{pmatrix}+\boldsymbol{\delta_t}),
</br> 其中![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{\delta_t})很难衡量，分别是角度和和角速度的零均值高斯干扰量，
对应的Q<sub>t</sub>根据实际的测量值(使用MPU6050)去选取，见build/data.txt文件，根据初中统计数据知识算到![pic](http://latex.codecogs.com/gif.latex?cov[\theta,\theta]=E[[\theta-E[\theta]]^2]),![pic](http://latex.codecogs.com/gif.latex?cov[\theta,\dot\theta]=E[\theta\dot\theta]-E[\theta]E[\dot\theta]),![pic](http://latex.codecogs.com/gif.latex?cov[\dot\theta,\dot\theta]=E[[\dot\theta-E[\dot\theta]]^2])
</br>![pic](http://latex.codecogs.com/gif.latex?\boldsymbol{Q_t}=\begin{pmatrix}cov[\theta,\theta]&cov[\theta,\dot\theta]\\\\cov[\dot\theta,\theta]&cov[\dot\theta,\dot\theta]\end{pmatrix}=\begin{pmatrix}1023.684&0.221\\\\0.221&25.228\end{pmatrix}).
</br>由此可以建立卡尔曼算法，基于Eigen矩阵库使用C++编程可得到如下效果图，可以看到测量值跳变非常大，而中间的得到的滤波值跳变很小，黄色是角加速度值，由于只静置，所以得到的值在0附近，蓝色是加速度计测到的角度值，在-200左右。
</br>![pic](build/result.png)

