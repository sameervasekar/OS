#include<iostream>
using namespace std;

int main()
{
    int n = 5, m = 3;

    int alloc[5][3] = {
        {0,1,0},
        {2,0,0},
        {3,0,2},
        {2,1,1},
        {0,0,2}
    };

    int max[5][3] = {
        {7,5,3},
        {3,2,2},
        {9,0,2},
        {2,2,2},
        {4,3,3}
    };

    int avail[3] = {3,3,2};

    int need[5][3];

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            need[i][j] = max[i][j] - alloc[i][j];

    bool finish[5] = {false};
    int safeSeq[5];
    int work[3];

    for(int i=0;i<m;i++)
        work[i] = avail[i];

    int count = 0;

    while(count < n)
    {
        bool found = false;

        for(int i=0;i<n;i++)
        {
            if(!finish[i])
            {
                bool possible = true;

                for(int j=0;j<m;j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if(possible)
                {
                    for(int j=0;j<m;j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
        {
            cout<<"System is NOT in safe state\n";
            return 0;
        }
    }

    cout<<"System is in SAFE STATE\nSafe sequence: ";
    for(int i=0;i<n;i++)
        cout<<"P"<<safeSeq[i]<<" ";

    return 0;
}