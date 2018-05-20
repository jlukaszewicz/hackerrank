//https://www.hackerrank.com/challenges/board-cutting

#include <bits/stdc++.h>
#include <vector>
#include <functional>

template <class T>
class my_vector {
private:
	int _size;
	int _capacity;
	T* buffer;

	void resize() {
		int new_capacity = _capacity * 2;
		T* tmp = new T[new_capacity];
		for (int i = 0; i < _size; i++) {
			tmp[i] = buffer[i];
		}
		delete[] buffer;
		buffer = tmp;
		_capacity = new_capacity;
	}

public:

	typedef T value_type;
	typedef int size_type;
	typedef T& reference;
	typedef const T& const_reference;

	T& begin() {
		return buffer[0];
	}

	const_reference front() const {
		return buffer[0];
	}

	const_reference back() const {
		return buffer[size() - 1];
	}

	T& end() {
		return buffer[size() - 1];
	}

	my_vector() {
		_size = 0;
		_capacity = 10;
		buffer = new T[_capacity];
	}

	~my_vector() {
		delete[] buffer;
	}

	void push_back(const value_type& t) {
		if (_capacity <= _size + 1) {
			resize();
		}

		buffer[_size] = t;
		_size++;
	}

	void pop_back() {
		if (_size > 0) {
			_size--;
		}
	}

	bool empty() {
		return _size == 0;
	}

	size_type size() const {
		return _size;
	}

	T& operator [] (int idx) {
		return buffer[idx];
	}

};

template <class T, class U, class X>
class my_priority_queue {
public:
	U storage;
	X cmp;

	my_priority_queue() {
		// Empty elem
		storage.push_back(T());
	}

	bool empty() {
		return size() <= 0;
	}

	int size() {
		return storage.size() - 1;
	}

	void heapifyDown(int index) {
		int parent = index;
		int lc = -1;
		int rc = -1;
		if (storage.size() > 2 * parent) {
			lc = 2 * parent;
		}
		if (storage.size() > 2 * parent + 1) {
			rc = 2 * parent + 1;
		}

		if (lc > 0) {
			int betterChildIdx = lc;
			if (rc > 0 && cmp(storage[lc], storage[rc])) {
				betterChildIdx = rc;
			}
			if (cmp(storage[parent], storage[betterChildIdx])) {
				// Swap with smaller child
				T tmp = storage[parent];
				storage[parent] = storage[betterChildIdx];
				storage[betterChildIdx] = tmp;
				heapifyDown(betterChildIdx);
			}
		}

	}

	void heapifyUp(int index) {
		if (index > 1) {
			int parent = index / 2;
			int child = index;

			if (cmp(storage[parent], storage[child])) {
				// Swap with smaller child
				T tmp = storage[parent];
				storage[parent] = storage[child];
				storage[child] = tmp;
				heapifyUp(parent);
			}
		}
	}

	void pop() {
		if (storage.size() > 1) {
			storage[1] = storage[storage.size() - 1];
			storage.pop_back();
			heapifyDown(1);
		}
	}

	void push(T elem) {
		storage.push_back(elem);
		heapifyUp(storage.size() - 1);
	}

	T top() {
		return storage[1];
	}

};

template <class T>
class cmp_pair {
public:
	bool operator() (T p1, T p2) {
		return p1.first < p2.first;
	}
};

using namespace std;

vector<string> split_string(string);

// Complete the boardCutting function below.
int boardCutting(vector<int> cost_y, vector<int> cost_x) {

    long long hor_pieces = 1;
	long long ver_pieces = 1;
	
	my_priority_queue<pair<int, bool>, my_vector<pair<int,bool>>, cmp_pair<pair<int, bool>>> data;

	for (int i = 0; i < cost_y.size(); i++) {
		data.push(make_pair(cost_y[i], true));
	}

	for (int i = 0; i < cost_x.size(); i++) {
		data.push(make_pair(cost_x[i], false));
	}

	long long cost = 0;

	while (!data.empty()) {
		long long cut_cost = data.top().first;
		bool cut_dir = data.top().second;

		if (cut_dir) {
			cost += (cut_cost * ver_pieces ) % 1000000007;
			hor_pieces += 1;
		} else {
			cost += (cut_cost * hor_pieces) % 1000000007;
			ver_pieces += 1;
		}
		data.pop();
	}
	return cost % 1000000007;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string mn_temp;
        getline(cin, mn_temp);

        vector<string> mn = split_string(mn_temp);

        int m = stoi(mn[0]);

        int n = stoi(mn[1]);

        string cost_y_temp_temp;
        getline(cin, cost_y_temp_temp);

        vector<string> cost_y_temp = split_string(cost_y_temp_temp);

        vector<int> cost_y(m-1);

        for (int i = 0; i < m-1; i++) {
            int cost_y_item = stoi(cost_y_temp[i]);

            cost_y[i] = cost_y_item;
        }

        string cost_x_temp_temp;
        getline(cin, cost_x_temp_temp);

        vector<string> cost_x_temp = split_string(cost_x_temp_temp);

        vector<int> cost_x(n-1);

        for (int i = 0; i < n-1; i++) {
            int cost_x_item = stoi(cost_x_temp[i]);

            cost_x[i] = cost_x_item;
        }

        int result = boardCutting(cost_y, cost_x);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

