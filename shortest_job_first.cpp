#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival Time of the process
    int burstTime;      // Burst Time of the process
    int remainingTime;  // Remaining Burst Time (for preemptive)
    int finishTime;     // Finish Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
    bool isCompleted;   // Completion status
};

// Non-Preemptive SJF Scheduling Function
void sjfNonPreemptive(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minBurstTime = INT_MAX;

        // Find the shortest burst time among processes that have arrived
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted)
            {
                if (processes[i].burstTime < minBurstTime)
                {
                    minBurstTime = processes[i].burstTime;
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++;
        }
        else
        {
            Process &p = processes[shortest];
            currentTime += p.burstTime;
            p.finishTime = currentTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            p.isCompleted = true;
            completed++;
        }
    }
}

// Preemptive SJF Scheduling Function (Shortest Remaining Time First)
void sjfPreemptive(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    while (completed < n)
    {
        int shortest = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time among arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                if (processes[i].remainingTime < minRemainingTime)
                {
                    minRemainingTime = processes[i].remainingTime;
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++;
        }
        else
        {
            Process &p = processes[shortest];
            p.remainingTime--;
            currentTime++;

            if (p.remainingTime == 0)
            {
                p.finishTime = currentTime;
                p.turnaroundTime = p.finishTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
                completed++;
            }
        }
    }
}

// Function to display results
void displayResults(const vector<Process> &processes)
{
    cout << "ID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t"
             << process.arrivalTime << "\t"
             << process.burstTime << "\t"
             << process.finishTime << "\t"
             << process.turnaroundTime << "\t\t"
             << process.waitingTime << endl;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        // cout << "Enter arrival time and burst time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    int choice;
    // cout << "Choose Scheduling Method:\n1. Non-Preemptive SJF\n2. Preemptive SJF\n";
    cin >> choice;

    if (choice == 1)
    {
        sjfNonPreemptive(processes);
    }
    else if (choice == 2)
    {
        sjfPreemptive(processes);
    }
    else
    {
        cout << "Invalid choice!";
        return 1;
    }

    displayResults(processes);

    return 0;
}
