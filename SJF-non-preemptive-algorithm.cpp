#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<string, int>> processAndBurstTime;
vector<int> allWaitingTime, allTurnAroundTime;

bool customSort(pair<string, int> a, pair<string, int> b)
{
    if (a.second != b.second)
        return a.second < b.second;
    return a.first < b.first;
}

void takeInput()
{
    cout << "How many process? -> ";
    cin >> n;
    cout << "Enter the Process and Burst time : " << '\n';
    cout << '\n'
         << "Process - Burst Time " << '\n';

    for (int i = 1; i <= n; i++)
    {
        string process;
        int burstTime;
        cin >> process >> burstTime;
        processAndBurstTime.push_back({process, burstTime});
    }
    sort(processAndBurstTime.begin(), processAndBurstTime.end(), customSort);
    cout << '\n';
}

void calculateTurnAroundTimeWaitingTimeAndAverageTime()
{
    int waitingTime = 0, turnAroundTime = processAndBurstTime[0].second;

    allWaitingTime.push_back(0);
    allTurnAroundTime.push_back(turnAroundTime);

    double totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;
    totalTurnAroundTime += turnAroundTime;

    cout << '\n'
         << "Individual Calculation : " << '\n'
         << '\n';
    for (int i = 0; i < n; i++)
    {
        if (i >= 1)
        {
            turnAroundTime += processAndBurstTime[i].second;
            allTurnAroundTime.push_back(turnAroundTime);
            totalTurnAroundTime += turnAroundTime;
        }
        cout << "Waiting time for " << processAndBurstTime[i].first << " -> " << waitingTime << '\n';
        cout << "Turn around time for " << processAndBurstTime[i].first << " -> " << turnAroundTime << '\n';
        if (i < (n - 1))
        {
            waitingTime += processAndBurstTime[i].second;
            allWaitingTime.push_back(waitingTime);
            totalWaitingTime += waitingTime;
        }
        cout << '\n';
    }

    cout << '\n'
         << "Average Calculation : " << '\n'
         << '\n';

    cout << fixed << setprecision(3) << "Average waiting time -> " << (totalWaitingTime / n) << '\n';
    cout << fixed << setprecision(3) << "Average turn around time -> " << (totalTurnAroundTime / n) << '\n';
}

void printGanttChart()
{
    cout << '\n'
         << '\n';
    cout << '\n'
         << "-------Gantt Chart-------" << '\n';
    for (int i = 1; i <= n; i++)
        cout << "________";
    cout << '\n';
    for (int i = 0; i < n; i++)
        cout << "|   " << processAndBurstTime[i].first << "  ";
    cout << "|\n|_______|";
    for (int i = 1; i <= (n - 1); i++)
        cout << "_______|";
    cout << '\n';
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cout << allWaitingTime[i] << "      " << allTurnAroundTime[i];
        else
            cout << "      " << allTurnAroundTime[i];
    }
    cout << '\n'
         << '\n';
}

int main()
{
    takeInput();
    calculateTurnAroundTimeWaitingTimeAndAverageTime();
    printGanttChart();
    return 0;
}
