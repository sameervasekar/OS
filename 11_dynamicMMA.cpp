#include <iostream>
#include <vector>
using namespace std;

// ---------------- FIFO ----------------
int FIFO(vector<int> pages, int frames)
{
    vector<int> mem;
    int faults = 0, idx = 0;

    for(int i=0;i<pages.size();i++)
    {
        bool hit = false;

        for(int j=0;j<mem.size();j++)
        {
            if(mem[j] == pages[i])
                hit = true;
        }

        if(!hit)
        {
            if(mem.size() < frames)
                mem.push_back(pages[i]);
            else
            {
                mem[idx] = pages[i];
                idx = (idx + 1) % frames;
            }
            faults++;
        }
    }
    return faults;
}

// ---------------- LRU ----------------
int LRU(vector<int> pages, int frames)
{
    vector<int> mem;
    vector<int> recent;
    int faults = 0;

    for(int i=0;i<pages.size();i++)
    {
        bool hit = false;

        for(int j=0;j<mem.size();j++)
        {
            if(mem[j] == pages[i])
            {
                hit = true;
                recent[j] = i;
            }
        }

        if(!hit)
        {
            if(mem.size() < frames)
            {
                mem.push_back(pages[i]);
                recent.push_back(i);
            }
            else
            {
                int lruIndex = 0;
                for(int j=1;j<recent.size();j++)
                {
                    if(recent[j] < recent[lruIndex])
                        lruIndex = j;
                }

                mem[lruIndex] = pages[i];
                recent[lruIndex] = i;
            }
            faults++;
        }
    }
    return faults;
}

// ---------------- OPTIMAL ----------------
int OPTIMAL(vector<int> pages, int frames)
{
    vector<int> mem;
    int faults = 0;

    for(int i=0;i<pages.size();i++)
    {
        bool hit = false;

        for(int j=0;j<mem.size();j++)
        {
            if(mem[j] == pages[i])
                hit = true;
        }

        if(!hit)
        {
            if(mem.size() < frames)
                mem.push_back(pages[i]);
            else
            {
                int farthest = -1, index = -1;

                for(int j=0;j<mem.size();j++)
                {
                    int k;
                    for(k=i+1;k<pages.size();k++)
                    {
                        if(mem[j] == pages[k])
                            break;
                    }

                    if(k > farthest)
                    {
                        farthest = k;
                        index = j;
                    }
                }

                mem[index] = pages[i];
            }
            faults++;
        }
    }
    return faults;
}

// ---------------- MAIN ----------------
int main()
{
    vector<int> ref;
    int n;
    cout<<"Enter number of page references: ";
    cin>>n;
    cout<<"Enter reference string: ";
    for(int i=0;i<n;i++)
    {
        int page;
        cin>>page;
        ref.push_back(page);
    }
    int frames = 3;

    cout<<"--------------------------------------\n";
    cout<<"Page Replacement Analysis\n";
    cout<<"--------------------------------------\n";

    cout<<"Reference String: ";
    for(int i=0;i<ref.size();i++)
        cout<<ref[i]<<" ";

    cout<<"\nNumber of Frames: "<<frames<<"\n";

    int f1 = FIFO(ref, frames);
    int f2 = LRU(ref, frames);
    int f3 = OPTIMAL(ref, frames);

    cout<<"\n--------------------------------------\n";
    cout<<"Algorithm\tPage Faults\n";
    cout<<"--------------------------------------\n";
    cout<<"FIFO\t\t"<<f1<<endl;
    cout<<"LRU\t\t"<<f2<<endl;
    cout<<"OPTIMAL\t\t"<<f3<<endl;

    return 0;
}