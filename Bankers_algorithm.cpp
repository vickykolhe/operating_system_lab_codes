#include <bits/stdc++.h>
using namespace std;

bool isSafe(vector<vector<int>> &max, vector<vector<int>> &allocation, vector<int> &available)
{
    int numProcesses = allocation.size();
    int numResources = available.size();

    vector<int> work = available;             // Copy of available resources
    vector<bool> finish(numProcesses, false); // Initially, no process is finished
    vector<int> safeSequence;                 // To store the safe sequence

    while (true)
    {
        bool found = false;
        for (int i = 0; i < numProcesses; i++)
        {
            if (!finish[i])
            {
                // Check if this process can be allocated resources
                bool canProceed = true;
                for (int j = 0; j < numResources; j++)
                {
                    if (max[i][j] - allocation[i][j] > work[j])
                    {
                        canProceed = false;
                        break;
                    }
                }

                // If all required resources are available for process i
                if (canProceed)
                {
                    for (int j = 0; j < numResources; j++)
                    {
                        work[j] += allocation[i][j]; // Release resources after finishing
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        // If no process could proceed, exit the loop
        if (!found)
            break;
    }

    // Check if all processes have finished
    for (bool f : finish)
    {
        if (!f)
        {
            cout << "The system is not in a safe state.\n";
            return false;
        }
    }

    // If all processes finished, print the safe sequence
    cout << "The system is in a safe state.\nSafe sequence: ";
    for (int i : safeSequence)
        cout << "P" << i << " ";
    cout << endl;

    return true;
}

int main()
{
    int numProcesses, numResources;

    // cout << "Enter the number of processes: ";
    cin >> numProcesses;

    // cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    vector<int> available(numResources);

    // cout << "Enter the maximum resource matrix (max[i][j]):\n";
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> max[i][j];
        }
    }

    // cout << "Enter the allocation matrix (allocation[i][j]):\n";
    for (int i = 0; i < numProcesses; i++)
    {
        for (int j = 0; j < numResources; j++)
        {
            cin >> allocation[i][j];
        }
    }

    // cout << "Enter the available resources:\n";
    for (int j = 0; j < numResources; j++)
    {
        cin >> available[j];
    }

    isSafe(max, allocation, available);

    return 0;
}