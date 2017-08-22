#include<iostream>
#include"context.h"
#include"state.h"

/*
 * Context在整个状态转换的过程中起着一个中间人的作用
 * 好比两个人进行商品交易，他们都来到一个共同的地方
 * 谈生意，在Context里面完成状态的交接
 * */

Context::Context(){}

Context::Context(State* state)
{
    this->_state = state;//指代私有变量为传入参数
}

Context::~Context()
{
    delete _state;
}
void Context::OperationInterface()
{
    _state->OperationInterface(this);
}

bool Context::ChangeState(State *state)
{
  //释放上一个申请的内存，不然会导致内存泄露
    State* st_temp = this->_state;
    delete st_temp;

    this->_state = state;
    return 1;
}

void Context::OperationChangeState()
{
    _state->OperationChangeState(this);
}






