#include <iostream>
#include <thread>
#include <sys/time.h>
using namespace std;

void hello(){
    while(true) {
        struct  timeval  time_start;
        gettimeofday(&time_start,NULL);
        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
        cout <<"hello time " <<  cost_time << endl;
    }

}

void hello2(){
    while(true) {
        struct  timeval  time_start;
        gettimeofday(&time_start,NULL);
        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
        cout <<"hello2 time " <<  cost_time << endl;
    }

}

int main() {

    cout.setf(ios::fixed);
    std::cout << "Hello, World!" << std::endl;

    std::thread t(hello);
    std::thread t2(hello2);

    t2.join();
    t.join();

    while(true) {
        struct  timeval  time_start;
        gettimeofday(&time_start,NULL);
        double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;
        cout <<"main time " <<  cost_time << endl;
    }


    return 0;
}