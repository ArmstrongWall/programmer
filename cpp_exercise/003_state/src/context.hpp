#ifndef CONTXET_H_
#define CONTEXT_H_

#include"state.h"
class State;
/*
 * Context在整个状态转换的过程中起着一个中间人的作用
 * 好比两个人进行商品交易，他们都来到一个共同的地方
 * 谈生意，在Context里面完成状态的交接
 * */

class Context
{
    friend class State;//表明在State类中可以访问Context的成员
    public:
        Context() = default;
        explicit  Context(State* state){
            this->_state = state;//指代私有变量为传入参数
        }
        ~Context(){
            delete _state;
        }
        void OperationInterface(){
            _state->OperationInterface(this);
        }
        void OperationChangeState(){
            _state->OperationChangeState(this);
        }

    private:

        bool ChangeState(State *state){
            //释放上一个申请的内存，不然会导致内存泄露
            State* st_temp = this->_state;
            delete st_temp;

            this->_state = state;
            return 1;
        }

    private:
        State* _state;

};


#endif
