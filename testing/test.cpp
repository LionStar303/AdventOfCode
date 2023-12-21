#include <iostream>
#include <cmath>
#include <string>

using namespace std;

struct node{
    int value;
    node *left;
    node *right;
};

void printList(node *n, char direction) {
    while(n != nullptr) {
        cout << n->value << ' ';
        if(direction == 'L') { n = n->left;
        } else if(direction == 'R') { n = n->right;
        } else { n = nullptr; }
    }
}

void insertAfter(node *n, char direction, int value) {

    if(n == nullptr) {
        cout << "previous node cannot be NULL" << endl;
        return;
    }

    node* newNode = new node;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if(direction == 'L') {
        n->left = newNode;
    } else if(direction == 'R') {
        n->right = newNode;
    } else { cout << "invalid direction" << endl; }
    return;
}

long long gcd(long long int a, long long int b) { 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
}

int main() {
    cout << 0 % 2;

    return 0;
}