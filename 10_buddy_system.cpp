#include <iostream>
#include <cmath>
using namespace std;

// Function to find next power of 2
int nextPowerOfTwo(int n)
{
    int power = 1;
    while(power < n)
        power *= 2;
    return power;
}

int main()
{
    int totalMemory, processSize;

    cout<<"Enter total memory size: ";
    cin>>totalMemory;

    cout<<"Enter process memory requirement: ";
    cin>>processSize;

    int blockSize = nextPowerOfTwo(processSize);

    cout<<"\n-----------------------------------\n";
    cout<<"Buddy System Allocation Process\n";
    cout<<"-----------------------------------\n";

    cout<<"Initial Memory Size : "<<totalMemory<<" KB\n";
    cout<<"Requested Size      : "<<processSize<<" KB\n";
    cout<<"Allocated Block     : "<<blockSize<<" KB\n";

    if(blockSize > totalMemory)
    {
        cout<<"\nMemory Allocation Failed (Insufficient Memory)\n";
    }
    else
    {
        cout<<"\nSplitting Process:\n";

        int current = totalMemory;

        while(current > blockSize)
        {
            current /= 2;
            cout<<"Block divided into two parts of size "<<current<<" KB\n";
        }

        cout<<"\nMemory Allocated Successfully!\n";
        cout<<"Internal Fragmentation = "<<blockSize - processSize<<" KB\n";
    }

    return 0;
}