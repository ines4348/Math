#include<iostream>
#include<algorithm>
#include<vector>
#include<boost/timer/timer.hpp>

using namespace std;
using namespace boost::timer;

int main() {
    auto_cpu_timer timer;
    int n;
    cout << "please input number: ";
    cin >> n;
    auto print = [](const int& el) { std::cout << el << " "; };

    int* elements = new int[n + 1];

    for (int i = 0; i <= n; i++) {
        elements[i] = 0;
    }

    timer.start();

    while (elements[n] != 1)
    {
        /*for_each(elements, elements + n, print);
        std::cout << "\n";*/

        int i = 0;

        while (elements[i] == 1)
        {
            elements[i] = 0;
            i++;
        }
        elements[i] = 1;
    }

};