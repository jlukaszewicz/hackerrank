// From https://www.hackerrank.com/challenges/unbounded-knapsack/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void solve() {
    int numbersNum;
    cin >> numbersNum;
    
    int k;
    cin >> k;
    
    int* nums = new int[numbersNum];   
    for (int i = 0; i < numbersNum; i++) {
        cin >> nums[i];
    }
    
    
    bool visited[2001];
    for (int j = 0; j < 2001; j++) {
        visited[j] = false;
    }
    int max = 0;
    
    for (int i = 0; i < numbersNum; i++) {
        for (int j = 0; j <= k; j++) {
            if (visited[j] || j == 0) {
                if (j + nums[i] <= k) {
                    visited[j + nums[i]] = true;
                    if ( j + nums[i] > max) {
                        max = j + nums[i];
                    }
                }
            }
        }
    }
    
    cout << max << endl;
    
    
    delete[] nums;
}

int main() {
    int tests;
    cin >> tests;
    
    for (int i = 0; i < tests; i++) {
        solve();
    }
    
    return 0;
}

