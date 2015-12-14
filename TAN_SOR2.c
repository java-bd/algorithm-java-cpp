#include<stdio.h>
#include<time.h>
#include<math.h>

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

void Merge(int low,int high)
{
    int i,j,k;

    k=node[low].st_index;

    if(node[low].as_ds==0 && node[high].as_ds==0 )
    {
        i=node[low].st_index;
        j=node[high].st_index;

        while(i<=node[low].ed_index&&j<= node[high].ed_index)
        {
            if(a[i]<=a[j])
                b[k++]=a[i++];
            else
                b[k++]=a[j++];
        }
        if(i>node[low].ed_index)
            while(j<= node[high].ed_index) b[k++]=a[j++];
        else
            while(i<= node[low].ed_index) b[k++]=a[i++];
    }
    else if(node[low].as_ds==0 && node[high].as_ds==1 )
    {
        i=node[low].st_index;
        j=node[high].ed_index;

        while(i<=node[low].ed_index&&j>= node[high].st_index)
        {
            if(a[i]<=a[j])
                b[k++]=a[i++];
            else
                b[k++]=a[j--];
        }
        if(i>node[low].ed_index)
            while(j>= node[high].st_index) b[k++]=a[j--];
        else
            while(i<= node[low].ed_index) b[k++]=a[i++];
    }
    else if(node[low].as_ds==1 && node[high].as_ds==0 )
    {
        i=node[low].ed_index;
        j=node[high].st_index;

        while(i>=node[low].st_index&&j<= node[high].ed_index)
        {
            if(a[i]<=a[j])
                b[k++]=a[i--];
            else
                b[k++]=a[j++];
        }
        if(j>node[high].ed_index)
            while(i>= node[low].st_index) b[k++]=a[i--];
        else
            while(j<= node[high].ed_index) b[k++]=a[j++];
    }
    else if(node[low].as_ds==1 && node[high].as_ds==1 )
    {
        i=node[low].ed_index;
        j=node[high].ed_index;

        while(i>=node[low].st_index&&j>= node[high].st_index)
        {
            if(a[i]<=a[j])
                b[k++]=a[i--];
            else
                b[k++]=a[j--];
        }
        if(i<node[low].st_index)
            while(j>= node[high].st_index) b[k++]=a[j--];
        else
            while(i>= node[low].st_index) b[k++]=a[i--];
    }
    for(k=node[low].st_index; k<=node[high].ed_index; k++)     a[k]=b[k];

    node[low].ed_index=node[high].ed_index;
    node[high].st_index=node[low].st_index;
    node[low].as_ds=0;
    node[high].as_ds=0;
}

int main()
{
    int i=0,n,k,j,tem,flag,first_ind,end_ind,numberOfItem=0;
    double time_spent;
    int h,p,q,r,low,high,g,x,count;
    time_t first, second;
    clock_t begin,end;
    //first = time(NULL);

    //freopen("tan2.txt","r",stdin);
    //freopen("out2.txt","w",stdout);

    index1=0;
    i=0;
    FILE* file = fopen ("data.txt", "r");
    x = 0;
    count=0;
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


            //insert(first_ind,end_ind,flag);
            first_ind=k;
            end_ind=k;
            tem=a[k++];
        }

        while(1)
        {
            if(tem<=a[k]&&k<i)
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

        if(end_ind==i) break;
    }

    // for(k=0; k<index1; k++)
    //     printf("%d %d %d\n",node[k].st_index,node[k].ed_index,node[k].as_ds );
    printf("\n");
    g=index1-1;
    h=0;
    while(g/2)
    {
        g/=2;
        h++;
    }

    printf("%d " ,h);
    h=(double) log((double)index1-1)/(double)log(2.0);
    printf("%d \n" ,h);
    p=1;
    for(q=0; q<=h; q++,p*=2)
    {
        for(r=0; r<index1; r++)
        {
            if(2*r*p+p>=index1) break;
            else
            {
                low=2*p*r;
                high=2*p*r+p;
                k=node[low].st_index;
                if(node[low].as_ds==0 && node[high].as_ds==0 )
                {
                    i=node[low].st_index;
                    j=node[high].st_index;

                    while(i<=node[low].ed_index&&j<= node[high].ed_index)
                    {
                        if(a[i]<=a[j])
                            b[k++]=a[i++];
                        else
                            b[k++]=a[j++];
                    }
                    if(i>node[low].ed_index)
                        while(j<= node[high].ed_index) b[k++]=a[j++];
                    else
                        while(i<= node[low].ed_index) b[k++]=a[i++];
                }
                else if(node[low].as_ds==0 && node[high].as_ds==1 )
                {
                    i=node[low].st_index;
                    j=node[high].ed_index;

                    while(i<=node[low].ed_index&&j>= node[high].st_index)
                    {
                        if(a[i]<=a[j])
                            b[k++]=a[i++];
                        else
                            b[k++]=a[j--];
                    }
                    if(i>node[low].ed_index)
                        while(j>= node[high].st_index) b[k++]=a[j--];
                    else
                        while(i<= node[low].ed_index) b[k++]=a[i++];
                }
                else if(node[low].as_ds==1 && node[high].as_ds==0 )
                {
                    i=node[low].ed_index;
                    j=node[high].st_index;

                    while(i>=node[low].st_index&&j<= node[high].ed_index)
                    {
                        if(a[i]<=a[j])
                            b[k++]=a[i--];
                        else
                            b[k++]=a[j++];
                    }
                    if(j>node[high].ed_index)
                        while(i>= node[low].st_index) b[k++]=a[i--];
                    else
                        while(j<= node[high].ed_index) b[k++]=a[j++];
                }
                else if(node[low].as_ds==1 && node[high].as_ds==1 )
                {
                    i=node[low].ed_index;
                    j=node[high].ed_index;

                    while(i>=node[low].st_index&&j>= node[high].st_index)
                    {
                        if(a[i]<=a[j])
                            b[k++]=a[i--];
                        else
                            b[k++]=a[j--];
                    }
                    if(i<node[low].st_index)
                        while(j>= node[high].st_index) b[k++]=a[j--];
                    else
                        while(i>= node[low].st_index) b[k++]=a[i--];
                }
                for(k=node[low].st_index; k<=node[high].ed_index; k++)     a[k]=b[k];

                node[low].ed_index=node[high].ed_index;
                node[high].st_index=node[low].st_index;
                node[low].as_ds=0;
                node[high].as_ds=0;


            }
        }
    }
    end=clock();
    time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
    printf("\nThe difference is: %f seconds\n",time_spent);
    FILE *f;
    f = fopen("output_Tan_sort.txt", "w");

    for(k=0; k<numberOfItem; k++)
    {
        fprintf(f,"%d\n",a[k]);
    }
    fclose(f);
    
    FILE *fp;
    fp = fopen("time_tan_sor2.txt", "w");
    fprintf(fp, "%f", time_spent);
    fclose(fp);

    printf("output saved to output_Tan_sort.txt");
    getchar();
    return 0;

}

