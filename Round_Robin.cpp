#include<iostream>
#include<queue>
#include<iomanip>
using namespace std;

int main()
{
    int n, tq;
    cout<<"Enter number of processes: ";
    cin>>n;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    for(int i=0;i<n;i++)
    {
        cout<<"Arrival Time of P"<<i+1<<": ";
        cin>>at[i];

        cout<<"Burst Time of P"<<i+1<<": ";
        cin>>bt[i];

        rt[i] = bt[i]; // remaining time
    }

    cout<<"Enter Time Quantum: ";
    cin>>tq;

    queue<int> q;
    int time = 0, completed = 0;
    bool visited[n] = {false};

    // push first process
    q.push(0);
    visited[0] = true;

    while(completed != n)
    {
        int i = q.front();
        q.pop();

        if(rt[i] > tq)
        {
            time += tq;
            rt[i] -= tq;
        }
        else
        {
            time += rt[i];
            ct[i] = time;
            rt[i] = 0;
            completed++;
        }

        // check new arrivals
        for(int j=0;j<n;j++)
        {
            if(at[j] <= time && !visited[j])
            {
                q.push(j);
                visited[j] = true;
            }
        }

        // if process still not finished
        if(rt[i] > 0)
            q.push(i);

        // if queue becomes empty → CPU idle case
        if(q.empty())
        {
            for(int j=0;j<n;j++)
            {
                if(rt[j] > 0)
                {
                    q.push(j);
                    visited[j] = true;
                    break;
                }
            }
        }
    }

    float avgWT = 0, avgTAT = 0;

    cout<<"\n---------------------------------------------\n";
    cout<<left<<setw(10)<<"Process"
        <<setw(6)<<"AT"
        <<setw(6)<<"BT"
        <<setw(6)<<"CT"
        <<setw(8)<<"TAT"
        <<setw(6)<<"WT"<<endl;
    cout<<"---------------------------------------------\n";

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        cout<<left<<setw(10)<<"P"+to_string(i+1)
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

    cout<<"---------------------------------------------\n";
    cout<<"Average Waiting Time = "<<avgWT<<endl;
    cout<<"Average Turnaround Time = "<<avgTAT<<endl;

    return 0;
}