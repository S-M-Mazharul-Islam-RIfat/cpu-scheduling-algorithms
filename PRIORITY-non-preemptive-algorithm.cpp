#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<int, pair<string, int>>> input;
vector<int> allWaitingTime, allTurnAroundTime;
void takeInput()
{
    cout << "How many process? ";
    cin >> n;
    cout << "Process - Burst Time - Priority " << '\n';

    for (int i = 1; i <= n; i++)
    {
        string process;
        int burstTime, priority;
        cin >> process >> burstTime >> priority;
        input.push_back({priority, {process, burstTime}});
    }
}
void calculateTurnAroundTimeWaitingTimeAndAverageTime()
{
    sort(input.begin(), input.end());

    int waitingTime = 0, turnAroundTime = input[0].second.second;

    allWaitingTime.push_back(0);
    allTurnAroundTime.push_back(turnAroundTime);

    double totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;
    cout << '\n'
         << "Individual Calculation : " << '\n'
         << '\n';

    for (int i = 0; i < n; i++)
    {
        if (i >= 1)
        {
            turnAroundTime += input[i].second.second;
            allTurnAroundTime.push_back(turnAroundTime);
            totalTurnAroundTime += turnAroundTime;
        }
        cout << "Waiting time for " << input[i].second.first << " -> " << waitingTime << '\n';
        cout << "Turn around time time for " << input[i].second.first << " -> " << turnAroundTime << '\n'
             << '\n';
        if (i < (n - 1))
        {
            waitingTime += input[i].second.second;
            allWaitingTime.push_back(waitingTime);
            totalWaitingTime += waitingTime;
        }
    }

    cout << "Average Calculation : " << '\n'
         << '\n';

    cout << fixed << setprecision(3) << "Average waiting time -> " << (totalWaitingTime / n) << '\n';
    cout << fixed << setprecision(3) << "Average turn around time -> " << (totalTurnAroundTime / n) << '\n';
}
void printGanttChart()
{
    cout << '\n'
         << "----------Gantt Chart-----------" << '\n';
    for (int i = 1; i <= n; i++)
        cout << "________";
    cout << '\n';
    for (int i = 0; i < n; i++)
        cout << "|    " << input[i].second.first << " ";
    cout << "|\n|_______|";
    for (int i = 1; i <= (n - 1); i++)
        cout << "_______|";
    cout << '\n';
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cout << allWaitingTime[i] << "       " << allTurnAroundTime[i];
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
