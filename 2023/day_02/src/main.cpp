// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define MAX_R 12
#define MAX_G 13
#define MAX_B 14

using namespace std;

struct game{
    int id;         //id of the game

    int red;        //highest number of red cubes
    int green;      //highest number of green cubes
    int blue;       //highest number of blue cubes

    int power;

    bool possible;  //true/false wether the game was possible max cubes
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

vector<string> split(string s, char a) {
    vector<string> sr;
    int start = 0;
    int len = 0;
    for(int i = 0; i < s.length(); i++) {
        if(s[i] == a) {
            sr.push_back(s.substr(start, len));
            len = 0;
            start = i + 1;
        } else {
            len++;
        }
    }
    sr.push_back(s.substr(start, len)); //pushes the last substring

    return sr;
}

string purge(string s, char p) {
    string sr;
    for(char c : s) {
        if(c != p) { sr += c; }
    }
    return sr;
}

game getGame(string line) {
    vector lineV = split(purge(purge(purge(line, ':'), ','), ';'), ' ');
    game g;

    g.id = stoi(lineV[1]);
    g.red = 0;
    g.green = 0;
    g.blue = 0;

    int num;

    for(int i = 2; i < lineV.size(); i++) {
        if (lineV[i] == "red") {
            if (num > g.red) { g.red = num; }
        } else if (lineV[i] == "green") {
            if (num > g.green) { g.green = num; }
        } else if (lineV[i] == "blue") {
            if (num > g.blue) { g.blue = num; }
        } else { num = stoi(lineV[i]); }
    }

    g.power = g.red * g.green * g.blue;
    g.possible = (
        g.red <= MAX_R
        && g.green <= MAX_G
        && g.blue <= MAX_B);

    return g;
}

int main() {

    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";

    vector input = getInputByLine(inputFileName);
    vector<game> games;

    for (string line : input) {
        game g = getGame(line);

        games.push_back(g);

        cout    << g.id << "  "
                << g.red << ' '
                << g.green << ' '
                << g.blue << "  "
                << g.power << "  "
                << g.possible << ' '
                << endl;
    }

    int resultPart1 = 0;
    int resultPart2 = 0;

    for (game g : games) {
        if(g.possible == true) { resultPart1 += g.id; }
        resultPart2 += g.power;
    }

    cout << endl << "Result of Part 1: " << resultPart1;
    cout << endl << "Result of Part 2: " << resultPart2;

    return 0;
}