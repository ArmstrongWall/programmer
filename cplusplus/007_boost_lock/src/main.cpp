/*
 * 互斥体的概念有不少变种。Boost线程库支持两大类互斥体，包括简单互斥体（simple mutex)和递归互斥体（recursive mutex)。如果同一个线程对互斥体上了两次锁，就会发生死锁（deadlock），也就是说所有的等待解锁的线程将一直等下去。有了递归互斥体，单个线程就可以对互斥体多次上锁，当然也必须解锁同样次数来保证其他线程可以对这个互斥体上锁。

在这两大类互斥体中，对于线程如何上锁还有多个变种。一个线程可以有三种方法来对一个互斥体加锁：

1.一直等到没有其他线程对互斥体加锁。mutex

2.如果有其他互斥体已经对互斥体加锁就立即返回。try_mutex

3.一直等到没有其他线程互斥体加锁，直到超时。timed_mutex

似乎最佳的互斥体类型是递归互斥体，它可以使用所有三种上锁形式。然而每一个变种都是有代价的。所以Boost线程库允许你根据不同的需要使用最有效率的互斥体类型。Boost线程库提供了6中互斥体类型，下面是按照效率进行排序：
boost::mutex,
boost::try_mutex,
boost::timed_mutex,
boost::recursive_mutex,
boost::recursive_try_mutex,
boost::recursive_timed_mutex

        如果互斥体上锁之后没有解锁就会发生死锁。这是一个很普遍的错误，Boost线程库就是要将其变成不可能（至少时很困难）。直接对互斥体上锁和解锁对于Boost线程库的用户来说是不可能的。mutex类通过teypdef定义在RAII中实现的类型来实现互斥体的上锁和解锁。这也就是大家知道的Scope Lock模式。为了构造这些类型，要传入一个互斥体的引用。构造函数对互斥体加锁，析构函数对互斥体解锁。C++保证了析构函数一定会被调用，所以即使是有异常抛出，互斥体也总是会被正确的解锁。

        这种方法保证正确的使用互斥体。然而，有一点必须注意：尽管Scope Lock模式可以保证互斥体被解锁，但是它并没有保证在异常抛出之后贡献资源仍是可用的。所以就像执行单线程程序一样，必须保证异常不会导致程序状态异常。另外，这个已经上锁的对象不能传递给另一个线程，因为它们维护的状态并没有禁止这样做。

        List2给出了一个使用boost::mutex的最简单的例子。例子中共创建了两个新的线程，每个线程都有10次循环，在std::cout上打印出线程id和当前循环的次数，而main函数等待这两个线程执行完才结束。std::cout就是共享资源，所以每一个线程都使用一个全局互斥体来保证同时只有一个线程能向它写入。
 */
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

boost::mutex my_mutex;

void count(int id)
{
    for(int i=0 ; i<10 ; i++)
    {
        boost::mutex::scoped_lock lock(my_mutex);
        std::cout << "id = " << id << std::endl;
    }
    
    return;
}


int main(int argc,char** argv)
{
    
    boost::thread my_thread1(boost::bind(&count,1));
    boost::thread my_thread2(boost::bind(&count,2));
        
    my_thread1.join();
    my_thread2.join();
   
    return 0;
}

