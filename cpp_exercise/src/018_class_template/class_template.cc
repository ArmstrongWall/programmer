#include <iostream>
#include "class_template.h"


int main()
{
    apollo_camera< int , int > camera1(1,2);
    camera1.show(); 

    apollo_camera< int , char > camera2(1,'s');
    camera2.show();


    apollo_camera< int , float > camera3(1,2.23443);
    camera3.show(); 
    
    return 0;
}

