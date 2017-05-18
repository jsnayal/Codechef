#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d",&T);

    while(T--)
    {
        int n;
        scanf("%d",&n);

        int maxm= -1;
        for(int i=1;i<=n;i++)
        {
            int ai;
            scanf("%d",&ai);

            if(ai>maxm)
            maxm=ai;
        }

        printf("%d",n-maxm);
        printf("\n");
    }
    return 0;
}
