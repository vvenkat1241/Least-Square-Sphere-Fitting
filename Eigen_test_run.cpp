#include <iostream>
#include <Eigen/Dense>
 
int main()
{
   Eigen::MatrixXd A(3,4);
   A << 2, 0, 0, 1, 0, 2, 0, 1, 0, 0, 2, 1;
   std::cout << "Here is the matrix A:\n" << A << std::endl;
   Eigen::VectorXd f(3);
   f << 1, 1, 1;
   std::cout << "Here is the right hand side f:\n" << f << std::endl;
   std::cout << "The least-squares solution using normal equations is:\n"
        << (A.transpose() * A).ldlt().solve(A.transpose() * f) << std:: endl;
   std::cout << "The least-squares solutions using JacobiSVD is:\n"
        << A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(f) << std::endl;
   std::cout << "The solution using the QR decomposGition is:\n"
     << A.colPivHouseholderQr().solve(f) << std::endl;
   std::cout << "The least-squares solutions using BDCSVD is:\n"
        << A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(f) << std::endl;
}