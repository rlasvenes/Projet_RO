#ifndef DataSched_h
#define DataSched_h

#include <iostream>
#include <vector>

using namespace std;

class DataSched {
    public :
        int nbItems;
        vector<int> procTime; /* processing times */
        vector<int> penalty;  /* penalty per unit of time */
        vector<int> dueDate;  /* date for which the item is due */
        int makespan;         /* som of processing times */

    public :
        DataSched();
        void readDataFile(char* filename);
};

#endif
