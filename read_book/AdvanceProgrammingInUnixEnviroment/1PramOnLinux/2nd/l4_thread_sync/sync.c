//使用条件变量完成线程同步
#include<pthread.h>
#include<stdio.h>
pthread_t thread[2];
pthread_mutex_t mux;
int number = 0;
pthread_cond_t cond_ready=PTHREAD_COND_INITIALIZER;
//定义条件变量
void *studentA()
{
    int i= 0;
    for(i=0;i<5;i++)
    {
        //扫一次地
        pthread_mutex_lock(&mux);
        number+=1;
        if(number >= 5)
        {

            printf("A finish work\r\n");
            //通知B同学
            pthread_cond_signal(&cond_ready);//工作完成，通知另一个线程
        }
        pthread_mutex_unlock(&mux);
        //休息一分钟
        sleep(1);
    }

    //退出
    pthread_exit(NULL);
}

void *studentB()
{
        pthread_mutex_lock(&mux);
        if(number < 5)
        {
           pthread_cond_wait(&cond_ready,&mux);//等待被通知，这个函数会自动unlock互斥量
        }
        
    number = 0;
    pthread_mutex_unlock(&mux);
    printf("srtudent B finish\r\n");

    pthread_exit(NULL);
}

int main()
{
    //初始化线程互斥锁
    pthread_mutex_init(&mux,NULL);
    //创建A同学线程
    pthread_create(&thread[0],NULL,studentA,NULL);
    //创建B同学线程
    pthread_create(&thread[1],NULL,studentB,NULL);
    //等待A同学线程结束
    pthread_join(thread[0],NULL);
    //等待B同学线程结束
    pthread_join(thread[1],NULL);
    return 0;
}

/*
#include<pthread.h>
#include<stdio.h>
pthread_t thread[2];
pthread_mutex_t mux;
int number = 0;
void *studentA()
{
    int i= 0;
    for(i=0;i<5;i++)
    {
        //扫一次地
        pthread_mutex_lock(&mux);
        number+=1;
        if(number >= 5)
            printf("A finish work\r\n");
        pthread_mutex_unlock(&mux);
        //休息一分钟
        sleep(1);
    }

    //退出
    pthread_exit(NULL);
}

void *studentB()
{
    while(1)
    {    //判断A同学是否已经扫完5次地
        pthread_mutex_lock(&mux);
        if(number >= 5)
        {
           //拖地
            number = 0;

            pthread_mutex_unlock(&mux);
            printf("B finish his work\r\n");
           break;
        }
        else
        {

            pthread_mutex_unlock(&mux);
            //睡眠2秒钟
            sleep(2);
        }
    }

    pthread_exit(NULL);
}

int main()
{
    //初始化线程互斥锁
    pthread_mutex_init(&mux,NULL);
    //创建A同学线程
    pthread_create(&thread[0],NULL,studentA,NULL);
    //创建B同学线程
    pthread_create(&thread[1],NULL,studentB,NULL);
    //等待A同学线程结束
    pthread_join(thread[0],NULL);
    //等待B同学线程结束
    pthread_join(thread[1],NULL);
    return 0;
}
*/
