//main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> getInputByLine(string fileName) {
    
    vector<string> returnFile;                  //vector (dynamic array) which will be returned
    ifstream file(fileName);                    //file as an ifstream object
    if (file.fail()) {                          //checks if file can be opened
        cout << "file could not be opened";
    }

    string line;                                //current line in the file

    while (getline (file, line)) {              //loops as long as lines exist
        returnFile.push_back(line);
    }
    file.close();                               //closes the file

    return returnFile;
}

char getFirst(string in) {                      //returns first integer (as char) of the line
    for (char c : in) {
        if (isdigit(c)) {return c;}
    }
    return '0';
}
char getLast(string in) {                       //returns last integer (as char) of the line
    for (int i = in.length(); i >= 0; i--) {
        if (i >= 0 && isdigit(in[i])) {return in[i];}
    }
    return '0';
}

char transform(string s, int i) {
    if(s.substr(i, 3) == "one") {
        return '1';
    } else if(s.substr(i, 3) == "two" && i < s.length()) {
        return '2';
    } else if(s.substr(i, 5) == "three" && i < s.length()) {
        return '3';
    } else if(s.substr(i, 4) == "four" && i < s.length()) {
        return '4';
    } else if(s.substr(i, 4) == "five" && i < s.length()) {
        return '5';
    } else if(s.substr(i, 3) == "six" && i < s.length()) {
        return '6';
    } else if(s.substr(i, 5) == "seven" && i < s.length()) {
        return '7';
    } else if(s.substr(i, 5) == "eight" && i < s.length()) {
        return '8';
    } else if(s.substr(i, 4) == "nine" && i < s.length()) {
        return '9';
    }
    return s[i];
}

int main() {

    string inputFileName = "../demo-input.txt";
    //string inputFileName = "../input.txt";

    vector input = getInputByLine(inputFileName);
    int result1 = 0;

    for (string line : input) {
        cout << line << endl;
        result1 += stoi(string(1, getFirst(line)) + getLast(line));
    }

    cout << endl << "Result of Part 1: " << result1 << endl;

    //Part 2
    cout << endl << "Part 2:" << endl;
    int result2 = 0;

    for(string line : input) {
        for(int i = 0; i < line.length(); i++) {
            line[i] = transform(line, i);
        }
        cout << line << endl;
        result2 += stoi(string(1, getFirst(line)) + getLast(line));
    }
    
    cout << endl << "Result of Part 2: " << result2 << endl;

    return 0;
}