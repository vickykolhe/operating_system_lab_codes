#include <bits/stdc++.h>
using namespace std;

int PI = 0;

void MOS()
{
    if (PI == 2)
    {
        cout << "opeand error" << endl;
    }
}
int main()
{
    string str;
    cin >> str;
    int n = str.size();

    for (int i = 0; i < n; i++)
    {
        if (i == n - 1 && str[i] == 'H')
        {
            cout << "there is no oprand error" << endl;
            return 0; // Exit program since there's no error
        }
        string IR = str.substr(i + 2, 2);

        if (IR[0] - '0' < 0 || IR[0] - '0' > 9 || IR[1] - '0' < 0 || IR[1] - '0' > 9)
        {
            PI = 2;
            MOS();
            break;
        }
        i += 3;
    }
    return 0;
}