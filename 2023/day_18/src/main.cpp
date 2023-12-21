// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

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

vector<string> split(string s, char a) {
    vector<string> sr;
    int start = 0;
    int len = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == a) {
            if(len > 0) {sr.push_back(s.substr(start, len));}
            len = 0;
            start = i +1;
        } else {
            len++;
        }
    }
    sr.push_back(s.substr(start, len)); //pushes the last substring

    return sr;
}

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    map<int, bool> trench;
    int x = 0;
    int y = 0;
    trench[1000*y + x] = true;

    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;

    for(string line : input) {
        vector lineV = split(line, ' ');
        if(lineV[0] == "R") {
            for(int i = 0; i < stoi(lineV[1]); i++) {
                x++;
                trench[1000*y + x] = true;
            }
            if(x > maxX) { maxX = x; }
        } else if(lineV[0] == "D") {
            for(int i = 0; i < stoi(lineV[1]); i++) {
                y++;
                trench[1000*y + x] = true;
            }
            if(y > maxY) { maxY = y; }
        } else if(lineV[0] == "L") {
            for(int i = 0; i < stoi(lineV[1]); i++) {
                x--;
                trench[1000*y + x] = true;
            }
            if(x < minX) { minX = x; }
        } else if(lineV[0] == "U") {
            for(int i = 0; i < stoi(lineV[1]); i++) {
                y--;
                trench[1000*y + x] = true;
            }
            if(y < minY) { minY = y; }
        }
    }

    vector<string> grid;

    int result1 = 0;
    for(int i = 0; i <= 1000*maxY; i += 1000) {
        string line = "";
        for(int j = i; j <= i+maxX; j++) {
            if(trench[j]) {
                line += '#';
                //cout << i << endl;
                continue;
            }
            line += '.';
        }
        grid.push_back(line);
    }

    for(string line : grid) {
        cout << line << endl;
    }

    //cout << "Result of part 1: " << result1;

    return 0;
}