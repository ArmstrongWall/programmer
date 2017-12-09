/*Athuor: Johnny Wang
 *Date:2017.12.9
 *Fuction: Kalman Filter
 *In&out: Angle
 *        Angular velocity
 */
#ifndef KALMAN_H
#define KALMAN_H

#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>

#include "sophus/so3.h"
#include "sophus/se3.h"

using namespace std;

class KalmanFilter
{
public:
    KalmanFilter();
    void Pridect(Eigen::Vector2d mu_last,Eigen::Matrix2d Sigma_last);
    Eigen::Vector2d MeanUpdate(Eigen::Vector2d Observe);
    Eigen::Matrix2d CovarienceUpdate(); 
    void LoadData(const char* filename);
    
    virtual ~KalmanFilter() = default;
    
    Eigen::Vector2d mu_pridect;    
    //State mean posterior Vector
    Eigen::Matrix2d Sigma_pridect;
    //State Covarience posterior Matrix2d
    
private:
    double sigma_acceleration = 0.001;
    /*assume acceleration of Angle is Normal distribution
       ..
      Angle ~ N(0,0.001)
    */
    double T = 0.010;
    //Sample time interval 10ms
    Eigen::Matrix2d A;
    //State Trans Matrix
    Eigen::Matrix2d K;
    //Kalman gain Matrix
    Eigen::Matrix2d C;
    //State to Obervation Matrix
    Eigen::Matrix2d R;
    //Covarience Matrix of State
    Eigen::Matrix2d Q;
    //Covarience Matrix of Obervation
    Eigen::Matrix2d I;
    //Identity
    
    
//about data load:
public:
    int totalnum;
    vector<Eigen::Vector2d> data_observe;
    
};


#endif
