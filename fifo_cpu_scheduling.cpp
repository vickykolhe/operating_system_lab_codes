#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id;
    int arival;
    int burst;
    int complete;
    int TAT;
    int wait;
};

void calculate(vector<process> &pro)
{
    int ct = 0;

    for (int i = 0; i < pro.size(); i++)
    {
        if (ct < pro[i].arival)
        {
            ct = pro[i].arival;
        }

        pro[i].complete = ct + pro[i].burst;
        pro[i].TAT = pro[i].complete - pro[i].arival;
        pro[i].wait = pro[i].TAT - pro[i].burst;
        ct = pro[i].complete;
    }
}

void displayResults(const vector<process> &processes)
{
    cout << "ID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n";
    for (const auto &process : processes)
    {
        cout << process.id << "\t"
             << process.arival << "\t"
             << process.burst << "\t"
             << process.complete << "\t"
             << process.TAT << "\t\t"
             << process.wait << endl;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<process> pro(n);
    for (int i = 0; i < n; i++)
    {
        pro[i].id = i + 1;
        cin >> pro[i].arival >> pro[i].burst;
    }

    calculate(pro);
    displayResults(pro);

    return 0;
}