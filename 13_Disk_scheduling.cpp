#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---------------- FCFS ----------------
int FCFS(vector<int> req, int head)
{
    int seek = 0;
    for(int i=0;i<req.size();i++)
    {
        seek += abs(req[i] - head);
        head = req[i];
    }
    return seek;
}

// ---------------- SSTF ----------------
int SSTF(vector<int> req, int head)
{
    int seek = 0;
    vector<bool> visited(req.size(), false);

    for(int i=0;i<req.size();i++)
    {
        int idx = -1, minDist = 1e9;

        for(int j=0;j<req.size();j++)
        {
            if(!visited[j])
            {
                int dist = abs(req[j] - head);
                if(dist < minDist)
                {
                    minDist = dist;
                    idx = j;
                }
            }
        }

        visited[idx] = true;
        seek += abs(req[idx] - head);
        head = req[idx];
    }
    return seek;
}

// ---------------- SCAN ----------------
int SCAN(vector<int> req, int head, int diskSize)
{
    int seek = 0;
    vector<int> left, right;

    for(int i=0;i<req.size();i++)
    {
        if(req[i] < head) left.push_back(req[i]);
        else right.push_back(req[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for(int i=0;i<right.size();i++)
    {
        seek += abs(right[i] - head);
        head = right[i];
    }

    seek += abs((diskSize-1) - head);
    head = diskSize-1;

    for(int i=left.size()-1;i>=0;i--)
    {
        seek += abs(left[i] - head);
        head = left[i];
    }

    return seek;
}

// ---------------- C-SCAN ----------------
int CSCAN(vector<int> req, int head, int diskSize)
{
    int seek = 0;
    vector<int> left, right;

    for(int i=0;i<req.size();i++)
    {
        if(req[i] < head) left.push_back(req[i]);
        else right.push_back(req[i]);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for(int i=0;i<right.size();i++)
    {
        seek += abs(right[i] - head);
        head = right[i];
    }
//end->start and dist between end and start is added to seek time
    seek += abs((diskSize-1) - head);
    head = 0;
    seek += diskSize-1;//

    for(int i=0;i<left.size();i++)
    {
        seek += abs(left[i] - head);
        head = left[i];
    }

    return seek;
}

// ---------------- MAIN ----------------
int main()
{
    int n, head, diskSize;

    cout<<"Enter number of requests: ";
    cin>>n;

    vector<int> request(n);

    cout<<"Enter request queue:\n";
    for(int i=0;i<n;i++)
        cin>>request[i];

    cout<<"Enter initial head position: ";
    cin>>head;

    cout<<"Enter disk size: ";
    cin>>diskSize;

    cout<<"\n----------------------------------------\n";
    cout<<"Algorithm\tSeek Time\n";
    cout<<"----------------------------------------\n";

    cout<<"FCFS\t\t"<<FCFS(request, head)<<endl;
    cout<<"SSTF\t\t"<<SSTF(request, head)<<endl;
    cout<<"SCAN\t\t"<<SCAN(request, head, diskSize)<<endl;
    cout<<"C-SCAN\t\t"<<CSCAN(request, head, diskSize)<<endl;

    return 0;
}