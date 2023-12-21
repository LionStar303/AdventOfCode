// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct mirror{
    int size = 0;
    int left = 0;
};

vector<vector<string>> getInputGrids(string fileName) {
    
    vector<vector<string>> returnFile;
    ifstream file(fileName);
    if (file.fail()) {
        cout << "file could not be opened";
    }

    string line;
    vector<string> grid;
    while (getline (file, line)) {
        if(line.empty()) {
            returnFile.push_back(grid);
            grid.clear();
            continue;
        }
        grid.push_back(line);
    }
    returnFile.push_back(grid);
    file.close();

    return returnFile;
}

vector<string> invert(vector<string> original) {
    vector<string> invertedGrid;
    for(int i = 0; i < original[0].length(); i++) {
        string line = "";
        for(int j = 0; j < original.size(); j++) {
            line += original[j][i];
        }
        invertedGrid.push_back(line);
    }
    return invertedGrid;
}

bool compareLine(string a, string b, int &smudgeCounter) {
    for(int i = 0; i < a.length(); i++) {
        if(a[i] != b[i]) {
            smudgeCounter++;
        }
    }
    if(smudgeCounter > 1) {
        return false;
    }
    return true;
}

mirror findReflection2(vector<string> grid) {
    mirror m;
    for(int i = 1; i < grid.size(); i++) {
        int smudgeCounter = 0;
        if(compareLine(grid[i], grid[i-1], smudgeCounter)) {
            int currentSize = 1;
            while(i+currentSize < grid.size() && i-currentSize > 0 && compareLine(grid[i+currentSize], grid[i-currentSize-1], smudgeCounter)) {
                currentSize++;
            }
            if((i-currentSize == 0 || i+currentSize == grid.size()) && smudgeCounter != 0) {
                m.size = currentSize;
                m.left = i;
            } // -> checks if the reflection is valid
        }
        smudgeCounter = 0;
    }
    cout << m.size << ' ';
    return m;
}

mirror findReflection(vector<string> grid) {
    mirror m;
    for(int i = 1; i < grid.size(); i++) {
        if(grid[i] == grid[i-1]) {
            int currentSize = 1;
            while(i+currentSize < grid.size() && i-currentSize > 0 && grid[i+currentSize] == grid[i-currentSize-1]) {
                currentSize++;
            }
            if(i-currentSize == 0 || i+currentSize == grid.size()) {
                m.size = currentSize;
                m.left = i;
            } // -> checks if the reflection is valid
        }
    }
    cout << m.size << ' ';
    return m;
}

void part1() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputGrids(inputFileName);

    int rows = 0;
    int columns = 0;
    int result1 = 0;
    for(vector<string> grid : input) {
        vector invertedGrid = invert(grid);
        mirror m = findReflection(grid);
        mirror n = findReflection(invertedGrid);
        if(n.size > m.size) {
            cout << "-> " << n.left << endl;
            columns += n.left;
        } else {
            cout << "-> " << m.left << endl;
            rows += m.left;
        }
        cout << "-> " << m.left << endl;

    }
    result1 = rows*100 + columns;
    cout << endl << endl << "Result of Part 1: " << result1;
}

void part2() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputGrids(inputFileName);

    int rows = 0;
    int columns = 0;
    int result2 = 0;
    for(vector<string> grid : input) {
        vector invertedGrid = invert(grid);
        mirror m = findReflection2(grid);
        mirror n = findReflection2(invertedGrid);
        if(n.size > m.size) {
            cout << "-> " << n.left << endl;
            columns += n.left;
        } else {
            cout << "-> " << m.left << endl;
            rows += m.left;
        }
        cout << "-> " << m.left << endl;

    }
    result2 = rows*100 + columns;
    cout << endl << endl << "Result of Part 2: " << result2;
}

int main() {

    part1();

    //part2();

   return 0;
}