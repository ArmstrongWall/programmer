#include <iostream>
#include "context.hpp"
#include "state.h"

int main(int argc,char** argv)
{
    std::cout << "Hello,learn state pattern" << std::endl;

    State *st = new ConcreateStateA();
    //实例化状态A

    Context *con = new Context(st);

    long count = 0;

    while(1)
    {
      con->OperationChangeState();
      count ++;
      std::cout<< count << std::endl;

    }

    if(con != NULL)
    {
        delete con;
    }

    if(st != NULL)
    {
        delete st;
    }

    return 0;
}

