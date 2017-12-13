/*Athuor: Johnny Wang
 *Date:2017.12.9
 *Fuction: Kalman Filter
 *In&out: Angle
 *        Angular velocity
 */

#include "kalman.h"

KalmanFilter::KalmanFilter()
{
    A << 1,T,
         0,1;

    C << 1,0,
         0,1;
    
    R << 0.25*T*T*T*T*sigma_acceleration,    0.5*T*T*T*sigma_acceleration,
         0.5*T*T*T*sigma_acceleration,       T*T*sigma_acceleration;
    
    Q << 400  , 0.01,
         0.01 , 25;

    I = Eigen::Matrix<double, 2, 2>::Identity();
        
}

void KalmanFilter::Pridect(Eigen::Vector2d mu_last,Eigen::Matrix2d Sigma_last)
{
    mu_pridect = A*mu_last;
    Sigma_pridect = A*Sigma_last*A.transpose()+ R;
}

Eigen::Vector2d KalmanFilter::MeanUpdate(Eigen::Vector2d Observe)
{
    K = Sigma_pridect * C.transpose() * (C*Sigma_pridect*C.transpose()+Q).inverse();
    return mu_pridect + K*(Observe - C*mu_pridect);
}

Eigen::Matrix2d KalmanFilter::CovarienceUpdate()
{
    return (I - K*C)*Sigma_pridect;
}

void KalmanFilter::LoadData(const char* filename)
{
    printf("Loading %s...\n",filename);
    const char* pch = strstr(filename,".txt");
    if (pch != NULL)//check file is .txt
    {
        FILE* file = fopen(filename,"r");//read open file
        if (!file)                    
        {
            printf("load data file %s failed\n",filename);
            return ;
        }
    
        fseek(file,0,SEEK_SET);
         //move file pointer to file begin
 
        if (file)
        {
            char buffer[1000];
            fgets(buffer,300,file);
            //read every line data in ply file to buffer
            while (  strncmp( "num", buffer,strlen("num")) != 0  )
            //alawys read until meet "element vertex"
            {
                fgets(buffer,300,file);			
            }
            strcpy(buffer, buffer+strlen("num"));   
            //record data numbers
            sscanf(buffer,"%d", &totalnum);                    
            //copy 
            cout << "totalnum = " << totalnum << endl;
            
            for (int iterator = 0; iterator < totalnum; iterator++)
            {
                
                fgets(buffer,300,file);
                Eigen::Vector2d temp;
                sscanf(buffer,"%lf %lf", &temp(0) , & temp(1));
                //cout<<temp(0)<<"   "<<temp(1)<<"\n";
                data_observe.push_back(temp);
            }
            //cout << vertexlist.size() << endl;
            fclose(file);
            printf("%s Loaded!\n",filename);
    
        }
        else 
        { 
            printf("File can't be opened\n");
        }
    }	
    else 
    {
        printf("File does not have a .PLY extension. ");    
    }   
}
    

KalmanFilter1::KalmanFilter1()
{
    A << 1,0,
         0,1;

    C << 0,0;
    
    R << 0.01, 0,
         0, 0.01;
    
    Q = 0.001;

    I = Eigen::Matrix<double, 2, 2>::Identity();
        
}

void KalmanFilter1::Pridect(Eigen::Vector2d mu_last,Eigen::Matrix2d Sigma_last)
{
    mu_pridect = A*mu_last;
    Sigma_pridect = A*Sigma_last*A.transpose()+ R;
}

Eigen::Vector2d KalmanFilter1::MeanUpdate(double Observe)
{
    K = Sigma_pridect * C.transpose() * (1/(C*Sigma_pridect*C.transpose()+Q));
    //cout << K;
    return mu_pridect + K*(Observe - C*mu_pridect);
}

Eigen::Matrix2d KalmanFilter1::CovarienceUpdate()
{
    return (I - K*C)*Sigma_pridect;
}

void KalmanFilter1::LoadData(const char* filename)
{
    printf("Loading %s...\n",filename);
    const char* pch = strstr(filename,".txt");
    if (pch != NULL)//check file is .txt
    {
        FILE* file = fopen(filename,"r");//read open file
        if (!file)                    
        {
            printf("load data file %s failed\n",filename);
            return ;
        }
    
        fseek(file,0,SEEK_SET);
         //move file pointer to file begin
 
        if (file)
        {
            char buffer[1000];
            fgets(buffer,300,file);
            //read every line data in ply file to buffer
            while (  strncmp( "num", buffer,strlen("num")) != 0  )
            //alawys read until meet "element vertex"
            {
                fgets(buffer,300,file);			
            }
            strcpy(buffer, buffer+strlen("num"));   
            //record data numbers
            sscanf(buffer,"%d", &totalnum);                    
            //copy 
            cout << "totalnum = " << totalnum << endl;
            
            for (int iterator = 0; iterator < totalnum; iterator++)
            {
                
                fgets(buffer,300,file);
                double temp;
                sscanf(buffer,"%lf", &temp);
                //cout<<temp(0)<<"   "<<temp(1)<<"\n";
                data_observe.push_back(temp);
            }
            //cout << vertexlist.size() << endl;
            fclose(file);
            printf("%s Loaded!\n",filename);
    
        }
        else 
        { 
            printf("File can't be opened\n");
        }
    }	
    else 
    {
        printf("File does not have a .PLY extension. ");    
    }   
}




