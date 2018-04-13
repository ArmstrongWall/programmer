#include<iostream>
using namespace std;

void ConvertStr (char *s,  char* output)
{
    char* p_str;
    char* p_out;
    int count = 0;
    
    p_str = s;
    p_out = output;

    while(*p_str != '\0')
    {

        if(count%2==0)
        {
            *p_out = *p_str;
            p_out++;
        }

        count++;
        p_str++;
    }

    *p_out = '\0';

    if(count > 20)
        output="ERROR!";


    cout << count << endl;
    cout << output << endl;
}

int main()
{
     char s[] = "cdefg22es";                                                                                                                                                                                  
    char out[] = "a";    
    
    cin >> s;                                                                                                                                                                                                        
    ConvertStr(s,out); 
    cout << out << endl;                             

    return 0;
}
