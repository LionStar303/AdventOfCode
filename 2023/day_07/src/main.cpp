// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <sys/time.h>

using namespace std;

struct game{
    string deck;
    int bid;
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

int getRank(string deck) {
    string d[5] = {"", "", "", "", ""};
    for(char c : deck) {
        int i = 0;
        while(!d[i].empty() && d[i][0] != c) {
            i++;
        }
        d[i] += c;
    }
    //cout << d[0] << ' ' << d[1] << ' ' << d[2] << ' ' << d[3] << ' ' << d[4] << ' ';
    
    int l = 0;
    int i = 0;
    while(!d[i].empty()) {
        l += pow(d[i].length(), 2);
        i++;
    }
    return l;
}

int getValue(char c) {
    switch (c) {
    case 'A': return 14;
    case 'K': return 13;
    case 'Q': return 12;
    case 'J': return 11;
    case 'T': return 10;
    case '9': return 9;
    case '8': return 8;
    case '7': return 7;
    case '6': return 6;
    case '5': return 5;
    case '4': return 4;
    case '3': return 3;
    case '2': return 2;
    default:
        break;
    }
    return 0;
}

bool compare(string d1, string d2) {    //returns true if d1 is a higher rank than d2
    int r1 = getRank(d1);
    int r2 = getRank(d2);
    if(r1 < r2) {
        return false;
    } else if(r1 > r2) {
        return true;
    }
    int i = 0;
    while(d1[i] == d2[i]) { i++; }
    if(getValue(d1[i]) > getValue(d2[i])) { return true; }
    return false;
}

int partition(vector<game> &v, int start, int end) {
    string pivot = v[start].deck;

    int count = 0;
    for(int i = start+1; i <= end; i++) {
        if(compare(pivot, v[i].deck)) {
            count++;
        }
    }
    int pivotIndex = start + count;
    swap(v[pivotIndex], v[start]);

    int i = start;
    int j = end;
    while(i < pivotIndex && j > pivotIndex) {
        while(compare(pivot, v[i].deck)) {
            cout << pivot << " > " << v[i].deck << endl;
            i++;
        }
        while(compare(v[j].deck, pivot)) {
            cout << pivot << " < " << v[j].deck << endl;
            j--;
        }
        if(i < pivotIndex && j > pivotIndex) {
            swap(v[i++], v[j--]);
        }
    }
    cout << '.' << endl;
    return pivotIndex;
}

void quicksortGame(vector<game> &v, int min, int max) {

    if(min >= max) { return; }
    int p = partition(v, min, max);

    quicksortGame(v, min, p-1);
    quicksortGame(v, p+1, max);
}

int getRank2(string deck) {
    string d[5] = {"", "", "", "", ""};
    int j = 0;
    for(char c : deck) {
        if(c == 'J') {
            j++;
            continue;
        }
        int i = 0;
        while(!d[i].empty() && d[i][0] != c) {
            i++;
        }
        d[i] += c;
    }
    //cout << d[0] << ' ' << d[1] << ' ' << d[2] << ' ' << d[3] << ' ' << d[4] << ' ';
    
    if(j == 5) { return 25; }

    int max = 0;
    int i = 0;
    while(!d[i].empty()) {
        if(d[i].length() > d[max].length()) { max = i; }
        i++;
    }

    int l = 0;
    i = 0;
    while(!d[i].empty()) {
        if(i == max) {
            l += pow(d[i].length()+j, 2);
        } else {
            l += pow(d[i].length(), 2);
        }
        i++;
    }
    return l;
}

int getValue2(char c) {
    switch (c) {
    case 'A': return 14;
    case 'K': return 13;
    case 'Q': return 12;
    case 'J': return 1;
    case 'T': return 10;
    case '9': return 9;
    case '8': return 8;
    case '7': return 7;
    case '6': return 6;
    case '5': return 5;
    case '4': return 4;
    case '3': return 3;
    case '2': return 2;
    default:
        break;
    }
    return 0;
}

bool compare2(string d1, string d2) {    //returns true if d1 is a higher rank than d2
    int r1 = getRank2(d1);
    int r2 = getRank2(d2);
    if(r1 < r2) {
        return false;
    } else if(r1 > r2) {
        return true;
    }
    int i = 0;
    while(d1[i] == d2[i]) { i++; }
    if(getValue2(d1[i]) > getValue2(d2[i])) { return true; }
    return false;
}

int partition2(vector<game> &v, int start, int end) {
    string pivot = v[start].deck;

    int count = 0;
    for(int i = start+1; i <= end; i++) {
        if(compare2(pivot, v[i].deck)) {
            count++;
        }
    }
    int pivotIndex = start + count;
    swap(v[pivotIndex], v[start]);

    int i = start;
    int j = end;
    while(i < pivotIndex && j > pivotIndex) {
        while(compare2(pivot, v[i].deck)) {
            cout << pivot << " > " << v[i].deck << endl;
            i++;
        }
        while(compare2(v[j].deck, pivot)) {
            cout << pivot << " < " << v[j].deck << endl;
            j--;
        }
        if(i < pivotIndex && j > pivotIndex) {
            swap(v[i++], v[j--]);
        }
    }
    cout << '.' << endl;
    return pivotIndex;
}

void quicksortGame2(vector<game> &v, int min, int max) {

    if(min >= max) { return; }
    int p = partition2(v, min, max);

    quicksortGame2(v, min, p-1);
    quicksortGame2(v, p+1, max);
}

void part1() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<game> games;

    for(string line : input) {
        //cout << getRank(split(line, ' ')[0]) << endl;
    	vector lineV = split(line, ' ');
        game g;
        g.deck = lineV[0];
        g.bid = stoi(lineV[1]);
        games.push_back(g);
    }

    quicksortGame(games, 0, games.size()-1);

    int result1 = 0;
    for(int i = 1; i <= games.size(); i++) {
        result1 += i * games[i-1].bid;
        cout << games[i-1].deck << ' ' << games[i-1].bid << endl;
    }
    
    cout << endl << "Result of part 1: " << result1 << endl;
}

void part2() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<game> games;

    for(string line : input) {
        //cout << getRank(split(line, ' ')[0]) << endl;
    	vector lineV = split(line, ' ');
        game g;
        g.deck = lineV[0];
        g.bid = stoi(lineV[1]);
        games.push_back(g);
    }

    quicksortGame2(games, 0, games.size()-1);

    int result2 = 0;
    for(int i = 1; i <= games.size(); i++) {
        result2 += i * games[i-1].bid;
        cout << games[i-1].deck << ' ' << games[i-1].bid << endl;
    }
    
    cout << endl << "Result of part 2: " << result2 << endl;
}

int main() {

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    //part1();

    part2();

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    cout << "Elapsed time: " << elapsed;

    return 0;
}