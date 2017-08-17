#ifndef STATE_H_
#define STATE_H_

class Context;//前置声明
class State
{
    public:
        State();
        virtual ~State();
        
        virtual void OperationInterface(Context *) = 0;
        virtual void OperationChangeState(Context *) = 0;

    protected:
        bool ChangeState(Context* con,State* st);
};

class ConcreateStateA: public State
{
    public:
        ConcreateStateA();
        virtual ~ConcreateStateA();

        virtual void OperationInterface(Context* con);
        virtual void OperationChangeState(Context * con);

};

class ConcreateStateB: public State
{
    public:
        ConcreateStateB();
        virtual ~ConcreateStateB();

        virtual void OperationInterface(Context* con);
        virtual void OperationChangeState(Context * con);

};


#endif
