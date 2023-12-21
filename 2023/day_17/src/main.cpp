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

int main() {
    
    string inputFileName = "../demo-input.txt";
    //string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    /*
    continue with code here
    */

    return 0;
}