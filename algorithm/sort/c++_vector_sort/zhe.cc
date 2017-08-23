#include<iostream>

#include<functional>
#include<algorithm>
#include<vector>

using namespace std;

long Sort (long n)
{
   vector<long> num;
   vector<long> s;
   
   long store = 0;

   int i=0;
   int ten =1;

   for(;;i++)
   {
       num.push_back(n%10);
       n=n/10;
       //cout << num[i] << endl;
       if(n==0)
           break;
   }
   sort(num.begin(),num.end(),greater<long>());//升序排序

   //sort(num.begin(),num.end(),less<long>());//降序排序


    
    for(i=0;i<num.size();i++)
    {
        cout << num[i] << endl;
       
    }

    return store;


}

int main()
{
    long n= 423234;  
    //cin >> n;                                                                                                                                                                                                        
    n = Sort(n); 
                

    return 0;
}
