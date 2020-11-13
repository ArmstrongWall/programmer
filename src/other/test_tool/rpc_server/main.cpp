#include <iostream>
#include "rpc/server.h"
#include "rpc/this_handler.h"

void foo() { std::cout<<"foo was called"<<std::endl; }

double divide(double a,double b)
{
	if(b==0)
		rpc::this_handler().respond_error("b can not  be zero");
	return a/b;

}

int main() {
	rpc::server srv("0.0.0.0",rpc::constants::DEFAULT_PORT);
	srv.bind("foo",&foo);
	srv.bind("add",[](int a,int b){ return a+b;});
	srv.bind("divide",&divide);
	srv.suppress_exceptions(true);
	srv.run();
	return 0;
}
