/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Semal Shah, Danielle Faustino
 * Date        : 10/19/20
 * Description : Solve water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
            a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string bfs(int a, int b, int c, State goalState) {
    queue<State> q;
    State initial(0, 0, c, "Initial state. ");
    vector<State> pour;
    bool **array = new bool*[a+1];

    for (int i = 0; i < a+1; ++i) {
        array[i] = new bool[b+1];
        // Fill the array with zeros.
        fill(array[i], array[i] + b+1, false);
    }

    vector<State*> addyvec;
    q.push(initial);
    while(!q.empty()) {
        State * addy;
        addy = new State (q.front());
        State current = q.front();
        q.pop();
        if ((current.to_string().compare(goalState.to_string())) == 0) {
            for (int i = 0; i < a+1; ++i) {
                delete [] array[i];
            }
            delete [] array;
            string output;
            while((initial.to_string().compare(current.to_string())) != 0) {
                output = current.directions + "\n" + output;
                current = *current.parent;
            }
            for (size_t i = 0; i < addyvec.size(); i++) {
                delete addyvec[i];
            }
            delete addy;
            return initial.directions + initial.to_string() + "\n" + output;
        }

        int availA = a - current.a;
        int availB = b - current.b;
        int availC = c - current.c;

        // pouring from C to A
        if(availA != 0 && current.c != 0){
            State copy = current;
            if(copy.c == availA) {
                copy.a += availA;
                copy.c -= availA;
            } else if (copy.c > availA) {
                copy.c -= availA;
                copy.a += availA;
            } else if (copy.c < availA) {
                copy.a += copy.c;
                copy.c = 0;
            }
            int poured = copy.a - current.a;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from C to A. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from C to A. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        // pouring from B to A
        if(availA != 0 && current.b != 0){
            State copy = current;
            if(copy.b == availA) {
                copy.a += availA;
                copy.b -= availA;
            }
            else if (copy.b > availA) {
                copy.b -= availA;
                copy.a += availA;
            }
            else if (copy.b < availA) {
                copy.a += copy.b;
                copy.b = 0;
            }
            int poured = copy.a - current.a;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from B to A. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from B to A. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        // pouring from C to B
        if(availB != 0 && current.c != 0){
            State copy = current;
            if(copy.c == availB) {
                copy.b += availB;
                copy.c -= availB;
            }
            else if (copy.c > availB) {
                copy.c -= availB;
                copy.b += availB;
            }
            else if (copy.c < availB) {
                copy.b += copy.c;
                copy.c = 0;
            }
            int poured = copy.b - current.b;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from C to B. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from C to B. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        // pouring from A to B
        if(availB != 0 && current.a != 0){
            State copy = current;
            if(copy.a == availB) {
                copy.b += availB;
                copy.a -= availB;
            }
            else if (copy.a > availB) {
                copy.a -= availB;
                copy.b += availB;
            }
            else if (copy.a < availB) {
                copy.b += copy.a;
                copy.a = 0;
            }
            int poured = copy.b - current.b;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from A to B. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from A to B. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        // pouring from B to C
        if(availC != 0 && current.b != 0){
            State copy = current;
            if(copy.b == availC) {
                copy.c += availC;
                copy.b -= availC;
            }
            else if (copy.b > availC) {
                copy.b -= availC;
                copy.c += availC;
            }
            else if (copy.b < availC) {
                copy.c += copy.b;
                copy.b = 0;
            }
            int poured = copy.c - current.c;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from B to C. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from B to C. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        // pouring from A to C
        if(availC != 0 && current.a != 0){
            State copy = current;
            if(copy.a == availC) {
                copy.c += availC;
                copy.a -= availC;
            }
            else if (copy.a > availC) {
                copy.a -= availC;
                copy.c += availC;
            }
            else if (copy.a < availC) {
                copy.c += copy.a;
                copy.a = 0;
            }
            int poured = copy.c - current.c;
            if (poured == 1)
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallon from A to C. " + copy.to_string();
            else
                copy.directions = (string)"Pour " + to_string(poured) + (string)" gallons from A to C. " + copy.to_string();
            copy.parent = addy;
            pour.push_back(copy);
        }

        for(size_t i = 0; i < pour.size(); i++) {
            int a = pour[i].a;
            int b = pour[i].b;

            if(!(array[a][b])) {
                array[a][b] = true;
                q.push(pour[i]);
            }
        }
        pour.clear();
        addyvec.push_back(addy);
    }
    for (int i = 0; i < a+1; ++i) {
        delete [] array[i];
    }

    delete [] array;
    for (size_t i = 0; i < addyvec.size(); i++) {
        delete addyvec[i];
    }
    return "No solution.";
}

int main(int argc, char * const argv[]) {
    float m;
    float n;
    istringstream iss;
    istringstream iss2;
    int capA, capB, capC, goalA, goalB, goalC;

    if (argc != 7) {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    for(int i = 1; i < 7; i++) {
        iss.str(argv[i]);
        if(!(iss >> m) || m < 0 || (int)m != m) {
            if(i < 4) {
                cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)(i+64) << "." << endl;
            }
            else {
                cerr << "Error: Invalid goal '" << argv[i] << "' for jug " <<  (char)(i+61) << "." <<endl;
            }
            return 1;
        }
        if (i < 4 && m==0) {
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << (char)(i+64) << "." << endl;
            return 1;
        }
        iss.clear();
    }

    for (int i = 1; i < 4; i++) {
        iss.str(argv[i]);
        iss2.str(argv[i + 3]);
        iss >> m;
        iss2 >> n;
        if (n > m) {
            cerr << "Error: Goal cannot exceed capacity of jug " << (char)(i+64) << "." << endl;
            return 1;
        }
        iss.clear();
        iss2.clear();
    }

    int all = 0;
    for (int i = 4; i < 7; i++) {
        iss.str(argv[i]);
        iss >> n;
        all += n;
        iss.clear();
    }
    iss2.str(argv[3]);
    iss2 >> m;
    if (m != all) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }
    iss2.clear();

    iss.str(argv[1]);
    iss >> capA;
    iss.clear();
    iss.str(argv[2]);
    iss >> capB;
    iss.clear();
    iss.str(argv[3]);
    iss >> capC;
    iss.clear();
    iss.str(argv[4]);
    iss >> goalA;
    iss.clear();
    iss.str(argv[5]);
    iss >> goalB;
    iss.clear();
    iss.str(argv[6]);
    iss >> goalC;
    iss.clear();

    State goalState(goalA, goalB, goalC, "Goal");
    cout << bfs(capA, capB, capC, goalState) << endl;
    return 0;
}
