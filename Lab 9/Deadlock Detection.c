#include <stdio.h>

int main()
{
    int n, m, i, j, k;
    int A[10][10], R[10][10];
    int Av[10], W[10], F[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &A[i][j]);

    printf("Enter Request Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d", &R[i][j]);

    printf("Enter Available Resources:\n");
    for(j=0;j<m;j++)
        scanf("%d", &Av[j]);

    for(j=0;j<m;j++)
        W[j] = Av[j];

    for(i=0;i<n;i++)
    {
        int zero = 1;
        for(j=0;j<m;j++)
            if(A[i][j] != 0)
                zero = 0;

        F[i] = zero;
    }

    while(1)
    {
        int found = 0;

        for(i=0;i<n;i++)
        {
            if(F[i] == 0)
            {
                for(j=0;j<m;j++)
                    if(R[i][j] > W[j])
                        break;

                if(j == m)
                {
                    for(k=0;k<m;k++)
                        W[k] += A[i][k];

                    F[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    printf("Deadlocked Processes: ");

    for(i=0;i<n;i++)
        if(F[i] == 0)
            printf("P%d ", i);

    return 0;
}
