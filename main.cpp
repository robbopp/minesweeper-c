#include <bits/stdc++.h>

using namespace std;

int SIZE, MINES;

void choseDifficulty()
{
    int level;

    cout << "Chose the difficulty:" << '\n';
    cout << "Press 0 for EASY 9x9" << '\n';
    cout << "Press 1 for MEDIUM 16x16" << '\n';
    cout << "Press 2 for HARD 24x24" << '\n';

    cin >> level;
    if (level == 0)
    {
        SIZE = 9;
        MINES = 10;
    }
    if (level == 1)
    {
        SIZE = 16;
        MINES = 40;
    }
    if (level == 2)
    {
        SIZE = 24;
        MINES = 99;
    }
}

int main()
{

    return 0;
}