#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<time.h>
#define MAX 50000

using namespace std;

void mergeSort(int arr[],int low,int mid,int high);
void partition(int arr[],int low,int high);

int main()
{

    double time_spent;
    clock_t begin,end;
    int merge[MAX],i,n,index=0;
    FILE* file = fopen ("data.txt", "r");
    int x = 0,count=0;
    fscanf (file, "%d", &x);
    while (!feof (file))
    {
        merge[index]=x;
        index++;
        fscanf (file, "%d", &x);
    }
    printf("\nCount: %d\n",index);
    fclose(file);
    n=index;
    
    begin=clock();
    partition(merge,0,n-1);
    end=clock();
    time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
    printf("\nThe difference is: %f seconds\n",time_spent);
    
    FILE *f;
    f = fopen("output_normal_merge_sort.txt", "w");

    printf("After merge sorting elements saved to output_normal_merge_sort.txt ");
    for(i=0; i<n; i++)
    {
        fprintf(f,"%d\n",merge[i]);
    }
    
    fclose(f);
    
    FILE *fp;
    fp = fopen("time_normal_merge_sort.txt", "w");
    fprintf(fp, "%f", time_spent);
    fclose(fp);
    
    getchar();
    return 0;
}

void partition(int arr[],int low,int high)
{

    int mid;

    if(low<high)
    {
        mid=(low+high)/2;
        partition(arr,low,mid);
        partition(arr,mid+1,high);
        mergeSort(arr,low,mid,high);
    }
}

void mergeSort(int arr[],int low,int mid,int high)
{

    int i,m,k,l,temp[MAX];

    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high))
    {

        if(arr[l]<=arr[m])
        {
            temp[i]=arr[l];
            l++;
        }
        else
        {
            temp[i]=arr[m];
            m++;
        }
        i++;
    }

    if(l>mid)
    {
        for(k=m; k<=high; k++)
        {
            temp[i]=arr[k];
            i++;
        }
    }
    else
    {
        for(k=l; k<=mid; k++)
        {
            temp[i]=arr[k];
            i++;
        }
    }

    for(k=low; k<=high; k++)
    {
        arr[k]=temp[k];
    }
}
