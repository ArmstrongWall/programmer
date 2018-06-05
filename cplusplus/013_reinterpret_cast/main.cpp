#include <cstdint>
#include <cassert>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include "data.h"



int f() { return 42; }

int main()
{
    int i = 7;

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





}