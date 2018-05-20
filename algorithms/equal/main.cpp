// https://www.hackerrank.com/challenges/equal

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void solve() {
    int colleagues;
    cin >> colleagues;
    
    int* arr = new int[colleagues];
    int min = 10001;
    for (int i = 0; i < colleagues; i++) {
        cin >> arr[i];
        if (min > arr[i]) {
            min = arr[i];
        }
    }
    
    long long variants[] = {0, 0, 0, 0, 0, 0};
    
    for (int i = 0; i < colleagues; i++) {
        int minDiff = arr[i] - min;
        for (int j = 0; j < 6; j++) {
            int diff = minDiff + j;
            int steps = diff / 5 + (diff % 5) / 2 + (diff % 5) % 2;
            variants[j] += steps;
        }
    }
    
    // Find min num of steps
    int minRes = variants[0];
    for (int j = 0; j < 6; j++) {
        if (minRes > variants[j]) {
            minRes = variants[j];
        }
    }
    cout << minRes << endl;
}


int main() {   
    int testCases;
    cin >> testCases;
    
    for (int i = 0; i < testCases; i++) {
        solve();
    }
    
    return 0;
}
