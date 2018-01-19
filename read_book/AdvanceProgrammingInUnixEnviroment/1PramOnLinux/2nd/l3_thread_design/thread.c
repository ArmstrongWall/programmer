#include<pthread.h>
#include<stdio.h>
pthread_t  thread[2];//线程号
int number = 0;
pthread_mutex_t mut;//线程互斥锁
void *worker1()
{
    int i=0;
    printf("I am worker1\r\n");
    for(i=0;i<10;i++)
    {
        pthread_mutex_lock(&mut);//打开线程互斥锁
        number+=1;
        pthread_mutex_unlock(&mut);//解开线程互斥锁
        printf("worker1 number is %d\r\n",number);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *worker2()
{
    int i=0;
    printf("I am worker2\r\n");
    for(i=0;i<10;i++)
    {
        pthread_mutex_lock(&mut);
        number+=1;
        pthread_mutex_unlock(&mut);
        printf("worker2 number is %d\r\n",number);
        sleep(1);
    }
    pthread_exit(NULL);

}

int main()
{
    //线程互斥锁初始化
    pthread_mutex_init(&mut,NULL);
    //创建工人1线程
    pthread_create(&thread[0],NULL,worker1,NULL);
    //创建工人2线程
    pthread_create(&thread[1],NULL,worker2,NULL);
    //等待工人1线程结束
    pthread_join(thread[0],NULL);
    //等待工人2线程结束
    pthread_join(thread[1],NULL);

    return 0;

}
