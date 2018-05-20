//https://www.hackerrank.com/challenges/superman-celebrates-diwali

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


template <class T>
class Matrix {
private:
	T* data;
	int _N;
	int _H;
public:
	Matrix(int N, int H) {
		_N = N;
		_H = H;
		data = new T[N*H];
		for (int i = 0; i < N*H; i++) {
			data[i] = 0;
		}
	}

	~Matrix() {
		delete[] data;
	}

	inline T& get(int i, int j) {
		return data[i * _H + j];
	}

	inline void set(int i, int j, T val) {
		data[i * _H + j] = val;
	}

};

void update_floors(int curHeight, int H, int N, int I, Matrix<int>& people, vector<int>& jumped) {
	int maxPeopleInRow = 0;
	for (int i = 0; i < N; i++) {
		// People from current row
		int carried = people.get(i, curHeight);
		
		// Find max in current row
		if (carried > maxPeopleInRow) {
			maxPeopleInRow = carried;
		}
	}

	// Jumping to other buildings
	if (curHeight + I <= H) {
		jumped[curHeight + I] = maxPeopleInRow;
	}
	
	// Update
	for (int i = 0; i < N; i++) {
		// People from current row
		int moved = people.get(i, curHeight);

		// People from jump
		if (jumped[curHeight + 1] > moved) {
			moved = jumped[curHeight + 1];
		}

		int oldVal = people.get(i, curHeight + 1);
		int newVal = moved + oldVal;
		if (newVal > oldVal)
			people.set(i, curHeight + 1, newVal);
	}
}


int main() {
    std::ios::sync_with_stdio(false);
    int N, H, I;
	cin >> N >> H >> I;

	Matrix<int> people(N, H + 1);
	vector<int> maxOfRow(H + 1);
	
	// Load data
	int peopleNum;
	int height;
	for (int i = 0; i < N; i++) {
		cin >> peopleNum;

		for (int j = 0; j < peopleNum; j++) {
			cin >> height;
			int val = people.get(i, height) + 1;
			people.set(i, height, val);
		}
	}

	// Compute
	for (int curHeight = 0; curHeight < H; curHeight++) {
		update_floors(curHeight, H, N, I, people, maxOfRow);
	}

	// Find max
	int res = 0;
	for (int i = 0; i < N; i++) {
		int candidate = people.get(i, H);
		if (candidate > res) {
			res = people.get(i, H);
		}
	}
	cout << res;
    
    return 0;
}

