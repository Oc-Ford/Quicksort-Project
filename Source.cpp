#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "GasWell.h"
using namespace std;

int main() {

    map<string, GasWell> wellMap;

    ifstream inputFile("gas_well_data.txt"); // Open file

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string wellName;
            int time, flow, pressure, temp;


            if (iss >> wellName >> time >> flow >> pressure >> temp) 
            {
                if (wellMap.find(wellName) == wellMap.end()) {
                    GasWell newWell(wellName);
                    wellMap[wellName] = newWell;
                }
                wellMap[wellName].addWellData(WellData(flow, pressure, temp));
            }
        }
        inputFile.close(); // Close file
    }
    else 
    {
        cout << "Unable to open file!" << std::endl;
        return 1;
    }


    // Displaying imported data
    for (const auto& well : wellMap) 
    {
        cout << "Well: " << well.second.wellName << " Data";
        for (const auto& data : well.second.getWellData())
        {
            cout << "Flow: " << data.flow << ", Pressure: " << data.pressure << ", Temperature: " << data.temperature << endl;
        }
        cout << std::endl;
    }

    vector<GasWell> sortedWells;
    for (auto& well : wellMap) {
        sortedWells.push_back(well.second);
    }

    GasWell().quicksortFlow(sortedWells, 0, sortedWells.size() - 1);

    cout << "Sorted Well Data Based on Flow Rate:\n";
    GasWell().printSortedWells(sortedWells);

    return 0;
}
