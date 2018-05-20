//https://www.hackerrank.com/challenges/find-the-running-median/submissions/code/72839613

#include <bits/stdc++.h>
#include <functional>
#include <vector>

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
	}

public:
	my_vector() {
		_size = 0;
		_capacity = 10;
		buffer = new T[_capacity];
	}

	~my_vector() {
		delete[] buffer;
	}

	void push_back(T t) {
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

	int size() {
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
		}
		storage.pop_back();
		heapifyDown(1);
	}

	void push (T elem) {
		storage.push_back(elem);
		heapifyUp(storage.size() - 1);
	}

	T top() {
		return storage[1];
	}

};

/*
 * Complete the runningMedian function below.
 */
vector<double> runningMedian(vector<int> a) {
    
    my_priority_queue<int, vector<int>, std::less<int>> q1;
	my_priority_queue<int, vector<int>, std::greater<int>> q2;
    vector<double> res;
    
	int tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp = a[i];

        
        
		if (q1.size() == 0) {
			q1.push(tmp);
			res.push_back(tmp * 2);
		}
		else {
            if (tmp > q1.top()) {
				q2.push(tmp);
			}
			else {
				q1.push(tmp);
			}

			// Rebalance
			if (q1.size() > q2.size() + 1) {
				q2.push(q1.top());
				q1.pop();
			} 	
			if (q2.size() > q1.size()) {
				q1.push(q2.top());
				q2.pop();
			}

			if (q1.size() > q2.size()) {
				res.push_back(q1.top() * 2);
			} else {
				res.push_back(q1.top() + q2.top());
			}
		}
	}
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    
    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr] / 2.0f;

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

