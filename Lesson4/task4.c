/*
What is the problem in the following program. Describe the problem
and the situation where it occurs.

*/


#include<stdio.h>
#include<omp.h>
int x =0;
int y =0;

void fun1 () {
    # pragma omp critical(one)
    {
        fun2 ();
        x +=1;

    }

}

void fun2 () {
    # pragma omp critical(two)
    y +=1;
}

void fun3 () {
    # pragma omp critical(two)
    {   y -=1;
        fun4 ();
    }
}


void fun4 () {
    # pragma omp critical(one)
    x -=1;
}

void main ( int argc , char ** argv ) {
int i;
# pragma omp parallel private (i )
{
    for (i =0; i < 10; i ++) {
        fun1 ();
        fun3 ();

        }
    }
printf ("%d---------%d\n" ,x ,y );
}


/*
    In this situation deadlock occurs.
    Thread 1 call fun1() and access critical section one then call fun2() and access
    critical section two. On the other hand, Thread 2 call function 3 want to access critical
    section two which is acquired by Thread 1. Besides, Thread 2 also call fun4  which is
    deal with critical section one. As a result a circular waiting happen.

    Thread 1: CS(one)->CS(two)
    Thread 2: CS(two)->CS(one)

    Circular waiting leads to Deadlock.

*/
