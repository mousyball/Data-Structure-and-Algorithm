#include <iostream>

using std::cout;
using std::endl;

int fib(int n)
{
    if (n == 1 || n == 2)
        return 1;
    else
        return fib(n - 1) + fib(n - 2);
}

int fib_02(int n, int acc = 1, int prev = 0)
{
    if (n == 0)
        return prev;
    else
        return fib_02(n - 1, acc + prev, acc);
}

int fib_03(int n, int acc = 1, int prev = 0)
{
    while (true) {
        if (n == 0)
            return prev;
        else
            return fib_03(n - 1, acc + prev, acc);
    }
}

int fib_04(int n, int acc = 1, int prev = 0)
{
    while (true) {
        if (n == 0)
            return prev;
        else {
            //return fib_04(n - 1, acc + prev, acc);
            int temp = acc;
            acc = acc + prev;
            prev = temp;
            n = n - 1;
        }
    }
}

int fib_05(int n, int acc = 1, int prev = 0)
{
    while (n > 0) {
        int temp = acc;
        acc += prev;
        prev = temp;
        --n;
    }
    return prev;
}

int main()
{
    int n = 40;
    cout << "1. Fibonacci of " << n << ": " << fib(n) << endl;
    cout << "2. Fibonacci of " << n << ": " << fib_02(n) << endl;
    cout << "3. Fibonacci of " << n << ": " << fib_03(n) << endl;
    cout << "4. Fibonacci of " << n << ": " << fib_04(n) << endl;
    cout << "5. Fibonacci of " << n << ": " << fib_05(n) << endl;

    std::cin.get();
    return 0;
}