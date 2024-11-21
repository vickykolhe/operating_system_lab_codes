#include <bits/stdc++.h>
using namespace std;

int PI = 0;

void MOS()
{
    if (PI == 1)
    {
        cout << "opcode error" << endl;
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
            cout << "there is no opcode error" << endl;
            return 0; // Exit program since there's no error
        }
        string IR = str.substr(i, 2);

        if (!((IR[0] == 'G' && IR[1] == 'D') || (IR[0] == 'P' && IR[1] == 'D') || (IR[0] == 'H' && IR[1] == ' ') || (IR[0] == 'L' && IR[1] == 'R') || (IR[0] == 'S' && IR[1] == 'R') || (IR[0] == 'C' && IR[1] == 'R') || (IR[0] == 'B' && IR[1] == 'T')))
        {
            PI = 1;
            MOS();
            break;
        }
        i += 3;
    }
    return 0;
}
