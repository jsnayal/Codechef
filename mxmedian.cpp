#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d",&T);

    while(T--)
    {
        int N;
        scanf("%d",&N);

        int sizze=2*N;
        int A[100010];
        for(int i=0;i<sizze;i++)
        {
            scanf("%d",&A[i]);
        }

        sort(A,A+sizze);
        /*for(int i=0;i<sizze;i++)
        {
            printf("%d ",A[i]);
        }
        */
        int median_index=(N+sizze-1)/2;
        printf("%d\n",A[median_index]);

        for(int i=0;i<N;i++)
        {
            printf("%d %d ",A[i],A[i+N]);
        }
        printf("\n");
    }
    return 0;
}
