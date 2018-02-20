// https://www.hackerrank.com/challenges/coin-change

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool calculated[51][251];
long long combinations[51][251];
int coins[51];
int N;
int M;

long long solve(int i, int make) {
    if (make < 0) {
        return 0;
    } else if (make == 0) {
        return 1;
    }
    
    if (i > N) {
        return 0;
    }
    
    if (calculated[i][make] == false) {
        combinations[i][make] = solve(i, make - coins[i]) + solve(i + 1, make);
        calculated[i][make] = true;
    }
    return combinations[i][make];
}

int main() {
    
    // The change
    cin >> M;
    
    // Number of coins
    cin >> N;
    
    // Fill coins 
    for (int i = 1 ; i <= N; i++) {
        cin >> coins[i];
    }
    
    cout << solve(1, M);
   
    return 0;
}
