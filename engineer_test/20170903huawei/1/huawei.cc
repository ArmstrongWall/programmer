#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main()
{
   

    int score  =0;
    int st_num =0;
    int op_num =0;
    char op;
    int A=0,B=0;
    int i=0;



    while(cin >> st_num >> op_num)
    {

        vector<int> st_score;

        for(i=0;i<st_num;i++)
        {
            //cout << "num :"<< i <<endl;
            cin >> score;
            st_score.push_back(score);
        }

        /*for(i=0;i<st_score.size();i++)
        {
            cout << st_score[i]<<endl;
        }*/
        for(i=0;i<op_num;i++)
        {
            cin >> op >> A >> B;
            if(op == 'Q')
            {
                if(A > B)
              {
                int te = A;
                A = B;
                B = te;

              }

                vector<int> temp(st_score);
                sort(temp.begin()+A-1,temp.begin()+B,greater<long>());
                cout << endl<< temp[A-1] << endl;
                //result.push_back(temp[A-1]);
            }
            else if(op == 'U')
            {
                st_score[A-1] = B;
            }

        }

    }

    return 0;
}
