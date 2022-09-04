#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<boost/timer/timer.hpp>

using namespace std;
using namespace boost::timer;

int main()
{
    auto_cpu_timer timer;
    int n;
    cout << "please input number: ";
    cin >> n;

    timer.start();

    int* elments = new int[n + 2];
    int* reverseElements = new int[n + 2]; 
    int* direction = new int[n + 2];
    auto print = [](const int& el) { std::cout << el << " "; };

    for (int i = 1; i <= n; i++)
    {
        elments[i] = i;
        reverseElements[i] = i;
        direction[i] = -1;
    }

    int m = 0;
    elments[0] = n + 1;
    elments[n + 1] = n + 1;
    direction[0] = 0;

    while (m != 1)
    {
        /*for_each(elments + 1, elments + n + 1, print);
        std::cout << "\n";*/

        m = n;

        while (elments[reverseElements[m] + direction[m]] > m && m > 1)
        {
            int temp = direction[m];
            direction[m] = -temp;
            m = m - 1;
        }

        std::swap(elments[reverseElements[m]], elments[reverseElements[m] + direction[m]]);
        std::swap(reverseElements[elments[reverseElements[m]]], reverseElements[m]);
    }
}