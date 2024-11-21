#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void c_scan_disk_scheduling(int tracks, int shiftTime, int queueSize, vector<int> &requestQueue, int initPos, int dir)
{
    sort(requestQueue.begin(), requestQueue.end());
    int min = 0, max = 0, totalSeekTime = 0;

    for (int i = 0; i < queueSize; i++)
    {
        if (requestQueue[i] > initPos)
        {
            min = i - 1;
            max = i;
            break;
        }
    }

    cout << "||\tCurrent Position\t||\tFinal Position\t||\tSeek Time\t||" << endl;

    if (dir == 2)
    {
        for (int i = min; i >= 0; i--)
        {
            int finalPos = requestQueue[i];
            if (finalPos >= tracks)
            {
                cout << "Track " << finalPos << " Not Available" << endl;
            }
            else
            {
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
            if (i == 0)
            {
                finalPos = 0;
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
                finalPos = tracks - 1;
                seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
        }
        for (int i = queueSize - 1; i >= max; i--)
        {
            int finalPos = requestQueue[i];
            if (finalPos >= tracks)
            {
                cout << "Track " << finalPos << " Not Available" << endl;
            }
            else
            {
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
        }
    }
    else
    {
        for (int i = max; i < queueSize; i++)
        {
            int finalPos = requestQueue[i];
            if (finalPos >= tracks)
            {
                cout << "Track " << finalPos << " Not Available" << endl;
            }
            else
            {
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
            if (i == queueSize - 1)
            {
                finalPos = tracks - 1;
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
                finalPos = 0;
                seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
        }
        for (int i = 0; i <= min; i++)
        {
            int finalPos = requestQueue[i];
            if (finalPos >= tracks)
            {
                cout << "Track " << finalPos << " Not Available" << endl;
            }
            else
            {
                int seekTime = abs(finalPos - initPos) * shiftTime;
                cout << "||\t\t" << initPos << "\t\t||\t\t" << finalPos << "\t\t||\t\t" << seekTime << "\t\t||" << endl;
                totalSeekTime += seekTime;
                initPos = finalPos;
            }
        }
    }

    cout << "Total Seek Time to Process Request Queue: " << totalSeekTime << endl;
}

int main()
{
    int tracks, shiftTime, queueSize, initPos, dir;

    cout << "Enter the Total Number of tracks: ";
    cin >> tracks;
    cout << "Enter the Time taken by the head to move one track to another: ";
    cin >> shiftTime;
    cout << "Enter the Size of Request Queue: ";
    cin >> queueSize;

    vector<int> requestQueue(queueSize);

    cout << "Enter the initial position of read-write head: ";
    cin >> initPos;
    cout << "Enter the requested Tracks: ";
    for (int i = 0; i < queueSize; i++)
    {
        cin >> requestQueue[i];
    }
    cout << "Select Direction: \n1) Current to Max\n2) Current to Min\n";
    cin >> dir;

    c_scan_disk_scheduling(tracks, shiftTime, queueSize, requestQueue, initPos, dir);

    return 0;
}
