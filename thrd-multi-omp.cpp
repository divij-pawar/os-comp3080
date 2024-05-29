#include <iostream>
#include <thread>
//#include <vector>
#include <omp.h>

using namespace std;

int sum = 0; /* this global variable is shared by all threads */


void runner(int value) {

	#pragma omp critical
		{
			sum += value;
			cout << "In runner: value == " << value
			<< ", number of threads == " << omp_get_num_threads()
			<< ", my thread num == " << omp_get_thread_num()
			<< endl;
	}
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

	#pragma omp parallel for
	for (int i = 1; i <=upper; i++) {
		runner(i);
	}
	
	cout << "sum = " << sum << endl;
	return 0;
}