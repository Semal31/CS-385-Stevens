/*******************************************************************************
* Name    : powergrid.cpp
* Author  : Semal Shah
* Version : 1.0
* Date    : December 16, 2020
* Description : Determine the quickest way around town
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int num_vertices;

bool kruskals(vector<vector<int>> &converteddatasorted, vector<vector<int>> &converteddatasortedanditerated) {
    const int vertices = num_vertices;
    int *track = new int[vertices + 1];
    for (int i = 1; i <= num_vertices; i++) {
        track[i] = 4200;
    }
    int groupCounter = 0;
    bool isDone = false;
    bool isSolution = true;
    while(!isDone) {
        for (size_t i = 0; i < converteddatasorted.size(); i++) {
            int vertex1 = converteddatasorted[i][0];
            int vertex2 = converteddatasorted[i][1];
            if (track[vertex1] == 4200 && track[vertex2] == 4200) {
                track[vertex1] = groupCounter;
                track[vertex2] = groupCounter;
                groupCounter++;
                converteddatasortedanditerated.push_back(converteddatasorted[i]);
            } else if (track[vertex1] == 4200 || track[vertex2] == 4200) {
                if (track[vertex1] == 4200) {
                    track[vertex1] = track[vertex2];
                    converteddatasortedanditerated.push_back(converteddatasorted[i]);
                }
                if (track[vertex2] == 4200) {
                    track[vertex2] = track[vertex1];
                    converteddatasortedanditerated.push_back(converteddatasorted[i]);
                }
            } else if (track[vertex1] == track[vertex2]) {
                continue;
            } else if (track[vertex1] != track[vertex2]) {
                int oldGroup = track[vertex2];
                for (int j = 1; j <= num_vertices; j++) {
                    if (track[j] == oldGroup)
                        track[j] = track[vertex1];
                }
                converteddatasortedanditerated.push_back(converteddatasorted[i]);
            }
            int howMany = 0;
            for (int k = 1; k <= num_vertices; k++) {
                int groupNumber = track[vertex1];
                if (track[k] == groupNumber)
                    howMany++;
            }
            if (howMany == num_vertices) {
                isDone = true;
                break;
            }
        }
        if (!isDone) {
            isDone = true;
            isSolution = false;
        }
        delete[] track;
    }
    return isSolution;
}

void convert(vector<vector<string>> &data, vector<vector<int>> &converteddata) {
    int vertex1;
    int vertex2;
    int length;
    for (size_t i = 0; i < data.size(); i++) {
        vector<int> temp;
        vertex1 = stoi(data[i][0]);
        vertex2 = stoi(data[i][1]);
        length = stoi(data[i][2]);
        temp.push_back(vertex1);
        temp.push_back(vertex2);
        temp.push_back(length);
        temp.push_back(i);
        converteddata.push_back(temp);
    }
}

void convertBack(vector<vector<int>> &converteddataiterated, vector<vector<string>> &data, vector<vector<string>> &finaldata) {
    for (size_t i = 0; i < converteddataiterated.size(); i++) {
        finaldata.push_back(data[converteddataiterated[i][3]]);
    }
}

bool sortVectorHelper(const vector<int> &length1, const vector<int> &length2) {
    return length1[2] < length2[2];
}

void sortVectorofVectors(vector<vector<int>> &converteddata) {
    sort(converteddata.begin(), converteddata.end(), sortVectorHelper);
}

bool sortStreetVectorHelper(const vector<string> &street1, const vector<string> &street2) {
    return street1[3] < street2[3];
}

void sortByStreet(vector<vector<string>> &finaldata) {
    sort(finaldata.begin(), finaldata.end(), sortStreetVectorHelper);
}

int addTotal(vector<vector<string>> &finaldata) {
    int sum = 0;
    for (size_t i = 0; i < finaldata.size(); i++) {
        sum += stoi(finaldata[i][2]);
    }
    return sum;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;

    vector<vector<string>> data;

    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        getline(input_file, line);
        istringstream iss(line);
        if (!(iss >> num_vertices) || (num_vertices > 1000 || num_vertices < 1)) {
            cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
            return 1;
        }
        line_number++;
        while (getline(input_file, line)) {
            istringstream iss(line);

            //iterates through the line and puts each edge and edgeWeight in the vector as separate object
            vector<string> linevector;
            string str;
            while(getline(iss, str, ',')) {
                if (!str.empty()) {
                    linevector.push_back(str);
                }
            }

            if (linevector.size() != 4) {
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                return 1;
            }

            int vertex1 = 0;
            int vertex2 = 0;
            int length = 0;

            iss.clear();
            iss.str(linevector[0]);
            if (!(iss >> vertex1) || vertex1 < 1 || vertex1 > num_vertices || stof(linevector[0]) != vertex1) {
                cerr << "Error: Starting vertex '" << linevector[0] << "' on line " << line_number << " is not among valid values 1-" << num_vertices << "." << endl;
                return 1;
            }
            iss.clear();

            iss.str(linevector[1]);
            if (!(iss >> vertex2) || vertex2 < 1 || vertex2 > num_vertices || stof(linevector[1]) != vertex2) {
                cerr << "Error: Ending vertex '" << linevector[1] << "' on line " << line_number << " is not among valid values 1-" << num_vertices << "." << endl;
                return 1;
            }
            iss.clear();

            iss.str(linevector[2]);
            if (!(iss >> length) || length < 1 || stof(linevector[2]) != length) {
                cerr << "Error: Invalid edge weight '" << linevector[2] << "' on line " << line_number << "." << endl;
                return 1;
            }
            iss.clear();

            data.push_back(linevector);

            line_number++;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    vector<vector<string>> finaldata;
    vector<vector<int>> converteddata;
    vector<vector<int>> converteddataiterated;

    convert(data, converteddata);
    sortVectorofVectors(converteddata);
    bool wonder = kruskals(converteddata, converteddataiterated);
    if (wonder) {
        convertBack(converteddataiterated, data, finaldata);
        cout << "Total wire length (meters): " << addTotal(finaldata) << endl;
        sortByStreet(finaldata);
        for (size_t i = 0; i < finaldata.size(); i++) {
            cout << finaldata[i][3] << " [" << finaldata[i][2] << "]" << endl;
        }
    } else
        cout << "No solution." << endl;

    return 0;
}
