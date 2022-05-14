#include "test.h"

int sum_fib(int n, int s) {
    if (n == 1) {
        return 1;
    }
    if (n == 0) {
        return 0;
    }

    // let s represent the original n
    if (n == s) {
        int sum = 0;
        for (int i = 0; i<n; i++) {
            sum += sum_fib(i, s);
        }
        sum += sum_fib(n, s+1);
        return sum;
    }
    else {
        return (sum_fib(n-1, s) + sum_fib(n-2, s));
    }
}
