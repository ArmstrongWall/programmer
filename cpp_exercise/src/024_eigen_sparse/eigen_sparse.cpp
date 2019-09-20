/**
 * Copyright© 2016-2018. UISEE (SHANGHAI) AUTOMOTIVE TECHNOLOGIES LTD. All rights reserved.
 * LICENSE AGREEMENT
 * The copy of the SOFTWARE is licensed, not sold.
 * Customer owns any media on which the SOFTWARE is recorded, but UISEE and its licensors or
 * suppliers retain ownership of the copy of the SOFTWARE itself, including all copyrights and
 * other intellectual property rights in and to the SOFTWARE (including but not limited to all
 * images, photographs, animations, video, audio, music, text, and other information incorporated
 * into the SOFTWARE), the accompanying printed materials, and any copies of the SOFTWARE.
 * The SOFTWARE is protected by copyright laws and international treaty provisions. Accordingly,
 * Customer is required to treat the SOFTWARE like any other copyrighted material,except as
 * otherwise allowed pursuant to this AGREEMENT and that it may make one copy of the SOFTWARE
 * solely for backup or archive purposes, provided that Customer reproduces all copyright and
 * proprietary notices that are on the original copy. The algorithms, structure, organization
 * and source code of the SOFTWARE are the valuable trade secrets and confidential
 * information of UISEE. Except as otherwise expressly provided herein, neither this AGREEMENT
 * nor UISEE grants Customer any express or implied right under any UISEE patents, copyrights,
 * trademarks, or other intellectual property rights in the SOFTWARE, and all rights, title
 * and interest in and to the SOFTWARE not expressly granted are reserved by UISEE or its
 * licensors or suppliers.
 *
 * @file   eigen_sparse.cpp
 * @brief  
 * @author Ziqiang Wang
 * @email  ziqiang.wang@uisee.com
 * @Date   19-9-18
 *----------------------------------------------------------------------------*
 *  Remark         : Description                                              *
 *----------------------------------------------------------------------------*
 *  Change History :                                                          *
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  19-9-18    | 1.0.0.0   | Ziqiang Wang   | Create file                     *
 *----------------------------------------------------------------------------*
 *                                                                            *
 */

#include "eigen_sparse.h"
#include <chrono>
#include <Eigen/Sparse>
#include <vector>
#include <iostream>
typedef Eigen::SparseMatrix<double> SpMat; // declares a column-major sparse matrix type of double
typedef Eigen::Triplet<double> T;

double get_machine_timestamp_s() {
    std::chrono::time_point<std::chrono::system_clock, std::chrono::microseconds> tp = std::chrono::time_point_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::microseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::cout <<"now timestamp: " << std::setiosflags(std::ios::fixed) << std::setprecision(8) << (static_cast<double>(timestamp))/1000000.0  <<std::endl;
    return (static_cast<double>(timestamp)) / 1000000.0;
}

void insertCoefficient(int id, int i, int j, double w, std::vector<T>& coeffs,
                       Eigen::VectorXd& b, const Eigen::VectorXd& boundary)
{
    int n = int(boundary.size());
    int id1 = i+j*n;
    if(i==-1 || i==n) b(id) -= w * boundary(j); // constrained coefficient
    else  if(j==-1 || j==n) b(id) -= w * boundary(i); // constrained coefficient
    else  coeffs.push_back(T(id,id1,w));              // unknown coefficient
}
void buildProblem(std::vector<T>& coefficients, Eigen::VectorXd& b, int n)
{
    b.setZero();
    Eigen::ArrayXd boundary = Eigen::ArrayXd::LinSpaced(n, 0,M_PI).sin().pow(2);
    for(int j=0; j<n; ++j)
    {
        for(int i=0; i<n; ++i)
        {
            int id = i+j*n;
            insertCoefficient(id, i-1,j, -1, coefficients, b, boundary);
            insertCoefficient(id, i+1,j, -1, coefficients, b, boundary);
            insertCoefficient(id, i,j-1, -1, coefficients, b, boundary);
            insertCoefficient(id, i,j+1, -1, coefficients, b, boundary);
            insertCoefficient(id, i,j,    4, coefficients, b, boundary);
        }
    }
}
void saveAsBitmap(const Eigen::VectorXd& x, int n, const char* filename)
{
    Eigen::Array<unsigned char,Eigen::Dynamic,Eigen::Dynamic> bits = (x*255).cast<unsigned char>();
    QImage img(bits.data(), n,n,QImage::Format_Indexed8);
    img.setColorCount(256);
    for(int i=0;i<256;i++) img.setColor(i,qRgb(i,i,i));
    img.save(filename);
}
int eigen_sparse()
{


    int n = 100;  // size of the image
    int m = n*n;  // number of unknows (=number of pixels)
    // Assembly:
    std::vector<T> coefficients;            // list of non-zeros coefficients
    Eigen::VectorXd b(m);                   // the right hand side-vector resulting from the constraints
    //buildProblem(coefficients, b, n);
    SpMat A(m,m);
    //A.setFromTriplets(coefficients.begin(), coefficients.end());

    for(int j=0; j< 6; ++j)
    {
        for(int i=0; i<6; ++i)
        {
            A.insert(i,j) = i * j;
        }
    }
    for(int j=6; j < m; ++j) {
       A.insert(j,j) = j;
    }

    for(int j=0; j < m; ++j) {
        b[j] = j;
    }



    double start_time = get_machine_timestamp_s();
    // Solving:
    Eigen:: SimplicialCholesky<SpMat> chol(A);  //SimplicialLLT SimplicialCholesky SimplicialLLT   performs a Cholesky factorization of A
    Eigen::VectorXd x = chol.solve(b);         // use the factorization to solve for the given right hand side
    double end = get_machine_timestamp_s();
    std::cout <<",stereo_time:" << end -  start_time<<" s\n";

//    std::cout << "A = \n"<< A << std::endl;
//    std::cout << "b = \n"<< b << std::endl;
//    std::cout << "x = \n"<< x << std::endl;

    // Export the result to a file:
    saveAsBitmap(x, n, "./app.jpg");
    return 0;
}