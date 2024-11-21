#include <bits/stdc++.h>

using namespace std;

// Function to find the optimal page to replace
int findOptimalPage(const vector<int> &referenceString, int currentIndex, const unordered_set<int> &pages)
{
    int farthest = currentIndex;
    int pageToReplace = -1;

    for (int page : pages)
    {
        int nextUse = -1;

        // Look ahead in the reference string to find when this page will be used next
        for (int i = currentIndex + 1; i < referenceString.size(); i++)
        {
            if (referenceString[i] == page)
            {
                nextUse = i;
                break;
            }
        }

        // If the page is not found in the future, select it for replacement
        if (nextUse == -1)
        {
            return page;
        }

        // Track the page with the farthest next usage
        if (nextUse > farthest)
        {
            farthest = nextUse;
            pageToReplace = page;
        }
    }

    return pageToReplace;
}

// Function to calculate page faults using Optimal page replacement
int optimalPageFaults(const vector<int> &referenceString, int frameSize)
{
    unordered_set<int> pages; // To store the current pages in memory
    int pageFaults = 0;

    for (int i = 0; i < referenceString.size(); i++)
    {
        int page = referenceString[i];

        // If page is not in memory, it causes a page fault
        if (pages.find(page) == pages.end())
        {
            // If there is space in memory, add the page
            if (pages.size() < frameSize)
            {
                pages.insert(page);
            }
            else
            {
                // Find the optimal page to replace
                int pageToReplace = findOptimalPage(referenceString, i, pages);
                pages.erase(pageToReplace);
                pages.insert(page);
            }

            pageFaults++; // Increment page fault count
        }
    }

    return pageFaults;
}

int main()
{
    vector<int> referenceString = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 0, 7};
    int frameSize = 3;

    int pageFaults = optimalPageFaults(referenceString, frameSize);

    cout << "Number of page faults: " << pageFaults << endl;

    return 0;
}
