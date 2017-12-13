/*Athuor: Johnny Wang
 *Date:2017.12.9
 *Fuction: Kalman Filter
 *In&out: Angle
 *        Angular velocity
 */

#include <iostream>
#include <cmath>
#include <iomanip>


#include <Eigen/Core>
#include <Eigen/Geometry>



#include "kalman/kalman.h"

int main(int argc,char** argv)
{
    
     
//     KalmanFilter* kalman = new KalmanFilter();
//     kalman->LoadData("data.txt");
//     
//     Eigen::Vector2d mu_last;
//     mu_last << -200,0;
//     Eigen::Matrix2d Sigma_last;
//     Sigma_last << 0,0,0,0;
//     cout.setf(ios::fixed);
//             
//     for(int i = 0 ; i < kalman->totalnum - 1; i++)
//     {
//         kalman->Pridect(mu_last,Sigma_last);
//         mu_last    = kalman->MeanUpdate(kalman->data_observe[i]);
//         Sigma_last = kalman->CovarienceUpdate();
//        
//         //cout << "count = " << i << endl << mu_last << endl;
//         cout  << setprecision(4) << mu_last[0] << " " << setprecision(4) << mu_last[1] << endl;
//         
//     }
    
    KalmanFilter1* kalman = new KalmanFilter1();
    kalman->LoadData("data.txt");
    
    Eigen::Vector2d mu_last;
    mu_last << 2.3,10;
    Eigen::Matrix2d Sigma_last;
    Sigma_last << 0.01,0,0,0.01;
    cout.setf(ios::fixed);
            
    for(int i = 0 ; i < kalman->totalnum - 1; i++)
    {
        kalman->C << kalman->data_observe[i],1;
        kalman->Pridect(mu_last,Sigma_last);
        mu_last    = kalman->MeanUpdate(kalman->data_observe[i]);
        Sigma_last = kalman->CovarienceUpdate();
        //cout << Sigma_last<< endl;
        //cout << "count = " << i << endl << mu_last << endl;
        cout  << setprecision(4) << mu_last[0] << " " << setprecision(4) << mu_last[1] << endl;
        
    }
        
   
    return 0;
}

