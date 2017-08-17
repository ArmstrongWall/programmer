#include <iostream>
#include "context.h"
#include "state.h"

using namespace std;

State::State(){}
State::~State(){}

void State::OperationInterface(Context *con)
{
    cout << "State::.." <<endl;
}

bool State::ChangeState(Context *con,State *st)
{
    con->ChangeState(st);//实际运行了状态转换
    return 1;
}


ConcreateStateA::ConcreateStateA(){}
ConcreateStateA::~ConcreateStateA(){}

void ConcreateStateA::OperationInterface(Context *con)
{
    cout << "This is StateA OperationInterface" <<endl;
}

void ConcreateStateA::OperationChangeState(Context *con)
{
    OperationInterface(con);//打印了一些State A的文字
    this->ChangeState(con,new ConcreateStateB());
}

ConcreateStateB::ConcreateStateB(){}
ConcreateStateB::~ConcreateStateB(){}
void ConcreateStateB::OperationInterface(Context *con)
{
    cout << "This is StateB OperationInterface" <<endl;
}

void ConcreateStateB::OperationChangeState(Context *con)
{
    OperationInterface(con);//打印了一些State B的文字
    this->ChangeState(con,new ConcreateStateA()); //转变到状态A
}













