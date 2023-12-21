// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct value{
    string left;
    string right;
};

map<string, value> network;

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

void transform(vector<string> &v, char direction) {
    if(direction == 'L') {
        for(int i = 0; i < v.size(); i++) {
            v[i] = network[v[i]].left;
        }
    } else if(direction == 'R') {
        for(int i = 0; i < v.size(); i++) {
            v[i] = network[v[i]].right;
        }
    } else {
        cout << "invalid direction" << endl;
    }
}

bool endsWith(vector<string> v, char c) {
    for(string s : v) {
        if(s[2] != c) {
            return false;
        }
    }
    return true;
}

long long gcd(long long int a, long long int b) { 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
}

long long lcm(long long a, long long b) { 
    return (a / gcd(a, b)) * b; 
} 

void part1() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    string directions = input[0];
    map<string, value> nodes;

    for(int i = 2; i < input.size(); i++) {
        string line = input[i];
        value newValue;
        newValue.left = line.substr(7, 3);
        newValue.right = line.substr(12, 3);
        nodes[line.substr(0, 3)] = newValue;
        cout << i-1 << ": " << line.substr(0, 3) << " -> " << newValue.left << ' ' << newValue.right << endl;
    }
    cout << directions << endl;

    cout << nodes["ZZZ"].left << endl;

    string element = "AAA";          //input[2].substr(0, 3); // -> gets the starting element edit: READ THE FULL TASK
    int count = 0;
    int max = directions.length();
    while(element != "ZZZ") {
        char d = directions[count % max];
        if(d == 'L') {
            element = nodes[element].left;
            count ++;
        } else if (d == 'R'){
            element = nodes[element].right;
            count ++;
        } else {
            cout << "invalid direction" << endl;
        }
    }

    cout << endl << "Result of Part 1: " << count << endl;

}

void part2() {
    
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);

    string directions = input[0];
    vector<string> nodes;

    for(int i = 2; i < input.size(); i++) {
        string line = input[i];
        value newValue;
        newValue.left = line.substr(7, 3);
        newValue.right = line.substr(12, 3);
        network[line.substr(0, 3)] = newValue;
        if(line[2] == 'A') {
            nodes.push_back(line.substr(0, 3));
        }
        cout << i-1 << ": " << line.substr(0, 3) << " -> " << newValue.left << ' ' << newValue.right << endl;
    }
    cout << directions << endl;

    int max = directions.length();
    bool stop = false;
    int loopSize[nodes.size()];
    
    for(int i = 0; i < nodes.size(); i++) {
        int count = 0;
        string element = nodes[i];
        while(element[2] != 'Z') {
            char d = directions[count % max];
            if(d == 'L') {
                element = network[element].left;
                count ++;
            } else if (d == 'R'){
                element = network[element].right;
                count ++;
            } else {
                cout << "invalid direction" << endl;
            }
        }
        loopSize[i] = count;
    }

    long long result2 = loopSize[0];
    cout << result2 << ' ';

    for(int i = 1; i < nodes.size(); i++) {
        result2 = lcm(result2, loopSize[i]);
        cout << loopSize[i] << ' ';
    }

    cout << endl << "Result of Part 2: " << result2 << endl;

}
int main() {
    
    //part1();

    part2();

   return 0;
}