#include <iostream>
using namespace std;

int main() {
    int n, m;

    // Input number of processes and resources
    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int Allocation[n][m];
    int Max[n][m];
    int Need[n][m];
    int Available[m];

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> Allocation[i][j];
        }
    }

    // Input Max Matrix
    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> Max[i][j];
        }
    }

    // Input Available Resources
    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> Available[i];
    }

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << Need[i][j] << " ";
        }
        cout << endl;
    }

    int Work[m];
    bool Finish[n]={false};

    // Initialize Work and Finish
    for(int i = 0; i < m; i++) {
        Work[i] = Available[i];
    }


    int safeSeq[n];
    int count = 0;

    // Banker's Algorithm
    while (count < n) {
        bool executed = false;

        for (int i = 0; i < n; i++) {

            if (!Finish[i]) {

                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < m; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    safeSeq[count] = i;
                    count++;

                    Finish[i] = true;
                    executed = true;
                }
            }
        }

        // No process can execute
        if (!executed) {
            cout << "\nSystem is NOT in Safe State (Deadlock Possible)\n";
            return 0;
        }
    }

    // Safe State
    cout << "\nSystem is in SAFE State\n";
    cout << "Safe Sequence: ";

    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];

        if (i != n - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}
