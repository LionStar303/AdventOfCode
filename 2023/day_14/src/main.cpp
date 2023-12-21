// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

struct match{
    bool matching = false;
    int i;
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

int getRocks(string line) {
    int out = 0;
    for(char c : line) {
        if(c == 'O') { out++; }
    }
    return out;
}

int load(vector<string> input) {
    int totalLoad = 0;
    int size = input.size();
    for(int i = 0; i < size; i++) {
        totalLoad += (size-i) * getRocks(input[i]);
    }
    return totalLoad;
}

void north(vector<string>* input) {     //shifts all the rocks to the northern side
    int changes = 1;
    while(changes) {
        changes = 0;
        for(int i = 1; i < input->size(); i++) {
            string* prev = &(*input)[i-1];
            string* line = &(*input)[i];
            for(int j = 0; j < line->length(); j++) {
                if( (*line)[j] == 'O' && (*prev)[j] == '.') {
                    (*prev)[j] = 'O';
                    (*line)[j] = '.';
                    changes++;
                }
            }
        }
    }
}

void east(vector<string>* input) {      //shifts all the rocks to the eastern side
    int changes = 1;
    while(changes) {
        changes = 0;
        for(int i = 0; i < input->size(); i++) {
            string* line = &(*input)[i];
            for(int j = line->length() -1; j > 0; j--) {
                if( (*line)[j-1] == 'O' && (*line)[j] == '.') {
                    (*line)[j] = 'O';
                    (*line)[j-1] = '.';
                    changes++;
                }
            }
        }
    }
}

void south(vector<string>* input) {     //shifts all the rocks to the southern side
    int changes = 1;
    while(changes) {
        changes = 0;
        for(int i = input->size()-1; i > 0; i--) {
            string* prev = &(*input)[i-1];
            string* line = &(*input)[i];
            for(int j = 0; j < line->length(); j++) {
                if( (*prev)[j] == 'O' && (*line)[j] == '.') {
                    (*prev)[j] = '.';
                    (*line)[j] = 'O';
                    changes++;
                }
            }
        }
    }
}

void west(vector<string>* input) {      //shifts all the rocks to the western side
    int changes = 1;
    while(changes) {
        changes = 0;
        for(int i = 0; i < input->size(); i++) {
            string* line = &(*input)[i];
            for(int j = 1; j < line->length(); j++) {
                if( (*line)[j-1] == '.' && (*line)[j] == 'O') {
                    (*line)[j] = '.';
                    (*line)[j-1] = 'O';
                    changes++;
                }
            }
        }
    }
}

bool equals(vector<string> a, vector<string> b) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

match findMatch(vector<vector<string>> history, vector<string> input) {
    match m;
    for(int i = 0; i < history.size(); i++) {
        if(equals(history[i], input)) {
            m.matching = true;
            m.i = i;
            return m;
        }
    }
    return m;
}

int main() {

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<vector<string>> history;

    for(int i = 0; i < 490; i++) {
        north(&input);
        west(&input);
        south(&input);
        east(&input);
        history.push_back(input);
        cout << i << endl;
    }

    int start;
    int cycle;
    for(int i = 488; i >= 0; i--) {
        if(equals(history[i], history[489]) && equals(history[i-1], history[488])) {
            start = i;
            break;
        }
    }
    cycle = 489 - start;

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    //cout << "Result of Part 1: " << result1 << endl;

    int lastGrid = 1000000000 % (cycle);

    cout << endl;
    for(string line : history[lastGrid - 1]) {
        cout << line << endl;
    }
    cout << endl;
    for(string line : history[lastGrid - 1 + cycle]) {
        cout << line << endl;
    }

    cout << "Elapsed time: " << elapsed << endl;

    cout << "Found match at " << start << " & " << start + cycle << " repeating every " << cycle << " iterations" << endl;

    int result2 = load(history[lastGrid + 8*cycle - 1]);
    cout << "Result of Part 2: " << result2 << endl;
    /*for(int i = 7*cycle-2; i <= 8*cycle; i++) {
        result2 = load(history[lastGrid + 8*cycle + i]);
        cout << i <<  "  Result of Part 2: " << result2 << endl;
    }*/

    return 0;
}