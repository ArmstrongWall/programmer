#include<iostream>

#include<functional>
#include<algorithm>
#include<vector>

using namespace std;

long Convert (long n)
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
   //sort(num.begin(),num.end(),greater<long>());

   sort(num.begin(),num.end());

    for(i=0;i<num.size();i++)
    {
        if(i==0)
        {
            s.push_back(num[i]);
        }
        else
        {
            if(num[i]!=s[s.size()-1])
            {

               s.push_back(num[i]);
            }
        }
    }
    
    for(i=0;i<s.size();i++)
    {
        cout << s[i] << endl;
        store += s[i]*ten;
        ten*=10;
        cout << store << endl;
    }

    return store;


}

int main()
{
    long n= 423234;  
    //cin >> n;                                                                                                                                                                                                        
    n = Convert(n); 

    cout << "n is"<<n << endl;                             

    return 0;
}
