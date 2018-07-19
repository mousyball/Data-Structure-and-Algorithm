#include <iostream>

using std::cout;
using std::endl;

int factorial_s01(int n)
{
    if (n == 0) return 1;
    else return n * factorial_s01(n - 1);
}

int factorial_s02(int n, int acc = 1)
{
    if (n == 0) return acc * 1;
    else return factorial_s02(n - 1, acc * n);
}

int factorial_s03(int n, int acc = 1)
{
    while (true) {
        if (n == 0) return acc * 1;
        else return factorial_s03(n - 1, acc * n);
    }
}

int factorial_s04(int n, int acc = 1)
{
    while (true) {
        if (n == 0) return acc * 1;
        else {
            //return factorial_s04(n - 1, acc * n);
            acc = acc * n;
            n = n - 1;
        }
    }
}

int factorial_s05(int n, int acc = 1)
{
    if (n < 0) {
        std::cerr << "Value of n shouldn't be negative." << std::endl;
        return -1;
    }

    while (n > 1) {
        acc *= n;
        --n;
    }
    return acc;
}

int main()
{
    int n = 5;
    cout << "1. Factorial of " << n << ": " << factorial_s01(n) << endl;
    cout << "2. Factorial of " << n << ": " << factorial_s02(n) << endl;
    cout << "3. Factorial of " << n << ": " << factorial_s03(n) << endl;
    cout << "4. Factorial of " << n << ": " << factorial_s04(n) << endl;

    n = -100;
    cout << "5. Factorial of " << n << ": " << factorial_s05(n) << endl;
    n = 6;
    cout << "5. Factorial of " << n << ": " << factorial_s05(n) << endl;

    std::cin.get();
    return 0;
}