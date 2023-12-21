//main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct number{
    int value = 0;          //value of the number

    int x = 0;              //index in line (first digit)
    int y = 0;              //index of line
    int len = 0;            //length of the number

    bool valid = false;     //whether the number is valid or not
};

struct gear{
    int x = 0;                      //index in line
    int y = 0;                      //index of line

    int ratio = 1;

    int count = 0;
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

bool checkForSymbols(string line, int start, int len) {
    
    len += 2; //also checks for diagonal symbols
    start--;
    int end = start + len;
    for( int k = start; k < end; k++ ) {
        if(k < 0 || k >= line.length()) { continue; }
        if( !(line[k] == '.' || isdigit(line[k])) ) {
            return true;
        }
    }
    return false;
}

int getNum(string line, int index) {

    int len = 0;
    while(isdigit(line[index]) && index >= 0) {
        index--;
    }
    index++;
    while(isdigit(line[index])) {
        len++;
        index++;
    }
    cout << stoi(line.substr((index -len), len)) << ' ';
    return stoi(line.substr((index -len), len));
}

int main() {

    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";

    vector input = getInputByLine(inputFileName);
    vector<number> numbers;

    for(int i = 0; i < input.size(); i++) {

        string line = input[i];
        int c = 0;
        int len = 0;
        number num;
        num.y = i;

        while( c < line.length() ) {

            if( isdigit(line[c]) ) {
                len += 1;
                num.x = c;
            }
            c++;

            while( len > 0 ) {
                if( isdigit(line[c]) ) {
                    len += 1;
                } else {
                    num.len = len;
                    len = 0;
                    num.value = stoi(line.substr(num.x, num.len));

                    if( !(num.y == 0) && !num.valid) {
                        num.valid = checkForSymbols(input[i-1], num.x, num.len);
                    }
                    if( !(num.y == input.size() - 1) && !num.valid ) {
                        num.valid = checkForSymbols(input[i+1], num.x, num.len);
                    }
                    if( !num.valid && num.x > 0 ) { num.valid = !(line[num.x -1] == '.'); }
                    if( !num.valid && line.length() > num.x +num.len) { num.valid = !(line[num.x +num.len] == '.'); }

                    numbers.push_back(num); //adds the number to the list
                    num.value = 0;
                    num.x = 0;
                    num.valid = false;
                }
                c++;
            }
        }
    }

    int line = 0;
    int result1 = 0;

    for(number n : numbers) {
        if ( n.y > line ) {
            line = n.y;
            cout << endl;
        }
        if(n.valid) { cout << n.value << " "; }

        if(n.valid) { result1 += n.value; }
    }

    cout << endl << endl << "Result Part 1: " << result1 << endl;

    vector<gear> gears;

    for(int i = 0; i < input.size(); i++) {

        string line = input[i];

        for(int j = 0; j < line.length(); j++) {

            if(line[j] != '*') { continue; }

            gear g;
            g.x = j;
            g.y = i;

            if(isdigit(line[j-1])) {                    //checks left to the gear
                g.ratio *= getNum(line, j -1);
                g.count++;
            }
            if(isdigit(line[j+1])) {                    //checks right to the gear
                g.ratio *= getNum(line, j +1);
                g.count++;
            }
            if(i > 0) {
                if( isdigit(input[i-1][j]) ) {          //checks above the gear
                    g.ratio *= getNum(input[i -1], j);
                    g.count++;
                } else {
                    if(isdigit(input[i-1][j-1])) {
                        g.ratio *= getNum(input[i-1], j-1);
                        g.count++;
                    }
                    if(isdigit(input[i-1][j+1])) {
                        g.ratio *= getNum(input[i-1], j+1);
                        g.count++;
                    }
                }
            }
            if(i < input.size() -1) {
                if( isdigit(input[i+1][j]) ) {          //checks below the gear
                    g.ratio *= getNum(input[i +1], j);
                    g.count++;
                } else {
                    if(isdigit(input[i+1][j-1])) {
                        g.ratio *= getNum(input[i+1], j-1);
                        g.count++;
                    }
                    if(isdigit(input[i+1][j+1])) {
                        g.ratio *= getNum(input[i+1], j+1);
                        g.count++;
                    }
                }
            }
            if(g.count < 2) {g.ratio = 0;}              //sets gear ratio to 0 when there are less than 2 gears next to it
            gears.push_back(g);
        }
    }

    int result2 = 0;

    for(gear g : gears) {
        result2 += g.ratio;
        cout << g.count << "*(" << g.x << ',' << g.y << ") ratio: " << g.ratio << endl;
    }

    cout << endl << endl << "Result Part 2: " << result2 << endl;

    return 0;
}