#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival Time of the process
    int burstTime;      // Burst Time of the process
    int remainingTime;  // Remaining Burst Time for the process
    int finishTime;     // Finish Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

void roundRobinScheduling(vector<Process> &processes, int timeQuantum)
{
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;

    // Initialize remaining time and arrival status
    for (auto &process : processes)
    {
        process.remainingTime = process.burstTime;
    }

    queue<int> readyQueue; // Queue to manage ready processes
    readyQueue.push(0);    // Start with the first process (assuming all arrive at 0 for simplicity)
    vector<bool> inQueue(n, false);
    inQueue[0] = true;

    while (completed < n)
    {
        int i = readyQueue.front();
        readyQueue.pop();

        // Process selected from the ready queue
        if (processes[i].remainingTime > timeQuantum)
        {
            currentTime += timeQuantum;
            processes[i].remainingTime -= timeQuantum;
        }
        else
        { // Process will finish
            currentTime += processes[i].remainingTime;
            processes[i].remainingTime = 0;
            processes[i].finishTime = currentTime;
            processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
            completed++;
        }

        // Enqueue new processes that have arrived and aren't in the queue
        for (int j = 0; j < n; j++)
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0 && !inQueue[j])
            {
                readyQueue.push(j);
                inQueue[j] = true;
            }
        }

        // If current process still has remaining time, re-add it to the queue
        if (processes[i].remainingTime > 0)
        {
            readyQueue.push(i);
        }

        // If the queue is empty but there are still processes left to complete
        if (readyQueue.empty())
        {
            for (int j = 0; j < n; j++)
            {
                if (processes[j].remainingTime > 0)
                {
                    readyQueue.push(j);
                    inQueue[j] = true;
                    break;
                }
            }
        }
    }
}

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
    int n, timeQuantum;
    // cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        // cout << "Enter arrival time and burst time for process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }

    // cout << "Enter time quantum: ";
    cin >> timeQuantum;

    roundRobinScheduling(processes, timeQuantum);
    displayResults(processes);

    return 0;
}