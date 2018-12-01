/*
Transform the following program fragment, so that the constructs #pragma omp prallel and #pragma omp for
are used separately.
const int N = 100;
int a[N], b[N], x[N ];
int i;
# pragma omp parallel for shared (a ,b , x ) private ( i ) schedule ( static ) \
num_threads (8) default ( none ) nowait
for (i = 0; i < N; i ++)
{
x[i] = a[i] * b[i ];
}
*/
#include<stdio.h>
#include<omp.h>

int main(){
const int N=10000;
int a[N],b[N],x[N];
int i;
float time;
for(i=0;i<N;i++){
    a[i]=2*i;
    b[i]=i;
}
time=omp_get_wtime();
/*
The mapping of loop iterations to threads of a parallel region can be
specified precisely by using the scheduling parameter.
schedule(static)/Static distribution: The iterations are assigned in blocks of size
block size in a round-robin fashion to the threads of the team.

nowait: At the end of a parallel loop, all participating threads are synchronized
implicitly, which can be avoided by using the parameter nowait.
*/

#pragma omp parallel shared(a,b,x) private(i) num_threads(8) default(none)
#pragma omp for schedule(static) nowait
for(i=0;i<N;i++){
    x[i]=a[i]*b[i];
    //printf("%d\n",x[i]);
}

time=omp_get_wtime()-time;
printf("Parallel program ");
printf("Time needs to computation %f\n",time);
time=omp_get_wtime();
for(i=0;i<N;i++){
    x[i]=a[i]*b[i];
    //printf("%d\n",x[i]);
}
time=omp_get_wtime()-time;
printf("Sequential program ");
printf("Time needs to computation %f\n",time);

}
