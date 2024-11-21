#include <bits/stdc++.h>
using namespace std;

int calculate(vector<int> &refstr, int framsize)
{
    unordered_set<int> pages;
    queue<int> pageq;
    int falt = 0;

    for (int page : refstr)
    {
        if (pages.find(page) == pages.end())
        {
            if (pages.size() < framsize)
            {
                pages.insert(page);
                pageq.push(page);
                falt++;
            }
            else
            {
                int rm = pageq.front();
                pageq.pop();
                pages.erase(rm);

                pages.insert(page);
                pageq.push(page);
                falt++;
            }
        }
    }
    return falt;
}

int main()
{
    vector<int> refstr = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 0, 7};
    int framsize = 3;

    int pagefault = calculate(refstr, framsize);
    cout << pagefault;

    return 0;
}