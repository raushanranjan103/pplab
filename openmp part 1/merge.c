//sort an array of n elements using seq and merge sort

#include<stdio.h>

#include<omp.h>

#include<stdlib.h>

void merge(int a[],int low,int mid,int high){

    int i, j, k, B[100];

    i = low;

    j = mid + 1;

    k = low;

    while (i <= mid && j <= high)

    {

        if (a[i] < a[j])



        {



            B[k] = a[i];//B[k] is a tempeorary array 



            i++;



            k++;



        }



        else



        {



            B[k] = a[j];



            j++;



            k++;



        }



    }



    while (i <= mid)    



    {



        B[k] = a[i];  // this loop will  copy remaining 1/2 array elements  as it is



        k++;



        i++;



    }



    while (j <= high)



    {



        B[k] = a[j];  //this loop will copy remaining other 1/2 array elements  as it is



        k++;



        j++;



    }



    for (int i = low; i <= high; i++)



    {



        a[i] = B[i];  //this loop will copy array elementrs from tempeorary array to main array



    }



}



void mergesortParallel(int a[],int l,int h){

    if(l<h){

        int mid = (l+h)/2;

        

        #pragma omp parallel sections

        {

            #pragma omp section

            mergesortParallel(a,l,mid);

            

            #pragma omp section

            mergesortParallel(a,mid+1,h);

        }

        merge(a,l,mid,h);

    }

}



void mergesortSerial(int a[],int l,int h){

    if(l<h){

        int mid = (l+h)/2;

        

        

        {

            

            mergesortSerial(a,l,mid);

            

            

            mergesortSerial(a,mid+1,h);

        }

        merge(a,l,mid,h);

    }

}





void main(){

    int a[100],num,i;

	printf("enter number:");

	scanf("%d",&num);

	printf("array before sorting");

	for(i=0;i<num;i++){

	       	a[i]= rand()%100;

		printf("%d ",a[i]);

	}

	double start = omp_get_wtime();

	mergesortSerial(a,0,num-1);

	double end = omp_get_wtime();

    printf("\narray after sorting\n");

	for(i =0;i<num;i++) printf("%d ",a[i]);

	double val = end - start;

	printf("\nTime for serial is:%f\n",val);



    start = omp_get_wtime();

    mergesortParallel(a,0,num-1);

    end = omp_get_wtime();

    val = end-start;

    printf("Time for parallel execution is %f\n",val);

}