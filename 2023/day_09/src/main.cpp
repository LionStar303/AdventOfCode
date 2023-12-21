// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

bool isZero(vector<int> sequence) {
    for(int i : sequence) {
        if(i != 0) {
            return false;
        }
    }
    return true;
}

int nextValue(vector<int> sequence) {

    if(isZero(sequence)) { return 0; }

    vector<int> differences;
    for(int i = 1; i < sequence.size(); i++) {
        differences.push_back(sequence[i] - sequence[i-1]);
    }

    int next = sequence[sequence.size()-1] + nextValue(differences);

    return next;
}

int previousValue(vector<int> sequence) {

    if(isZero(sequence)) { return 0; }

    vector<int> differences;
    for(int i = 1; i < sequence.size(); i++) {
        differences.push_back(sequence[i] - sequence[i-1]);
    }

    int next = sequence[0] - previousValue(differences);

    return next;
}

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    //Part 1
    int result1 = 0;
    for(string line : input) {
        vector lineV = split(line, ' ');
        vector<int> sequence;
        for(string s : lineV) {
            sequence.push_back(stoi(s));
        }
        result1 += nextValue(sequence);
    }
    cout << "Result of Part 1: " << result1 << endl;

    //Part 2
    int result2 = 0;
    for(string line : input) {
        vector lineV = split(line, ' ');
        vector<int> sequence;
        for(string s : lineV) {
            sequence.push_back(stoi(s));
        }
        result2 += previousValue(sequence);
    }
    cout << "Result of Part 2: " << result2 << endl;

   return 0;
}