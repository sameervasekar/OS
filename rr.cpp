#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n, tq;

    cout<<"Enter number of processes: ";
    cin>>n;

    int at[n], bt[n], rem_bt[n];
    int ct[n], tat[n], wt[n];

    // Input
    for(int i=0;i<n;i++)
    {
        cout<<"\nArrival Time of P"<<i+1<<": ";
        cin>>at[i];

        cout<<"Burst Time of P"<<i+1<<": ";
        cin>>bt[i];

        rem_bt[i] = bt[i];
    }

    cout<<"\nEnter Time Quantum: ";
    cin>>tq;

    int time = 0;
    int completed = 0;

    cout<<"\nGantt Chart:\n";

    while(completed < n)
    {
        bool found = false;

        for(int i=0;i<n;i++)
        {
            // Process has arrived and still remaining
            if(at[i] <= time && rem_bt[i] > 0)
            {
                found = true;

                cout<<"| P"<<i+1<<" ";

                // If remaining burst time > time quantum
                if(rem_bt[i] > tq)
                {
                    time += tq;

                    rem_bt[i] -= tq;
                }
                else
                {
                    // Process completes
                    time += rem_bt[i];

                    ct[i] = time;

                    rem_bt[i] = 0;

                    completed++;
                }
            }
        }

        // CPU Idle
        if(!found)
        {
            cout<<"| Idle ";
            time++;
        }
    }

    cout<<"|\n";

    float avgWT = 0;
    float avgTAT = 0;

    // Calculate TAT and WT
    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];

        avgWT += wt[i];

        avgTAT += tat[i];
    }

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
    }

    avgWT /= n;
    avgTAT /= n;

    cout<<"--------------------------------------------------\n";

    cout<<"Average Waiting Time = "<<avgWT<<endl;

    cout<<"Average Turnaround Time = "<<avgTAT<<endl;

    return 0;
}