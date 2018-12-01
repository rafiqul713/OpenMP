/*
Write a parallel program with OpenMP and C which adds two vectors a and b of length n (a, b ∈ R n )
with c = a + b. Use random values for initializing the vector elements.
*/

#include<stdio.h>
#include<omp.h>
int main(){

const int N=100000;
int a[N],b[N],c[N],i;
float time;

for(i=0;i<N;++i){
    a[i]=2*i;
    b[i]=i;
}
time=omp_get_wtime();
#pragma omp parallel for  private(i)
for(i=0;i<N;i++){
    c[i]=a[i]+b[i];
    printf("%d\n",c[i]);
}
time=omp_get_wtime()-time;
printf("Time: %f s\n",time);
}
