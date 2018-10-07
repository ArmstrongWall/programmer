## 误区1：
thread_planControl = std::thread(&planControl::planControlThreadLoop,this);
后直接就已经开始了线程了，而不是等到thread_planControl.join();时才开始线程。
