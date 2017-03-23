#include <fstream>

#include "DataSched.hpp"

DataSched::DataSched(){}

void DataSched::readDataFile(char* filename){
  ifstream infile(filename);

  infile >> nbItems >> ws;
  penalty = vector<int>(nbItems);
  procTime = vector<int>(nbItems);
  dueDate = vector<int>(nbItems);
  makespan = 0;

  for (int i = 0; i < nbItems; i++){
    infile >> penalty[i] >> ws;
  }

  for (int i = 0; i < nbItems; i++){
    infile >> procTime[i] >> ws;
    makespan += procTime[i];
  }

  cout << "Makespan = " << makespan << endl;
  
  for (int i = 0; i < nbItems; i++){
    infile >> dueDate[i] >> ws;
  }
}
