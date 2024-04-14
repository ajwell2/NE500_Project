//  csvwrite.h
//  Author: A. Wells
//  Date:   2022-07-22

//  Description:
//  Provides basic utility for exporting 2D data vector in .csv format

//  Note:
//  Input data must be flattened prior to export: data[][] = {data[row1], data[row2], ...}

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

//  write2csv:  writes data from vector to .csv
void write2csv(vector<double>& data, string fileName, int& width, int& length)
{
      std::ofstream myfile;
      myfile.open (fileName);
      for(int x2 = 0; x2 < length; x2++){
          for(int x1 = 0; x1 < width; x1++){
              myfile << data[x1 + (width * x2)] << ",";
          }
          myfile << "\n";
      }
      myfile.close();
      cout << "data written to " << fileName << endl;
}