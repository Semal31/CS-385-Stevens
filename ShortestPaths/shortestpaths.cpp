/*******************************************************************************
* Name    : shortestpaths.cpp
* Author  : Semal Shah, Shreyas Keerthi
* Version : 1.0
* Date    : December 8, 2020
* Description : finds the shortest path using floyd's algorithm
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;

long INF = 42000000000000;
int num_vertices;
vector<vector<long>> distanceMatrix;
vector<vector<long>> pathMatrix;

void backPath(int i, int j) {
    //the algorithm that was taught in class for backtracking
    if (pathMatrix[i][j] != INF) {
        backPath(i, pathMatrix[i][j]);
        backPath(pathMatrix[i][j], j);
    }
    else
        cout << " -> " << char('A' + j);
}

void displayPath() {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            // if i and j are equal then they are the same letter
            if(i == j)
                cout << char('A' + i) << " -> " << char('A' + i) << ", " << "distance: 0, path: " << char('A' + i) << endl;
                // if the distance is infinity then there is no path
            else if (distanceMatrix[i][j] == INF)
                cout << char('A' + i) << " -> " << char('A' + j) << ", " << "distance: infinity, path: none" << endl;
            else {
                //check if there is an intermediate
                //if there is no intermediate
                if(pathMatrix[i][j] == INF)
                    cout << char('A' + i) << " -> " << char('A' + j) << ", " << "distance: " << distanceMatrix[i][j] << ", path: " << char('A' + i) << " -> " << char('A' + j);
                else {
                    //there is an intermediate
                    cout << char('A' + i) << " -> " << char('A' + j) << ", " << "distance: " << distanceMatrix[i][j] << ", path: " << char('A' + i);
                    backPath(i, j);
                }
                cout << endl;
            }
        }
    }
}

void floydAlgo(){
    //CLRS version of algorithm and updating pathMatrix
    size_t n = distanceMatrix.size();
    for(size_t k=0; k<n; k++){
        for(size_t i=0; i<n; i++){
            for(size_t j=0;j<n;j++){
                //checking if the new value is less than the old one
                if ((distanceMatrix[i][k] + distanceMatrix[k][j]) < distanceMatrix[i][j])
                    pathMatrix[i][j] = k;
                //takes shorter distance and updates distanceMatrix
                distanceMatrix[i][j] = min(distanceMatrix[i][j], distanceMatrix[i][k] + distanceMatrix[k][j]);
            }
        }
    }
}

int len(long val) {
    int digits = 0;
    if (val == 0)
        return 1;
    while (val > 0) {
        val = val / 10;
        digits++;
    }
    return digits;
}

void display_table(vector<vector<long>> matrix, const string &label,
                   const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
                         len(max(static_cast<long>(num_vertices), max_val));
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        getline(input_file, line);
        istringstream iss(line);
        if (!(iss >> num_vertices) || (num_vertices > 26 || num_vertices < 1)) {
            cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
            return 1;
        }
        line_number++;

        distanceMatrix = vector<vector<long>> (num_vertices, vector<long>(num_vertices, INF));
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if (i == j) {
                    distanceMatrix[i][j] = 0;
                }
            }
        }

        pathMatrix = vector<vector<long>> (num_vertices, vector<long>(num_vertices, INF));

        while (getline(input_file, line)) {
            istringstream iss(line);
            //iterates through the line and puts each edge and edgeWeight in the vector as separate objects
            vector<string> linevector((istream_iterator<string>(iss)),istream_iterator<string>());
            if (linevector.size() != 3) {
                cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
                return 1;
            }

            if (linevector[0] < "A" || linevector[0] > string(1, char('A' + num_vertices - 1))) {
                cerr << "Error: Starting vertex '" << linevector[0] << "' on line " << line_number << " is not among valid values A-" << char('A' + num_vertices - 1) << "." << endl;
                return 1;
            }

            if (linevector[1] < "A" || linevector[1] > string(1, char('A' + num_vertices - 1))) {
                cerr << "Error: Ending vertex '" << linevector[1] << "' on line " << line_number << " is not among valid values A-" << char('A' + num_vertices - 1) << "." << endl;
                return 1;
            }

            iss.clear();
            iss.str(linevector[2]);
            int edgeWeight = 0;
            if (!(iss >> edgeWeight) || edgeWeight < 1) {
                cerr << "Error: Invalid edge weight '" << linevector[2] << "' on line " << line_number << "." << endl;
                return 1;
            }
            iss.clear();

            distanceMatrix[linevector[0][0] - 'A'][linevector[1][0] - 'A'] = edgeWeight;

            line_number++;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    display_table(distanceMatrix, "Distance matrix:");
    floydAlgo();
    display_table(distanceMatrix, "Path lengths:");
    display_table(pathMatrix, "Intermediate vertices:", true);
    displayPath();
    return 0;
}
