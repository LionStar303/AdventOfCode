// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct lens{
    string label;
    int focalLength;
};

string getInputAsString(string fileName) {
    
    string returnFile;
    ifstream file(fileName);
    if (file.fail()) {
        cout << "file could not be opened";
    }

    string line;

    while (getline (file, line)) {
        returnFile += line;
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

void part1(vector<string> sequence) {

    int result1 = 0;

    for(string s : sequence) {
        int hash = 0;
        for(char c : s) {  hash = ((hash + int(c)) * 17) % 256; }
        result1 += hash;
        cout << s << " -> " << hash << endl;
    }

    cout << endl << "Result of Part 1: " << result1 << endl;
}

void part2(vector<string> sequence) {

    map<int, vector<lens>> boxes;

    for(string s : sequence) {
        int hash = 0;
        int i = 0;
        while(s[i] != '=' && s[i] != '-') {
            hash = ((hash + int(s[i])) * 17) % 256;
            i++;
        }
        lens l;
        l.label = s.substr(0, i);
        if(s[i] == '=') {
            l.focalLength = stoi(s.substr(i+1, 1));
            bool replaced = false;
            for(lens& s : boxes[hash]) {
                if(l.label  == s.label) {
                    s = l;
                    replaced = true;
                    cout << hash << " replaced " << l.label << " with " << l.focalLength << endl;
                    break;
                }
            }
            if(!replaced) {
                boxes[hash].push_back(l);
                cout << hash << " added " << l.label << " with " << l.focalLength << endl;
            }
        } else {
            for(int i = 0; i < boxes[hash].size(); i++) {
                if(boxes[hash][i].label == l.label) {
                    boxes[hash].erase(boxes[hash].begin() + i);
                    cout << hash << " removed " << l.label << endl;
                }
            }
        }
    }

    int result2 = 0;

    cout << endl << endl;
    for(int i = 0; i < 256; i++) {
        cout << "Box " << i << ": ";
        for(int j = 0; j < boxes[i].size(); j++) {
            lens l = boxes[i][j];
            result2 += (i+1) * (j+1) * l.focalLength;
            cout << '[' << l.label << ' ' << l.focalLength << "] ";
        }
        cout << endl;
    }

    cout << endl << "Result of Part 2: " << result2 << endl;
}

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    string input = getInputAsString(inputFileName);

    vector sequence = split(input, ',');

    //part1(sequence);

    part2(sequence);

    return 0;
}