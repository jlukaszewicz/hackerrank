//https://www.hackerrank.com/challenges/minimum-average-waiting-time

#include <bits/stdc++.h>

using namespace std;

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

	void push (T elem) {
		storage.push_back(elem);
		heapifyUp(storage.size() - 1);
	}

	T top() {
		return storage[1];
	}

};


class cmp_pair {
public:
	bool operator() (std::pair<long long, long long> p1, std::pair<long long, long long> p2) {
		return p1.first > p2.first;
	}
};


/*
 * Complete the minimumAverage function below.
 */
long long minimumAverage(vector<vector<int>> customers) {
       
	// start_time, cook_time
	my_priority_queue<pair<long long, long long>, my_vector<pair<long long, long long>>, cmp_pair> data;

	// cook_time, start_time
	my_priority_queue<pair<long long, long long>, my_vector<pair<long long, long long>>, cmp_pair> candidates;

	long long n = customers.size();

	long long cur_time = 0;

	int order_time, cook_time;
	for (int i = 0; i < n; i++) {
        order_time = customers[i][0];
		cook_time = customers[i][1];
		data.push(make_pair(order_time, cook_time));
	}

	long long counter = 0;

	while (!data.empty() || !candidates.empty()) {
		// Select candidates
		while (!data.empty() && data.top().first <= cur_time) {
			candidates.push(make_pair(data.top().second, data.top().first));
			data.pop();
		}

		if (candidates.size() > 0) {
			cur_time += candidates.top().first;
			counter += (cur_time - candidates.top().second);
			candidates.pop();
		} else {
			if (data.size() > 0) {
				cur_time = data.top().first;
			}
		}
	}
    long long res = counter / n;
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> customers(n);
    for (int customers_row_itr = 0; customers_row_itr < n; customers_row_itr++) {
        customers[customers_row_itr].resize(2);

        for (int customers_column_itr = 0; customers_column_itr < 2; customers_column_itr++) {
            cin >> customers[customers_row_itr][customers_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long long result = minimumAverage(customers);

    fout << result << "\n";

    fout.close();

    return 0;
}

