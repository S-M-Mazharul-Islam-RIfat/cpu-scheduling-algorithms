#include <bits/stdc++.h>
using namespace std;
int timeQuantum, n;
map<string, int> input;
bool endAll = false;
vector<pair<string, int>> seq;
int sum = 0;
map<string, int> allExitTime, allEnterTime;
void takeInput()
{

    cout << "Enter time quantum : ";
    cin >> timeQuantum;
    cout << "How many process ? ";
    cin >> n;
    cout << "Enter the Process and Burst time -> " << '\n';
    cout << '\n'
         << "Process - Burst Time " << '\n';

    for (int i = 1; i <= n; i++)
    {
        string process;
        int burstTime;
        cin >> process >> burstTime;
        input[process] = burstTime;
    }
}

void processTheTask()
{

    while (!endAll)
    {
        int cnt = 0;
        for (auto [p, b] : input)
        {
            if (b == 0)
            {
                cnt += (b == 0);
                continue;
            }
            int currentBurstTime = b;
            b -= min(b, timeQuantum);
            sum += min(currentBurstTime, timeQuantum);
            input[p] = b;
            seq.push_back({p, sum});
        }
        if (cnt == n)
            endAll = true;
    }
    cout << '\n'
         << '\n';
}

void adjustTheSequence()
{
    int start, i = 0;

    while (seq[i].first != seq[i + 1].first && i < ((int)seq.size() - 1))
        i++;
    string p = seq[i].first;
    int last = ((seq[(int)seq.size() - 1].second - seq[i].second) + timeQuantum);
    if ((i - 1) >= 0)
        last += seq[i - 1].second;
    int j = (int)seq.size();
    while (j != i)
    {
        j--;
        seq.pop_back();
    }
    seq.push_back({p, last});

    for (auto [f, s] : seq)
    {
        if (f == "P1")
            allEnterTime[f] = 0;
        else
            allEnterTime[f] = min(allEnterTime[f] == 0LL ? LLONG_MAX : allEnterTime[f] * 1LL, s * 1LL);
    }

    for (int i = 0; i < (int)seq.size(); i++)
    {
        pair<string, int> p = seq[i];
        if (p.second == allEnterTime[p.first])
            allEnterTime[p.first] = seq[i - 1].second;
    }

    for (auto [f, s] : seq)
        allExitTime[f] = max(allExitTime[f], s);
}

void calculateTurnAroundTimeWaitingTimeAndAverageTime()
{
    vector<pair<string, pair<int, int>>> waitingTimeAndTurnAroundTime;
    double totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;
    for (auto [f, s] : allEnterTime)
    {
        waitingTimeAndTurnAroundTime.push_back({f, {(allExitTime[f] - input[f]), allExitTime[f]}});
        totalTurnAroundTime += allExitTime[f];
        totalWaitingTime += (allExitTime[f] - input[f]);
    }
    cout << '\n'
         << "Individual Calculation : " << '\n';
    cout << '\n'
         << "Process - Waiting Time - Turn around Time " << '\n';

    for (auto it : waitingTimeAndTurnAroundTime)
        cout << "  " << it.first << "            " << it.second.first << "            " << it.second.second << '\n';

    cout << '\n'
         << '\n'
         << "Average Calculation : " << '\n'
         << '\n';
    cout << fixed << setprecision(3) << "Average waiting time -> " << (totalWaitingTime / n) << '\n';
    cout << fixed << setprecision(3) << "Average turn around time -> " << (totalTurnAroundTime / n) << '\n';
}

void printGanttChart()
{
    cout << '\n'
         << '\n'
         << '\n';
    for (int i = 1; i <= ((int)seq.size() * 2) + 7; i++)
        cout << "-";
    cout << "Gantt Chart";
    for (int i = 1; i <= ((int)seq.size() * 2) + 7; i++)
        cout << "-";
    cout << '\n';

    for (int i = 1; i <= (int)seq.size(); i++)
        cout << "________";
    cout << '\n';
    for (int i = 0; i < (int)seq.size(); i++)
        cout << "|   " << seq[i].first << "  ";
    cout << "|\n|_______|";
    for (int i = 1; i <= ((int)seq.size() - 1); i++)
        cout << "_______|";
    cout << '\n';
    cout << 0 << "       ";
    for (int i = 0; i < (int)seq.size(); i++)
    {
        if (i == (int)seq.size() - 2)
            cout << seq[i].second << "      ";
        else
            cout << seq[i].second << "       ";
    }
    cout << '\n';
}
int main()
{
    takeInput();
    processTheTask();
    adjustTheSequence();
    calculateTurnAroundTimeWaitingTimeAndAverageTime();
    printGanttChart();
    return 0;
}
