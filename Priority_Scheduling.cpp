#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    int at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n];
    bool done[n] = {false};

    for(int i=0;i<n;i++)
    {
        cout<<"Arrival Time of P"<<i+1<<": ";
        cin>>at[i];

        cout<<"Burst Time of P"<<i+1<<": ";
        cin>>bt[i];

        cout<<"Priority of P"<<i+1<<": ";
        cin>>pr[i];   // smaller value = higher priority
    }

    int completed = 0, time = 0;

    while(completed < n)
    {
        int idx = -1;
        int highest_priority = 9999;

        // find highest priority process among arrived
        for(int i=0;i<n;i++)
        {
            if(at[i] <= time && !done[i])
            {
                if(pr[i] < highest_priority)
                {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        if(idx == -1)
        {
            time++; // CPU idle
            continue;
        }

        // execute process
        time += bt[idx];
        ct[idx] = time;

        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        done[idx] = true;
        completed++;
    }

    float avgWT = 0, avgTAT = 0;

    cout<<"\n---------------------------------------------\n";
    cout<<left<<setw(10)<<"Process"
        <<setw(6)<<"AT"
        <<setw(6)<<"BT"
        <<setw(8)<<"PR"
        <<setw(6)<<"CT"
        <<setw(8)<<"TAT"
        <<setw(6)<<"WT"<<endl;
    cout<<"---------------------------------------------\n";

    for(int i=0;i<n;i++)
    {
        cout<<left<<setw(10)<<"P"+to_string(i+1)
            <<setw(6)<<at[i]
            <<setw(6)<<bt[i]
            <<setw(8)<<pr[i]
            <<setw(6)<<ct[i]
            <<setw(8)<<tat[i]
            <<setw(6)<<wt[i]
            <<endl;

        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    cout<<"---------------------------------------------\n";
    cout<<"Average Waiting Time = "<<avgWT<<endl;
    cout<<"Average Turnaround Time = "<<avgTAT<<endl;

    return 0;
}