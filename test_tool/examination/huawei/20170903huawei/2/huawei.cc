#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    int count = 0;
    vector<string> error_set;
    vector<int>    error_count;

    while(1)
    {
        string record;
        string row_num;
        cin >> record >> row_num;
        record.append(" ");
        record.append(row_num);

        for(int i=record.size();i>=0;i--)


        error_set.push_back(record);


        cout << record << endl;   
        cout << record.size() << endl;   
        if(record.size()>16)
        {
            for(int i=record.size()-16,j=0;i<record.size();i++,j++)
            {
                record[j]=record[i];
            }
            record.erase(16,record.size());
        }
        cout << record << endl;   
    }
    

    return 0;
}
