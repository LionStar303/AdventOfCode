// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

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

vector<int> splitToInt(string s, char a) {
    vector<int> sr;
    int start = 0;
    int len = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == a) {
            if(len > 0) {sr.push_back(stoi(s.substr(start, len)));}
            len = 0;
            start = i +1;
        } else {
            len++;
        }
    }
    sr.push_back(stoi(s.substr(start, len))); //pushes the last substring

    return sr;
}

bool isValid(string row, vector<int> records) {
    int counter = 0;
    for(int i = 0; i < row.length(); i++) {
        if(row[i] == '#') {
            int broken = 0;
            while(row[i] == '#') {
                broken++;
                i++;
            }
            if(broken != records[counter]) {
                return false;
            }
            counter++;
        }
    }
    if(counter != records.size()) {
        return false;
    }
    return true;
}

int main() {
    
    string inputFileName = "../demo-input.txt";
    //string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    int result1 = 0;
    for(int l = 0; l < input.size(); l++) {
        string row = split(input[l], ' ')[0];
        vector records = splitToInt(split(input[l], ' ')[1], ',');
        vector<int> broken;
        for(int i = 0; i < row.length(); i++) {
            if(row[i] == '?') {
                broken.push_back(i);
            }
        }
        int max = broken.size();
        for(int i = 0; i < pow(2, max); i++) {
            string variant = row;
            int num = i;
            for(int j = max-1; j >= 0; j--) {
                int p = pow(2, j);
                if(num >= p) {
                    variant[broken[j]] = '#';
                    num -= p;
                } else {
                    variant[broken[j]] = '.';
                }
            }
            cout << l << " " << max << "  " << variant;
            if(isValid(variant, records)) {
                result1++;
                cout << " valid";
            }
            cout << endl;
        }
    }

    cout << endl << "Result of Part 1: " << result1;
   return 0;
}