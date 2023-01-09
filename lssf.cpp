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

// void saveData(string fileName, MatrixXd matrix){
//    const static IOFormat CSVFormat(FullPrecision, DontAlignCols,", ","\n");
//    ofstream file(fileName);
//    if(file.is_open()){
//       file << matrix.format(CSVFormat);
//       file.close();
//    }
// }

MatrixXd openData(string fileToOpen)
{
 
    // the inspiration for creating this function was drawn from here (I did NOT copy and paste the code)
    // https://stackoverflow.com/questions/34247057/how-to-read-csv-file-and-assign-to-eigen-matrix
     
    // the input is the file: "fileToOpen.csv":
    // a,b,c
    // d,e,f
    // This function converts input file data into the Eigen matrix format
 
 
 
    // the matrix entries are stored in this variable row-wise. For example if we have the matrix:
    // M=[a b c 
    //    d e f]
    // the entries are stored as matrixEntries=[a,b,c,d,e,f], that is the variable "matrixEntries" is a row vector
    // later on, this vector is mapped into the Eigen matrix format
    vector<double> matrixEntries;
 
    // in this object we store the data from the matrix
    ifstream matrixDataFile(fileToOpen);
 
    // this variable is used to store the row of the matrix that contains commas 
    string matrixRowString;
 
    // this variable is used to store the matrix entry;
    string matrixEntry;
 
    // this variable is used to track the number of rows
    int matrixRowNumber = 0;
    
    getline(matrixDataFile, matrixRowString);
    matrixRowString = "";
 
    while (getline(matrixDataFile, matrixRowString)) // here we read a row by row of matrixDataFile and store every line into the string variable matrixRowString
    {
        stringstream matrixRowStringStream(matrixRowString); //convert matrixRowString that is a string to a stream variable.
        
        while (getline(matrixRowStringStream, matrixEntry, ',')) // here we read pieces of the stream matrixRowStringStream until every comma, and store the resulting character into the matrixEntry
        {
            // matrixEntries.push_back(matrixEntries.cast<double>(matrixEntry));   //here we convert the string to double and fill in the row vector storing all the matrix entries
            matrixEntries.push_back(stod(matrixEntry));
        }
        matrixRowNumber++; //update the column numbers
    }
 
    // here we convert the vector variable into the matrix and return the resulting object, 
    // note that matrixEntries.data() is the pointer to the first memory location at which the entries of the vector matrixEntries are stored;
    return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(matrixEntries.data(), matrixRowNumber, matrixEntries.size() / matrixRowNumber);
 
}
 
int main()
{
   vector<int> values(10000);
   auto start = high_resolution_clock::now();
   // int n;
   // int flag=0;
   // ifstream inputFile;
   // inputFile.open("incorrect.csv");
   // string line = "";
   MatrixXd A;
   // std::cout<<"Enter number of points: ";
   // cin>>n;
   // A.resize(n,3);

   A = openData("incorrect.csv");
   // B.resize(A.rows(),3);

   MatrixXd B = A.block(0, 0, A.rows(), 3);

   cout<<B;

   VectorXd f(3);
   f << 1, 1, 1;
   cout << "Here is the right hand side f:\n" << f <<endl;
   cout << "The least-squares solution using normal equations is:\n"
        << (B.transpose() * B).ldlt().solve(B.transpose() * f) <<endl;
      // <<(((B.transpose() * B).inverse())*B.transpose())* f<< endl;

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