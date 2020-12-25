/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Semal Shah
 * Date        : October 1, 2020
 * Description : Lists the number of ways to climb n stairs and outputs in a fancy way.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector<vector<int>> ways;
    vector<vector<int>> way;
    vector<int> nothing;
    int size;

    if (num_stairs <= 0)
        ways.push_back(nothing);
    else {
        for (int i = 1; i <= 3; i++) {
            if (num_stairs >= i) {
                way = get_ways(num_stairs - i);
                size = way.size();
                for (int s = 0; s < size; s++) {
                    way[s].insert(way[s].begin(), i);
                }
                ways.insert(ways.end(), way.begin(), way.end());
            }
        }
    }

    return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    int num_ways = ways.size();
    int num_ways_for_width = ways.size();
    int num_stairs = ways[0].size();
    int width = 0;
    int size;

    while(num_ways_for_width > 0) {
        num_ways_for_width = num_ways_for_width / 10;
        width++;
    }

    if (num_stairs == 1)
        cout << num_ways << " way to climb " << num_stairs << " stair."<< endl;
    else
        cout << num_ways << " ways to climb " << num_stairs << " stairs."<< endl;

    for (int i = 0; i < num_ways; i++) {
        cout << setw(width) << i+1 << ". [";
        size = ways[i].size();
        for (int s = 0; s < size; s++) {
            if (s != size - 1)
                cout << ways[i][s] << ", ";
            else
                cout << ways[i][s] << "]" << endl;

        }
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    float m;
    istringstream iss;

    iss.str(argv[1]);

    if (!(iss >> m) || m <= 0 || (int)m != m) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    
    display_ways(get_ways(m));

    return 0;
}
