/**
 * A C++11 thread program illustrating how to
 * create multiple cooperating threads using the C++11 Thread STL class API.
 * This program implements a summation function where
 * the summation operation for each integer is run as a separate thread.
 *
 * Most Unix/Linux/OS X users:
 * g++ thrd-cpp11.cpp -lpthread
 *
 * To run 1000 times, and count the number of different results (bash syntax):
 *	for i in {1..1000}; do ./a.out; done | sort | uniq -c
 */

#include <iostream>
#include <thread>
#include <vector>


using namespace std;

int sum = 0; /* this global variable is shared by all threads */


void runner(int value) {
	sum += value;
}


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "usage: a.out <integer value>\n";
		return -1;
	}

	int upper = atoi(argv[1]);
	
	if (upper < 0) {
		cerr << "Argument " << upper << " must be non-negative\n";
		return -1;
	}

	vector<thread> ths;
	for (int i = 1; i <= upper; i++) {
		ths.push_back(thread(&runner, i));
	}
	
	for (auto& th : ths) {
		th.join();
	}
	
	cout << "sum = " << sum << endl;
	return 0;
}
