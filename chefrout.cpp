#include<bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    scanf("%d",&T);

    while(T--)
    {
        char str[100005];
        scanf("%s",str);

        int state=0;
        int flag=0;
        for(int i=0;str[i]!='\0';i++)
        {
            int curr=str[i]-64;
            if(curr<state)
            {
                flag=1;
                break;
            }
            else
            {
                state=curr;
            }
        }
        if(flag==0)
        printf("yes");
        else
        printf("no");

        printf("\n");
    }
    return 0;
}
