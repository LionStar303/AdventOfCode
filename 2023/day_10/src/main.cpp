// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct coord{
    int line = 0;
    int row = 0;
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

coord findStart(vector<string> input) {
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        for(int j = 0; j < line.length(); j++) {
            if(line[j] == 'S') {
                coord start;
                start.line = i;
                start.row = j;
                return start;
            }
        }
    }
}

coord findNext(vector<string> input, coord current, coord previous) {

    char left = ' '; char top = ' '; char right = ' '; char bottom = ' ';
    int x = current.row; int y = current.line;
    coord next;

    if(x > 0 && x > previous.row)                   { left = input[y][x-1]; }
    if(y > 0 && y > previous.line)                  { top = input[y-1][x]; } 
    if(x < input[0].length() && x < previous.row)   { right = input[y][x+1]; }
    if(y < input.size() && y < previous.line)       { bottom = input[y+1][x]; }

    switch(input[y][x]) {
        case '-': {
            next.line = y;
            if(previous.row == x-1) {
                next.row = x+1;
            } else {
                next.row = x-1;
            }
            break;
        }
        case '|': {
            next.row = x;
            if(previous.line == y-1) {
                next.line = y+1;
            } else {
                next.line = y-1;
            }
            break;
        }
        case 'L': {
            if(previous.row == x) {
                next.row = x+1;
                next.line = y;
            } else {
                next.row = x;
                next.line = y-1;
            }
            break;
        }
        case 'F': {
            if(previous.row == x) {
                next.row = x+1;
                next.line = y;
            } else {
                next.row = x;
                next.line = y+1;
            }
            break;
        }
        case 'J': {
            if(previous.row == x) {
                next.row = x-1;
                next.line = y;
            } else {
                next.row = x;
                next.line = y-1;
            }
            break;
        }
        case '7': {
            if(previous.row == x) {
                next.row = x-1;
                next.line = y;
            } else {
                next.row = x;
                next.line = y+1;
            }
            break;
        }
    }
    return next;
}

bool coordEquals(coord a, coord b) {
    return ( a.line == b.line && a.row == b.row );
}

void part1() {
    
    //string inputFileName = "../demo-input.txt";
    //string inputFileName = "../demo-input2.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    coord start = findStart(input);
    cout << "Start: (" << start.row << "," << start.line << ")" << endl;

    coord previous = start;
    coord current;
    char left = ' '; char top = ' '; char right = ' '; char bottom = ' ';
    if(start.row > 0)                   { left = input[start.line][start.row-1]; }
    if(start.line > 0)                  { top = input[start.line-1][start.row]; } 
    if(start.row < input[0].length())   { right = input[start.line][start.row+1]; }
    if(start.line < input.size())       { bottom = input[start.line+1][start.row]; }
    cout << ' ' << top << ' ' << endl
         << left << 'S' << right << endl
         << ' ' << bottom << ' ' << endl;

    if(left == '-' || left == 'F' || left == 'L') {
        current.line = start.line;
        current.row = start.row-1;
    } else if(top == '|' || top == 'F' || top == '7') {
        current.line = start.line-1;
        current.row = start.row;
    } else if(right == '-' || right == '7' || right == 'J') {
        current.line = start.line;
        current.row = start.row+1;
    } else if(bottom == '|' || bottom == 'L' || bottom == 'J') {
        current.line = start.line+1;
        current.row = start.row;
    }
    cout << endl << '(' << current.row << ',' << current.line << ") -> \'" << input[current.line][current.row]<< '\'' << endl;

    int steps = 1;
    while(!coordEquals(current, start)) {
        coord next = findNext(input, current, previous);
        previous = current;
        current = next;
        steps++;
    }

    cout << steps << endl;
    int result1 = steps/2;
    cout << endl << "Result of Part 1: " << result1 << endl;
}

int main() {

    //part1();
    
    //string inputFileName = "../demo-input.txt";
    //string inputFileName = "../demo-input2.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector original = input;

    coord start = findStart(input);
    cout << "Start: (" << start.row << "," << start.line << ")" << endl;

    coord previous = start;
    input[previous.line][previous.row] = 'X';
    coord current;
    char left = ' '; char top = ' '; char right = ' '; char bottom = ' ';
    if(start.row > 0)                   { left = input[start.line][start.row-1]; }
    if(start.line > 0)                  { top = input[start.line-1][start.row]; } 
    if(start.row < input[0].length())   { right = input[start.line][start.row+1]; }
    if(start.line < input.size())       { bottom = input[start.line+1][start.row]; }

    string startSign = "";

    if(left == '-' || left == 'F' || left == 'L') {
        current.line = start.line;
        current.row = start.row-1;
    } else if(top == '|' || top == 'F' || top == '7') {
        current.line = start.line-1;
        current.row = start.row;
    } else if(right == '-' || right == '7' || right == 'J') {
        current.line = start.line;
        current.row = start.row+1;
    } else if(bottom == '|' || bottom == 'L' || bottom == 'J') {
        current.line = start.line+1;
        current.row = start.row;
    }

    if(left == '-' || left == 'F' || left == 'L') { startSign += 'L'; }
    if(top == '|' || top == 'F' || top == '7') { startSign += 'T'; }
    if(right == '-' || right == '7' || right == 'J') { startSign += 'R'; }
    if(bottom == '|' || bottom == 'L' || bottom == 'J') { startSign += 'B'; }

    if(startSign == "LT") { original[start.line][start.row] = 'J';
    } else if(startSign == "LR") { original[start.line][start.row] = '-';
    } else if(startSign == "LB") { original[start.line][start.row] = '7';
    } else if(startSign == "TR") { original[start.line][start.row] = 'L';
    } else if(startSign == "TB") { original[start.line][start.row] = '|';
    } else if(startSign == "RB") { original[start.line][start.row] = 'F'; }

    int steps = 1;
    while(!coordEquals(current, start)) {
        coord next = findNext(input, current, previous);
        previous = current;
        current = next;
        input[previous.line][previous.row] = 'X';
        steps++;
    }

    int result2 = 0;
    for(int i = 0; i < input.size(); i++) {
        string line = input[i];
        bool inLoop = false;
        bool above = false;      //true if inner area is above a horizontal pipe, false if it is not
        for(int j = 0; j < line.length(); j++) {
            char c = line[j];
            if(c == 'X') {
                if(original[i][j] == '|') {
                    inLoop = !inLoop;
                } else if(original[i][j] == 'L') {
                    above = !inLoop;
                } else if(original[i][j] == 'F') {
                    above = inLoop;
                } else if(original[i][j] == 'J') {
                    inLoop = !above;
                } else if(original[i][j] == '7') {
                    inLoop = above;
                }
                continue;
            }
            if(inLoop) {
                input[i][j] = 'O';
                result2++;
            }
        }
        cout << input[i] << endl;
    }

    cout << "Result of Part 2: " << result2 << endl;

   return 0;
}