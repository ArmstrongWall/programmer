#include<iostream>
#include"context.h"
#include"state.h"



Context::Context(){}

Context::Context(State* state)
{
    this->_state = state;
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
    this->_state = state;
    return 1;
}

void Context::OperationChangeState()
{
    _state->OperationChangeState(this);
}






