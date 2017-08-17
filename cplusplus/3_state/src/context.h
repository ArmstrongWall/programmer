#ifndef CONTXET_H_
#define CONTEXT_H_

class State;

class Context
{
    public:
        Context();
        Context(State* state);
        ~Context();
        void OperationInterface();
        void OperationChangeState();

    private:
        friend class State;//表明在State类中可以访问Context的成员
        bool ChangeState(State *state);

    private:
        State* _state;

};


#endif
