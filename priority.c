#include<stdio.h>

void sort(int at[],int bt[],int pr[],int p[],int n)
{
    int temp;
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(at[i]>at[j])
            {
                temp=at[i];
                at[i]=at[j];
                at[j]=temp;

                temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;

                temp=pr[i];
                pr[i]=pr[j];
                pr[j]=temp;

                temp=p[i];
                p[i]=p[j];
                p[j]=temp;

            }
        }
    }

}


void completionTime(int ct[],int at[],int bt[],int pr[],int p[],int n)
{
    int total=bt[0];
    ct[0]=total;
    for(int i=1; i<n; i++)
    {
        if(at[i] >total)
        {
            total=at[i]-total + bt[i]+bt[i-1];
            ct[i]=total;
        }
        else
        {
            int k=0;
            int readyp[n];
            int readya[n];
            int readyb[n];
            int readypr[n];

            for(int j=i; j<n; j++)
            {
                if(at[j] <total)
                {
                    readyp[k]=p[j];
                    readya[k]=at[j];
                    readyb[k]=bt[j];
                    readypr[k]=pr[j];
                    k++;
                }
            }
            sort(readya,readyb,readypr,readyp,k);
            int g=i;
            int index=0;
            for(int g=i; g<k; g++)
            {
                at[g]=readya[index];
                bt[g]=readyb[index];
                pr[g]=readypr[index];
                p[g]=readyp[index];
                index++;
            }
            total=total+bt[i];
            ct[i]=total;
        }
    }
}
void print(int arr[],int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d \t",arr[i]);
    }
    printf("\n");
}
int main()
{
    int n;

    printf("Enter the number of processes\n");
    scanf("%d",&n);
    int p[n];
    int bt[n];
    int at[n];
    int pr[n];
    int ct[n];
    int tat[n];
    int wt[n];
    int rt[n];
    float awt=0, atat=0;
    printf("Enter arrival time , burst time and priority of the processes\n");
    for(int i=0; i<n; i++)
    {
        p[i]=i+1;
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
    }
    sort(at,bt,pr,p,n);
    completionTime(ct,at,bt,pr,p,n);
    for(int i=0; i<n; i++)
    {
        tat[i]=ct[i]-at[i];
    }
    for(int i=0; i<n; i++)
    {
        wt[i]=tat[i]-bt[i];
    }
    for(int i=0; i<n; i++)
    {
        rt[i]=wt[i];
    }
    printf("Pid\tAt\tBT\tPr\tCT\tTAT\tWT\tRT\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i],at[i],bt[i],pr[i],ct[i],tat[i],wt[i],rt[i]);
    }
    for(int i=0; i<n; i++)
    {
        atat+=tat[i];
        awt+=wt[i];
    }

    atat=atat/n;
    awt=awt/n;
    printf("\n avg tat=%f and avg wt=%f\n",atat, awt);
    return 0;
}
