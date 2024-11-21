#include <bits/stdc++.h>
using namespace std;

// Function to calculate page faults using LRU page replacement
int lruPageFaults(vector<int> &referenceString, int frameSize)
{
    unordered_set<int> pages;          // Set to store pages currently in memory
    unordered_map<int, int> recentUse; // Map to store the recent use times of each page
    int pageFaults = 0;
    int time = 0; // Variable to simulate time, tracking the order of page accesses

    for (int page : referenceString)
    {
        // If page is not in memory, it causes a page fault
        if (pages.find(page) == pages.end())
        {
            // If there is still space in memory
            if (pages.size() < frameSize)
            {
                pages.insert(page); // Insert page into memory
            }
            else
            {
                // Find the least recently used page to replace
                int lruPage = -1;
                int lruTime = time;

                for (auto it : pages)
                {
                    if (recentUse[it] < lruTime)
                    {
                        lruTime = recentUse[it];
                        lruPage = it;
                    }
                }

                pages.erase(lruPage); // Remove the least recently used page
                pages.insert(page);   // Insert the new page into memory
            }

            pageFaults++; // Increment page fault count
        }

        // Update the recent use time of the page
        recentUse[page] = time;
        time++; // Increment time for each page access
    }

    return pageFaults;
}

int main()
{
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 0, 7};
    int frameSize = 3;

    int pageFaults = lruPageFaults(referenceString, frameSize);

    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}