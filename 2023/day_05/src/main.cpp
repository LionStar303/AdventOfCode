// main file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/time.h>

using namespace std;

struct range{
    long long destination = 0;      //start of the destination range
    long long source = 0;           //start of the source range
    long long length = 0;           //length of the range (including the start)
    long long sourceEnd;            //not included in the range
    long long displacement;
};

struct seedBag{
    long long start = 0;            //number of the first seed
    long long length = 1;           //length of the seedBag (including the start)
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

long long change(vector<range> ranges, long long seed) {
    for(range r : ranges) {
        if(r.source <= seed && r.sourceEnd > seed) {
            return (seed + r.displacement);
        }
    }
    return seed;
}

void part1() {
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<long long> seeds;
    vector<range> ranges;

    int i = 0;
    string line = input[i];
    vector lineV = split(line, ' ');

    //Seeds for Part 1
    for(int j = 1; j < lineV.size(); j++) { //pulls the seeds out of the first line
        seeds.push_back(stoll(lineV[j]));
    }
    
    i += 3;

    while(i < input.size()) {
        line = input[i];
        if(line.empty()) {
            for(int j = 0; j < seeds.size(); j++) {
                long long seed = seeds[j];
                cout << seed << " -> ";
                seed = change(ranges, seed);
                seeds[j] = seed;
                cout << seed << endl;
            }
            cout << endl;
            ranges.clear();
            i += 2;
            continue;
        }
        lineV = split(line, ' ');
        range r;
        r.destination = stoll(lineV[0]);
        r.source = stoll(lineV[1]);
        r.length = stoll(lineV[2]);
        r.sourceEnd = r.source + r.length;
        r.displacement = r.destination - r.source;
        ranges.push_back(r);
        i++;
    }

    for(int j = 0; j < seeds.size(); j++) { //last transformation
        long long seed = seeds[j];
        cout << seed << " -> ";
        seed = change(ranges, seed);
        seeds[j] = seed;
        cout << seed << endl;
    }

    long long result1 = seeds[0];
    for(long long seed : seeds){
        if(result1 > seed) {
            result1 = seed;
        }
    }
    cout << endl << endl << "Result Part 1: " << result1 << endl;
}

void part2() {
    //string inputFileName = "../demo-input.txt";
    string inputFileName = "../input.txt";
    vector input = getInputByLine(inputFileName);
    vector<seedBag> seeds;
    vector<range> ranges;

    int i = 0;  //starting in the first line of input
    string line = input[i];
    vector lineV = split(line, ' ');

    for(int j = 1; j < lineV.size(); j += 2) {
        seedBag s;
        s.start = stoll(lineV[j]);
        s.length = stoll(lineV[j+1]);
        seeds.push_back(s);
        cout << "Startvalue: " << s.start << "  Length: " << s.length << endl;
    }
    
    i += 3;

    while(i < input.size()) {
        line = input[i];
        if(line.empty()) {
            vector<seedBag> newSeeds;
            for(int j = 0; j < seeds.size(); j++) {
                seedBag s = seeds[j];
                for(range r : ranges) {
                    if(r.source <= s.start && r.sourceEnd > s.start) {
                        if (s.start + s.length <= r.sourceEnd) {
                            cout << s.start << ',' << s.length << " -> ";
                            s.start += r.displacement;
                            cout << s.start << ',' << s.length << endl;
                            break;
                        }
                        cout << s.start << ',' << s.length << " -> ";
                        seedBag newBag;
                        newBag.start = r.sourceEnd;
                        newBag.length = s.length;
                        s.length = r.sourceEnd - s.start;
                        s.start += r.displacement;
                        newBag.length -= s.length;
                        seeds.push_back(newBag);
                        cout << s.start << ',' << s.length << " & " << newBag.start << ',' << newBag.length << endl;
                    }
                    
                }
                newSeeds.push_back(s);
            }
            cout << '.' << endl;
            seeds = newSeeds;
            ranges.clear();
            i += 2;
            continue;
        }
        lineV = split(line, ' ');
        range r;
        r.destination = stoll(lineV[0]);
        r.source = stoll(lineV[1]);
        r.length = stoll(lineV[2]);
        r.sourceEnd = r.source + r.length;
        r.displacement = r.destination - r.source;
        ranges.push_back(r);
        i++;
    }

    
    
    vector<seedBag> newSeeds;
    for(int j = 0; j < seeds.size(); j++) {
        seedBag s = seeds[j];
        for(range r : ranges) {
            if(r.source <= s.start && r.sourceEnd > s.start) {
                if (s.start + s.length <= r.sourceEnd) {
                    cout << s.start << ',' << s.length << " -> ";
                    s.start += r.displacement;
                    cout << s.start << ',' << s.length << endl;
                    break;
                }
                cout << s.start << ',' << s.length << " -> ";
                seedBag newBag;
                newBag.start = r.sourceEnd;
                newBag.length = s.length;
                s.length = r.sourceEnd - s.start;
                s.start += r.displacement;
                newBag.length -= s.length;
                seeds.push_back(newBag);
                cout << s.start << ',' << s.length << " & " << newBag.start << ',' << newBag.length << endl;
            }
            
        }
        newSeeds.push_back(s);
    }
    cout << '.' << endl;
    seeds = newSeeds;

    long long result2 = seeds[0].start;
    for(seedBag s : seeds){
        if(result2 > s.start) {
            result2 = s.start;
        }
    }
    cout << endl << endl << "Result Part 1: " << result2 << endl;
}


int main() {

    struct timeval begin, end;
    gettimeofday(&begin, 0);
    
    part2();
    
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    cout << "Elapsed time: " << elapsed;

    return 0;
}