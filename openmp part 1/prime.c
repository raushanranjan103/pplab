#include<stdio.h>

#include<stdlib.h>

#include<omp.h>



//primes

int isprime(int n){

    for(int i=2;i<=n/2;i++){

        if(n%i==0)

            return 0;

    }

    return 1;

}



void main(){

    int i=0,n,x=2,primes[1100];

    printf("\n enter the value of n");

    scanf("%d",&n);

    double start = omp_get_wtime();

    #pragma omp parallel

    while(i<n){

        if(isprime(x)){

            primes[i] = x;

            #pragma omp atomic 

            i++;

        }

        #pragma omp atomic

        x++;

    }

    double end = omp_get_wtime();

    printf("parallel exec time: %f\n",end-start);



    i=0;x=2;

    start =omp_get_wtime();

    while(i<n){

        if(isprime(x)){

            primes[i] = x;

            i++;

        }

        x++;

    }

    end = omp_get_wtime();

    printf("serial exec time: %f\n",end-start);

    printf("\n now lets print the prime nos\n");

    int count=0;

    for(int num = 1;num<=n;num++){

      count = 0;

      for(i=2;i<=num/2;i++){

         if(num%i==0){

            count++;

         break;

      }

   }

   if(count==0 && num!= 1)

      printf("%d ",num);

   }

}

