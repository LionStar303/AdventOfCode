// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct coord{
    int line;
    int row;
};
struct coord2{
    int line;
    int row;
    int expansions = 0;
};

vector<string> getInputByLine(string fileName) {
    
    vector<string> returnFile;
    ifstream file(fileName);
    if (file.fail()) {
        cout << "file could not be opened";
    }

    string line;

    while (getline (file, line)) {
        returnFile.push_back(line);
    }
    file.close();

    return returnFile;
}

bool lineEmpty(string line) {
    for(char c : line) {
        if(c != '.') {
            return false;
        }
    }
    return true;
}

bool rowEmpty(vector<string> input, int row) {
    for(string line : input) {
        if(line[row] != '.') {
            return false;
        }
    }
    return true;
}

int shortestPath(coord pointA, coord pointB) {
    int distance = abs(pointA.line - pointB.line) + abs(pointA.row-pointB.row);
    return distance;
}

int longerPath(coord pointA, coord pointB, vector<int> emptyLines, vector<int> emptyRows) {
    int distance = abs(pointA.line - pointB.line) + abs(pointA.row-pointB.row);
    int expansions = 0;
    for(int i = 0; i < emptyLines.size(); i++) {
        if((emptyLines[i] < pointA.line && emptyLines[i] > pointB.line) || (emptyLines[i] > pointA.line && emptyLines[i] < pointB.line)) {
            expansions++;
        }
    }
    for(int i = 0; i < emptyRows.size(); i++) {
        if((emptyRows[i] < pointA.row && emptyRows[i] > pointB.row) || (emptyRows[i] > pointA.row && emptyRows[i] < pointB.row)) {
            expansions++;
        }
    }
    distance += expansions * 999999;
    return distance;
}

vector<coord> findGalaxies(vector<string> grid) {
    vector<coord> galaxies;
    for(int line = 0; line < grid.size(); line++) {
        for(int row = 0; row < grid[line].length(); row++) {
            if(grid[line][row] == '#') {
                coord galaxy;
                galaxy.line = line;
                galaxy.row = row;
                galaxies.push_back(galaxy);
            }
        }
    }
    return galaxies;
}

void part1() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    for(int i = 0; i < input.size(); i++) {
        if(!lineEmpty(input[i])) {
            continue;
        }
        input.insert(input.begin()+i, input[i]);
        i++;
        cout << "added line " << i << endl;
    }

    for(int i = 0; i < input[0].length(); i++) {
        if(!rowEmpty(input, i)) {
            continue;
        }
        for(string &line : input) {
            string str1 = line.substr(0, i);
            string str2 = line.substr(i, line.length()-i);
            line = str1 + '.' + str2;
        }
        i++;
        cout << "added row " << i << endl;
    }

    vector galaxies = findGalaxies(input);
    int result1 = 0;
    for(int i = 0; i < galaxies.size(); i++) {
        for(int j = i+1; j < galaxies.size(); j++) {
            result1 += shortestPath(galaxies[i], galaxies[j]);
        }
    }

    cout << endl << "Result of Part 1: " << result1 << endl;

}

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    vector<int> emptyLines;
    vector<int> emptyRows;
    
    for(int i = 0; i < input.size(); i++) {
        if(!lineEmpty(input[i])) { continue; }
        emptyLines.push_back(i);
    }
    for(int i = 0; i < input[0].length(); i++) {
        if(!rowEmpty(input, i)) { continue; }
        emptyRows.push_back(i);
    }

    for(int i : emptyLines) {
        cout << i << ' ';
    }
    cout << endl;
    for(int i : emptyRows) {
        cout << i << ' ';
    }

    vector galaxies = findGalaxies(input);
    long long result2 = 0;
    for(int i = 0; i < galaxies.size(); i++) {
        for(int j = i+1; j < galaxies.size(); j++) {
            result2 += longerPath(galaxies[i], galaxies[j], emptyLines, emptyRows);
        }
    }

    cout << endl << "Result of Part 2: " << result2 << endl;
    return 0;
}