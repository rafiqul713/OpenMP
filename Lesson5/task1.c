/*
Parallelize the following fibonaccni series program with OpenMP tasking constructs.

It is favorable to set up a parallel section in which the function fib() is
called by only one thread. This thread creates the tasks to be processed in
parallel using the task directive.

*/

#include<stdio.h>
#include<omp.h>
#define N 100

int fib(int n)
{
    int x,y;
    if (n < 2) return n;
    #pragma omp task shared(x)
    x = fib(n-1);
    #pragma omp task shared(y)
    y = fib(n-2);
    #pragma omp taskwait
    return x+y;

}


int main(){

int fibonacci;

/*
Execution of a structured block within a parallel region only by the master
thread.
*/
#pragma omp parallel
#pragma omp master
fibonacci=fib(N);
printf("Fibonacci %d th position number is: %d\n",N,fibonacci);

}
