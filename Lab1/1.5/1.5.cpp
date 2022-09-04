#include<iostream>
#include<algorithm>
#include<vector>
#include<boost/timer/timer.hpp>

using namespace std;
using namespace boost::timer;

int main() {
    auto_cpu_timer timer;
    int k = 5;
    int n;
    cout << "please input number: ";
    cin >> n;
    auto print = [](const int& el) { std::cout << el << " "; };

    int* elements = new int[k + 1];

    elements[0] = -1;
    for (int i = 1; i <= k; i++) {
        elements[i] = i;
    }

    timer.start();

    int m = 1;

    while (m != 0)
    {
        /*for_each(elements + 1, elements + k + 1, print);
        std::cout << "\n";*/

        int* permutation = elements;
        while (next_permutation(permutation + 1, permutation + k +1))
        {
            /*for_each(permutation + 1, permutation + k + 1, print);
            std::cout << "\n";*/
        }

        m = k;

        while (elements[m] == n - k + m)
        {
            m = m - 1;
        }
        elements[m] = elements[m] + 1;

        for (int i = m + 1; i <= k; i++) {
            elements[i] = elements[i - 1] + 1;
        }
    }

};