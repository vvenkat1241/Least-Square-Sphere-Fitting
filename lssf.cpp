#include <iostream>
#include "eigen-3.4.0\Eigen\Dense"
#include <algorithm>
#include <chrono>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;
using namespace std::chrono;
using namespace Eigen;
 
int main()
{
   vector<int> values(10000);
   auto start = high_resolution_clock::now();
   int n;
   int flag=0;
   ifstream inputFile;
   inputFile.open("incorrect.csv");
   string line = "";
   MatrixXf A;
   std::cout<<"Enter number of points: ";
   cin>>n;
   A.resize(n,3);
   while (getline(inputFile,line) || flag<=n){
        double x_n;
        double y_n;
        double z_n;
        double delta_x;
        double delta_y;
        double delta_z;
        double l2norm;
        string tempString = "";
        stringstream inputString(line);
        getline(inputString,tempString,'\n');
        tempString = "";
        getline(inputString,tempString,',');
        x_n=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        y_n=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        z_n=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        delta_x=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        delta_y=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        delta_z=atof(tempString.c_str());
        tempString = "";
        getline(inputString,tempString,',');
        line = "";
     //    A << x_n, y_n, z_n;
        MatrixXd B {x_n, y_n, z_n};
        A.resize(A.rows(), A.cols()+B.cols());
        A << A, B;
        flag++;
   }
   std::cout << "Here is the matrix A:\n" << A <<endl;
//    Eigen::VectorXd f(3);
//    f << 1, 1, 1;
//    cout << "Here is the right hand side f:\n" << f <<endl;
//    cout << "The least-squares solution using normal equations is:\n"
//         << (A.transpose() * A).ldlt().solve(A.transpose() * f) <<endl;
   auto stop = high_resolution_clock::now();
   auto duration = duration_cast<microseconds>(stop - start);
   std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
//    std::cout << "The least-squares solutions using JacobiSVD is:\n"
//         << A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(f) << std::endl;
//    std::cout << "The solution using the QR decomposition is:\n"
//      << A.colPivHouseholderQr().solve(f) << std::endl;
//    std::cout << "The least-squares solutions using BDCSVD is:\n"
//         << A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(f) << std::endl;
}
