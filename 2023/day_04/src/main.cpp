// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct card{
    int id = 0;
    vector<string> win;
    int matching = 0;
    int worth = 0;
    int amount = 1;
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

string purge(string s, char p) {
    string sr;
    for(char c : s) {
        if(c != p) { sr += c; }
    }
    return sr;
}

int main() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<card> cards;

    for(string line : input) {
        card c;
        vector<string> lineV = split(purge(line, ':'), ' ');
        /*for(string e : lineV) {
            cout << e << ' ';
        }*/
        cout << endl;
        c.id = stoi(lineV[1]);
        int k = 2;
        while(lineV[k] != "|") {
            c.win.push_back(lineV[k]);
            k++;
        }
        k++;
        while(k < lineV.size()) {
            for(string s : c.win) {
                if(s == lineV[k]) {
                    if(c.worth == 0) { c.worth++;
                    } else { c.worth *= 2; }
                    c.matching++;
                }
            }
            k++;
        }
        cards.push_back(c);
    }
    
    //Part 1
    int result1 = 0;
    for(card c : cards) {
        cout << c.id << "->" << c.worth << endl;
        result1 += c.worth;
    }
    cout << endl << endl << "Result of Part 1: " << result1 << endl;

    //Part 2
    cout << endl << "Part 2:";
    int result2 = 0;

    for(card c : cards) {
        for(int i = c.id; i < c.id + c.matching; i++) {
            if(i < cards.size()) { cards[i].amount += c.amount; }
        }
        result2 += c.amount;
        cout << c.id << "->" << c.amount << endl;
    }

    cout << endl << endl << "Result of Part 2: " << result2;

    return 0;
}