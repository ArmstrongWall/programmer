#ifndef CLASS_TEMPLATE
#define CLASS_TEMPLATE

//define class template
template <typename T1 , typename T2>
class apollo_camera
{
    public:
        apollo_camera(T1 a,T2 b);
        void show();
    private:
        T1 I;
        T2 J;
};

//define class template member construct function
template <typename T1 , typename T2>
apollo_camera<T1,T2>::apollo_camera(T1 a,T2 b):I(a),J(b){}

//define class template member show function
template <typename T1 , typename T2>
void apollo_camera<T1,T2>::show()
{
    std::cout << "I = " << I <<  "; J = " << J << std::endl;
}


#endif
