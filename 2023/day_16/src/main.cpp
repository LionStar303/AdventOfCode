// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sys/time.h>

using namespace std;

struct coord{
    int line;
    int column;
    int direction = 0; //0 -> right, 1 -> down, 2 -> left, 3 -> up
};

struct visited{
    bool firstTime = false;
    bool right = false;
    bool down = false;
    bool left = false;
    bool up = false;
};

map<int, visited> history;

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

coord nextCoord(coord c) {      //returns the next coordinate based in the direction
    switch(c.direction) {
        case 0:
            c.column++;
            break;
        case 1:
            c.line++;
            break;
        case 2:
            c.column--;
            break;
        case 3:
            c.line--;
            break;
        default:
            break;
    }
    return c;
}

void nextStep(vector<string>* grid, coord c, int* counter) {
    if(c.line < 0 || c.column < 0 || c.line >= grid->size() || c.column >= (*grid)[0].length()) {
        cout << "beam out of range at (" << c.column << ',' << c.line << ')' << endl;
        return;
    }
    int cHash = c.line*1000 + c.column;
    if(!history[cHash].firstTime) { (*counter)++; }
    history[cHash].firstTime = true;

    if(history[cHash].right && c.direction == 0) {
        cout << "already visited (" << c.column << ',' << c.line << ')' << endl;
        return;
    } else if(history[cHash].down && c.direction == 1) {
        cout << "already visited (" << c.column << ',' << c.line << ')' << endl;
        return;
    } else if(history[cHash].left && c.direction == 2) {
        cout << "already visited (" << c.column << ',' << c.line << ')' << endl;
        return;
    } else if(history[cHash].up && c.direction == 3) {
        cout << "already visited (" << c.column << ',' << c.line << ')' << endl;
        return;
    }

    switch(c.direction) {
        case 0:
            history[cHash].right = true;
            break;
        case 1:
            history[cHash].down = true;
            break;
        case 2:
            history[cHash].left = true;
            break;
        case 3:
            history[cHash].up = true;
            break;
        default: break;
    }
    char element = (*grid)[c.line][c.column];
    switch (element) {
    case '.':
        cout << "moving forward at (" << c.column << ',' << c.line << ')' << endl;
        nextStep(grid, nextCoord(c), counter);
        break;
    case '\\':
        if(c.direction == 0) {
            c.direction = 1;
            cout << "90 degrees down at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 1) {
            c.direction = 0;
            cout << "90 degrees right at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 2) {
            c.direction = 3;
            cout << "90 degrees up at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 3) {
            c.direction = 2;
            cout << "90 degrees left at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        }
        break;
    case '/':
        if(c.direction == 0) {
            c.direction = 3;
            cout << "90 degrees up at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 3) {
            c.direction = 0;
            cout << "90 degrees right at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 2) {
            c.direction = 1;
            cout << "90 down right at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else if(c.direction == 1) {
            c.direction = 2;
            cout << "90 degrees left at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        }
        break;
    case '-':
        if(c.direction % 2 == 0) {
            cout << "moving forward at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
        } else {
            c.direction = 0;
            cout << "split beam horizontal at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
            c.direction = 2;
            nextStep(grid, nextCoord(c), counter);
        }
        break;
    case '|':
        if(c.direction % 2 != 0) {
            nextStep(grid, nextCoord(c), counter);
        } else {
            c.direction = 1;
            cout << "split beam vertical at (" << c.column << ',' << c.line << ')' << endl;
            nextStep(grid, nextCoord(c), counter);
            c.direction = 3;
            nextStep(grid, nextCoord(c), counter);
        }
        break;
    default:
        break;
    }
}

void part1() {

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    string inputFileName = "../demo-input.txt";
    //string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    int result1 = 0;

    coord start;
    start.line = 0;
    start.column = 0;

    nextStep(&input, start, &result1);

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    cout << endl << "Result of Part 1: " << result1 << endl;
    cout << "Elapsed time: " << elapsed << endl;
}

int main() {

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    //part1();

    vector<int> energized;
    for(int i = 0; i < input.size(); i++) {
        int numberOfTiles = 0;
        coord start;
        start.line = i;
        start.column = 0;
        nextStep(&input, start, &numberOfTiles);
        energized.push_back(numberOfTiles);
        history.clear();

        numberOfTiles = 0;
        start.column = input[i].length()-1;
        start.direction = 2;
        nextStep(&input, start, &numberOfTiles);
        energized.push_back(numberOfTiles);
        history.clear();
    }
    for(int i = 0; i < input[0].size(); i++) {
        int numberOfTiles = 0;
        coord start;
        start.line = 0;
        start.column = i;
        start.direction = 1;
        nextStep(&input, start, &numberOfTiles);
        energized.push_back(numberOfTiles);
        history.clear();

        numberOfTiles = 0;
        start.line = input.size()-1;
        start.direction = 3;
        nextStep(&input, start, &numberOfTiles);
        energized.push_back(numberOfTiles);
        history.clear();
    }

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    int result2 = 0;
    for(int num : energized) {
        if(num > result2) {
            result2 = num;
        }
    }

    cout << endl << "Result of Part 2: " << result2 << endl;
    cout << "Elapsed time: " << elapsed << endl;

    return 0;
}