#include <iostream>
#include <algorithm>
#include <boost/timer/timer.hpp>
#include <vector>

using namespace std;
using namespace boost::timer;


int main() {
	auto_cpu_timer timer;
	const int vector_size = 14;
	int tempInt = 1;
	vector <int> permutation(vector_size);
	auto print = [](const int& n) { std::cout << n << " "; };

	for (vector<int>::iterator i = permutation.begin(); i != permutation.end(); i++)
	{
		*i = tempInt;
		tempInt++;
	}

	timer.start();

	while (next_permutation(permutation.begin(), permutation.end()))
	{
		/*for_each(permutation.begin(), permutation.end(), print);
		std::cout << "\n";*/
	}
};