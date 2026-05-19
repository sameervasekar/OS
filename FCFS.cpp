#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n;

    cout<<"Enter number of processes: ";
    cin>>n;

    int at[n], bt[n], ct[n], tat[n], wt[n];

    // Input
    for(int i=0;i<n;i++)
    {
        cout<<"\nArrival Time of P"<<i+1<<": ";
        cin>>at[i];

        cout<<"Burst Time of P"<<i+1<<": ";
        cin>>bt[i];
    }

    int time = 0;

    cout<<"\nGantt Chart:\n";

    for(int i=0;i<n;i++)
    {
        // CPU Idle Condition
        if(time < at[i])
        {
            cout<<"| Idle ";
            time = at[i];
        }

        cout<<"| P"<<i+1<<" ";

        time += bt[i];

        ct[i] = time;

        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];
    }

    cout<<"|\n";

    float avgWT = 0;
    float avgTAT = 0;

    cout<<"\n--------------------------------------------------\n";

    cout<<left
        <<setw(10)<<"Process"
        <<setw(6)<<"AT"
        <<setw(6)<<"BT"
        <<setw(6)<<"CT"
        <<setw(8)<<"TAT"
        <<setw(6)<<"WT"<<endl;

    cout<<"--------------------------------------------------\n";

    for(int i=0;i<n;i++)
    {
        cout<<left
            <<setw(10)<<("P"+to_string(i+1))
            <<setw(6)<<at[i]
            <<setw(6)<<bt[i]
            <<setw(6)<<ct[i]
            <<setw(8)<<tat[i]
            <<setw(6)<<wt[i]
            <<endl;

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    cout<<"--------------------------------------------------\n";

    cout<<"Average Waiting Time = "<<avgWT<<endl;

    cout<<"Average Turnaround Time = "<<avgTAT<<endl;

    return 0;
}