//https://www.hackerrank.com/challenges/longest-increasing-subsequent

#include <vector>
#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int indexBisect(int* data, int idx1, int idx2, int val) {
	if (idx2 - idx1 <= 1) {
		return idx1;
	} else {
		int tmp_idx = (idx1 + idx2) / 2;
		if (data[tmp_idx] > val) {
			return(indexBisect(data, idx1, tmp_idx, val));
		}
		else {
			return(indexBisect(data, tmp_idx, idx2, val));
		}
	}
}

int longestIncreasingSubsequence(vector<int> arr) {
	int seqLen = 0;
	int* data = new int[arr.size()];
	for (int i = 0; i < arr.size(); i++) {
		data[i] = -1;
	}

	for (int i = 0; i < arr.size(); i++) {
		int val = arr[i];
		
		// Find by bisecting
		int idx = indexBisect(data, 0, seqLen, val);

		// Insert
		if (data[idx] == -1) {
			data[idx] = val;
			seqLen++;
		} else if (data[idx] > val) {
			data[idx] = val;
		} else if (data[idx] < val) {
			// Check next one
			if (data[idx + 1] == -1) {
				data[idx + 1] = val;
				seqLen++;
			} else if (data[idx + 1] > val) {
				data[idx + 1] = val;
			}
		}	
	}

	delete[] data;
	return seqLen;
}


int main()
{
	freopen("../input.txt", "r", stdin);

	int n; cin >> n;

	vector<int> arr;
	for (int i = 0; i < n; i++) {
		int tmp;
		cin >> tmp;
		arr.push_back(tmp);
	}

	cout << longestIncreasingSubsequence(arr);

    return 0;
}

