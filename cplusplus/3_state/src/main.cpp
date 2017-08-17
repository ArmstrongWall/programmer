#include <iostream>
#include "context.h"
#include "state.h"

int main(int argc,char** argv)
{
    std::cout << "Hello,learn state pattern" << std::endl;

    State *st = new ConcreateStateA();
    //实例化状态A

    Context *con = new Context(st);

    con->OperationChangeState();
    con->OperationChangeState();
    con->OperationChangeState();

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

