#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX 50000
#define max 50000



struct n
{
    int st_index;
    int ed_index;
    int as_ds;
} node[max];

int b[MAX],a[MAX],index1=0;


void insert(int st_ind,int end_ind,int fl)
{
    node[index1].st_index=st_ind;
    node[index1].ed_index=end_ind;
    node[index1++].as_ds=fl;
}



void mergeAlgorithm(int Value,int index,int HighStartingIndex,int HighEndingIndx)
{
    int lower,upper;
    int middle;
    if(Value<a[HighStartingIndex])
        b[index]=Value;
    else if(Value>a[HighEndingIndx])
        b[HighEndingIndx-HighStartingIndex+index+1]=Value;
    else
    {
        lower=0;
        upper=HighEndingIndx-HighStartingIndex;
        while(upper>lower)
        {
            float x1=(float)(upper-lower)/(a[HighStartingIndex+upper]-a[lower+HighStartingIndex]);
            middle=(int)lower+(Value-a[lower+HighStartingIndex])*x1;
            if(Value>a[middle+HighStartingIndex] && Value<a[HighStartingIndex+middle+1])
                break;
            else if(Value<a[HighStartingIndex+middle])
                upper=middle;
            else if(Value>a[middle+HighStartingIndex])
                lower=middle+1;
        }
        b[index+middle+1]=Value;
    }

}

void mergeAlgorithmDescending(int Value,int index,int HighStartingIndex,int HighEndingIndx)
{
    int lower,upper;
    int middle;
    if(Value<a[HighEndingIndx])
        b[index]=Value;
    else if(Value>a[HighStartingIndex])
        b[HighEndingIndx-HighStartingIndex+index+1]=Value;
    else
    {
        lower=0;
        upper=HighEndingIndx-HighStartingIndex;
        while(upper>lower)
        {
            float x1=(float)(upper-lower)/(a[HighEndingIndx-upper]-a[HighEndingIndx-lower]);
            middle=(int)lower+(Value-a[HighEndingIndx-lower])*x1;
            if(Value>a[HighEndingIndx-middle] && Value<a[HighEndingIndx-middle-1])
                break;
            else if(Value<a[HighEndingIndx-middle])
                upper=middle;
            else if(Value>a[HighEndingIndx-middle])
                lower=middle+1;
        }
        b[index+middle+1]=Value;
    }

}
int main()
{
    int i=0,n,k,j,tem,flag,first_ind,end_ind,numberOfItem=0,k1,m1;
    int h,p,q,r,low,high,g;
    double time_spent;
    time_t first,second;
    clock_t begin,end;
    index1=0;
    i=0;
    FILE* file = fopen ("data.txt", "r");
    int x = 0,count=0;
    fscanf (file, "%d", &x);
    while (!feof (file))
    {
        a[i]=x;
        i++;
        numberOfItem++;
        fscanf (file, "%d", &x);
    }
    printf("\nCount: %d\n",i);
    fclose(file);
    begin=clock();
    first_ind=0;
    end_ind=0;
    flag=0;
    tem=a[0];
    k=1;
    while(1)
    {
        while(1)
        {
            if(tem>=a[k]&&k<i)
            {
                end_ind=k;
                tem=a[k];
                k++;
                flag=1;
                continue;
            }
            break;
        }
        if(flag)
        {
            node[index1].st_index=first_ind;
            node[index1].ed_index=end_ind;
            node[index1++].as_ds=flag;
            first_ind=k;
            end_ind=k;
            tem=a[k++];
        }
        while(1)
        {
            if(tem<=a[k] && k<i)
            {
                tem=a[k];
                end_ind=k;
                flag=0;
                k++;
                continue;
            }
            break;
        }
        if(!flag)
        {
            insert(first_ind,end_ind,flag);
            first_ind=end_ind=k;
            tem=a[k++];
        }
        if(end_ind==i)
            break;
    }
    printf("\n");
    g=index1-1;
    h=0;
    while(g/2)
    {
        g/=2;
        h++;
    }
    printf("H=%d\n",h);
    h=(double)log((double)index1-1)/(double)log(2.0);
    printf("H=%d\n",h);
    p=1;
    for(q=0; q<=h; q++,p*=2)
    {
        for(r=0; r<index1; r++)
        {
            if(2*r*p+p>=index1)
                break;
            else
            {
                low=2*p*r;
                high=2*p*r+p;
                k=node[low].st_index;
                if(node[low].as_ds==0 && node[high].as_ds==0)
                {
                    m1=0;
                    for(k1=node[low].st_index; k1<=node[low].ed_index; k1++)
                    {
                        mergeAlgorithm(a[k1],m1++,node[high].st_index,node[high].ed_index);
                    }
                    m1=0;
                    for(k1=node[high].st_index; k1<=node[high].ed_index; k1++)
                    {
                        mergeAlgorithm(a[k1],m1++,node[low].st_index,node[low].ed_index);
                    }

                }
                else if(node[low].as_ds==0 && node[high].as_ds==1)
                {
                    m1=0;
                    for(k1=node[low].st_index; k1<=node[low].ed_index; k1++)
                    {
                        mergeAlgorithmDescending(a[k1],m1++,node[high].st_index,node[high].ed_index);
                    }
                    m1=0;
                    for(k1=node[high].ed_index; k1>=node[high].st_index; k1--)
                    {
                        mergeAlgorithm(a[k1],m1++,node[low].st_index,node[low].ed_index);
                    }

                }

                else if(node[low].as_ds==1 && node[high].as_ds==0)
                {
                    m1=0;
                    for(k1=node[low].ed_index; k1>=node[low].st_index; k1--)
                    {
                        mergeAlgorithm(a[k1],m1++,node[high].st_index,node[high].ed_index);
                    }
                    m1=0;
                    for(k1=node[high].st_index; k1<=node[high].ed_index; k1++)
                    {
                        mergeAlgorithmDescending(a[k1],m1++,node[low].st_index,node[low].ed_index);
                    }




                }

                else if(node[low].as_ds==1 && node[high].as_ds==1)
                {
                    m1=0;
                    for(k1=node[low].ed_index; k1>=node[low].st_index; k1--)
                    {
                        mergeAlgorithmDescending(a[k1],m1++,node[high].st_index,node[high].ed_index);
                    }
                    m1=0;
                    for(k1=node[high].ed_index; k1>=node[high].st_index; k1--)
                    {
                        mergeAlgorithmDescending(a[k1],m1++,node[low].st_index,node[low].ed_index);
                    }

                }

                int n1=0;
                for(k=node[low].st_index; k<=node[high].ed_index; k++)
                {
                    a[k]=b[n1++];
                }
                node[low].ed_index=node[high].ed_index;
                node[high].st_index=node[low].st_index;
                node[low].as_ds=0;
                node[high].as_ds=0;
                memset(b,sizeof(b),0);
            }
        }
    }
    end=clock();
    time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
    printf("\nThe difference is: %f seconds\n",time_spent);
    FILE *f;
    f = fopen("output_Adaptive_merge_sort_with_interpolation_search.txt", "w");
    for(k=0; k<numberOfItem; k++)
    {
        fprintf(f,"%d\n",a[k]);

    }
    fclose(f);
    printf("\n");
    printf("output saved to output_Adaptive_merge_sort_with_interpolation_search.txt");
    
    FILE *fp;
    fp = fopen("time_interpolation_search_merge_sort.txt", "w");
    fprintf(fp, "%f", time_spent);
    fclose(fp);
    
    getchar();
    return 0;
}

