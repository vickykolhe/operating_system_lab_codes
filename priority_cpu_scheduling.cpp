#include <bits/stdc++.h>

using namespace std;

struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival Time of the process
    int burstTime;      // Burst Time of the process
    int priority;       // Priority of the process (lower value indicates higher priority)
    int remainingTime;  // Remaining Burst Time (for preemptive)
    int finishTime;     // Finish Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
    bool isCompleted;   // Completion status
};

// Non-Preemptive Priority Scheduling Function
void priorityNonPreemptive(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    while (completed < n)
    {
        int highestPriority = -1;
        int minPriority = INT_MAX;

        // Find the process with the highest priority (smallest priority value) among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isCompleted)
            {
                if (processes[i].priority < minPriority)
                {
                    minPriority = processes[i].priority;
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1)
        {
            currentTime++;
        }
        else
        {
            Process &p = processes[highestPriority];
            currentTime += p.burstTime;
            p.finishTime = currentTime;
            p.turnaroundTime = p.finishTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            p.isCompleted = true;
            completed++;
        }
    }
}

// Preemptive Priority Scheduling Function
void priorityPreemptive(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0, completed = 0;

    while (completed < n)
    {
        int highestPriority = -1;
        int minPriority = INT_MAX;

        // Find the process with the highest priority among arrived processes with remaining burst time
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                if (processes[i].priority < minPriority)
                {
                    minPriority = processes[i].priority;
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1)
        {
            currentTime++;
        }
        else
        {
            Process &p = processes[highestPriority];
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
    cout << "ID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t"
             << process.arrivalTime << "\t"
             << process.burstTime << "\t"
             << process.priority << "\t\t"
             << process.finishTime << "\t"
             << process.turnaroundTime << "\t\t"
             << process.waitingTime << endl;
    }
}

int main()
{
    int n;
    // cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        // cout << "Enter arrival time, burst time, and priority for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isCompleted = false;
    }

    int choice;
    // cout << "Choose Scheduling Method:\n1. Non-Preemptive Priority\n2. Preemptive Priority\n";
    cin >> choice;

    if (choice == 1)
    {
        priorityNonPreemptive(processes);
    }
    else if (choice == 2)
    {
        priorityPreemptive(processes);
    }
    else
    {
        cout << "Invalid choice!";
        return 1;
    }

    displayResults(processes);

    return 0;
}