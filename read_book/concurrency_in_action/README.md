## C2：线程管理
```
thread_planControl = std::thread(&planControl::planControlThreadLoop,this);
```
直接就已经开始了线程了，而不是等到thread_planControl.join();时才开始线程。

## C3：线程间共享数据
### 3.2.1 C++中使用互斥量
1.大多数情况下,互斥量通常会与保护的数据放
在同一个类中,而不是定义成全局变量。这是面向对象设计的准则:将其放在一个类中,就
可让他们联系在一起,也可对类的功能进行封装,并进行数据保护。

2.并不是说将所有可访问的数据结构代码标记为互斥就可以完成根本上的数据保护。

### 3.2.6	std::unique_lock
