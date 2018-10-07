#include <cstdint>
#include <cassert>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include "data.h"

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
#include <iomanip>
int f() { return 42; }

int main()
{
    int i = 7;
    int64_t time_stamp = 1528351008071434;
    std::cout << "time_stamp=" << time_stamp << '\n';




    // pointer to integer and back
    std::uintptr_t v1 = reinterpret_cast<std::uintptr_t>(&i); // static_cast is an error
    std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
    int* p1 = reinterpret_cast<int*>(v1);
    assert(p1 == &i);

    // pointer to function to another and back
    void(*fp1)() = reinterpret_cast<void(*)()>(f);
    // fp1(); undefined behavior
    int(*fp2)() = reinterpret_cast<int(*)()>(fp1);
    std::cout << std::dec << fp2() << '\n'; // safe

    // type aliasing through pointer
    char* p2 = reinterpret_cast<char*>(&i);
    if(p2[0] == '\x7')
        std::cout << "This system is little-endian\n";
    else
        std::cout << "This system is big-endian\n";

    // type aliasing through reference
    reinterpret_cast<unsigned int&>(i) = 42;
    std::cout << i << '\n';

    [[maybe_unused]] const int &const_iref = i;
    //int &iref = reinterpret_cast<int&>(const_iref); //compiler error - can't get rid of const
    //Must use const_cast instead:  int &iref = const_cast<int&>(const_iref);


    VehicleState st(134,1245);


    memcpy(&_buffer,&st, sizeof(VehicleState));

    std::string str ;

    str.assign(reinterpret_cast<const char *>(_buffer), sizeof(VehicleState));

    std::cout << _buffer[0] << '\n';

    const VehicleState *st_cpy;

    uint8_t (* pbuff) = &_buffer[0];
    uint8_t (* pbuff1)[2048] = &_buffer;
    const uint8_t * pbuff2 = reinterpret_cast<const uint8_t *>(str.data());

    st_cpy = reinterpret_cast< const VehicleState* > (pbuff2);

    std::cout << st_cpy->time_stamp << '\n';

  std::cout <<std::setiosflags(std::ios::fixed);
  struct  timeval  time_start;

  while (1) {
    gettimeofday(&time_start,nullptr);
    double cost_time  = (time_start.tv_sec)+(time_start.tv_usec)/1000000.0;

    std::cout <<"cost time " <<  std::setprecision(10) <<cost_time << std::endl;
  }



  return 0;



}

