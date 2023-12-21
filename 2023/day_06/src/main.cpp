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

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    vector<int> time;
    vector<int> distance;

    for(string s : split(input[0], ' ')) {
        if(s == "Time:") { continue; }
        time.push_back(stoi(s));
    }
    for(string s : split(input[1], ' ')) {
        if(s == "Distance:") { continue; }
        distance.push_back(stoi(s));
    }

    int result1 = 1;
    for(int i = 0; i < time.size(); i++) {
        int k = time[i] / 2;
        int highscore = distance[i];
        int r = 0;
        while(k * (time[i] - k) > highscore) {
            r += 2;
            k--;
        }
        if( time[i] % 2 == 0 ) { r--; }
        result1 *= r;
    }

    cout << endl << "Result of Part 1: " << result1;

    //Part 2
    long long t = 53897698;
    long long k = t / 2;
    long long highscore = 313109012141201;
    long long result2 = 0;
    while(k * (t - k) > highscore) {
        result2 += 2;
        k--;
    }
    if( t % 2 == 0 ) { result2--; }

    cout << endl << "Result of Part 2: " << result2;

   return 0;
}