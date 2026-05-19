#include <iostream>
#include <vector>
using namespace std;

// 🔹 Display Allocation
void display(vector<int> process, vector<int> allocation)
{
    cout << "\nProcess\tSize\tBlock\n";
    for (int i = 0; i < process.size(); i++)
    {
        cout << "P" << i+1 << "\t" << process[i] << "\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

// 🔵 First Fit
void firstFit(vector<int> blocks, vector<int> process)
{
    vector<int> alloc(process.size(), -1);

    for (int i = 0; i < process.size(); i++)
    {
        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i])
            {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }

    cout << "\n--- First Fit ---";
    display(process, alloc);
}

// 🔵 Best Fit
void bestFit(vector<int> blocks, vector<int> process)
{
    vector<int> alloc(process.size(), -1);

    for (int i = 0; i < process.size(); i++)
    {
        int best = -1;

        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i])
            {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            alloc[i] = best;
            blocks[best] -= process[i];
        }
    }

    cout << "\n--- Best Fit ---";
    display(process, alloc);
}

// 🔵 Worst Fit
void worstFit(vector<int> blocks, vector<int> process)
{
    vector<int> alloc(process.size(), -1);

    for (int i = 0; i < process.size(); i++)
    {
        int worst = -1;

        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i])
            {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    cout << "\n--- Worst Fit ---";
    display(process, alloc);
}

// 🔵 Next Fit
void nextFit(vector<int> blocks, vector<int> process)
{
    vector<int> alloc(process.size(), -1);
    int last = 0;

    for (int i = 0; i < process.size(); i++)
    {
        int count = 0;

        while (count < blocks.size())
        {
            if (blocks[last] >= process[i])
            {
                alloc[i] = last;
                blocks[last] -= process[i];
                break;
            }

            last = (last + 1) % blocks.size();
            count++;
        }
    }

    cout << "\n--- Next Fit ---";
    display(process, alloc);
}

// 🔹 Main
int main()
{
    int m, n;

    cout << "Enter number of memory blocks: ";
    cin >> m;

    vector<int> blocks(m);
    cout << "Enter block sizes:\n";
    for (int i = 0; i < m; i++)
        cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> process(n);
    cout << "Enter process sizes:\n";
    for (int i = 0; i < n; i++)
        cin >> process[i];

    int choice;

    while (true)
    {
        cout << "\nMENU\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Run All\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: firstFit(blocks, process); break;
            case 2: bestFit(blocks, process); break;
            case 3: worstFit(blocks, process); break;
            case 4: nextFit(blocks, process); break;
            case 5:
                firstFit(blocks, process);
                bestFit(blocks, process);
                worstFit(blocks, process);
                nextFit(blocks, process);
                break;
            case 6: return 0;
            default: cout << "Invalid choice\n";
        }
    }
}