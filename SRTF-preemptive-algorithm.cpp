#include <bits/stdc++.h>
using namespace std;
int n;
map<int, pair<int, string>> input;
map<string, int> allArrivalTime;
map<string, int> allBurstTime;
vector<pair<pair<string, int>, int>> seq;
int nxt = 0;
priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
vector<pair<string, int>> ans;
vector<pair<string, pair<int, int>>> waitingTimeAndTurnAroundTime;

void takeInput()
{
    cout << "How many process ? ";
    cin >> n;
    cout << "Enter the Process,Arrival time and Burst time -> " << '\n';
    cout << '\n'
         << "Process - Arrival Time - Burst Time " << '\n';
    for (int i = 1; i <= n; i++)
    {
        string process;
        int arrivalTime, burstTime;
        cin >> process >> arrivalTime >> burstTime;
        input[arrivalTime] = {burstTime, process};
        allArrivalTime[process] = arrivalTime;
        allBurstTime[process] = burstTime;
    }
}

void processTillMaxArrivalTime()
{
    while (true)
    {
        auto it = input.end();
        it--;
        int maxArrival = it->first;
        if (nxt > maxArrival)
            break;

        pair<int, string> current;
        if (input.find(nxt) != input.end())
            current = input[nxt];
        else
        {
            current.first = seq.back().second;
            current.second = seq.back().first.first;
        }
        if ((int)seq.size() >= 1)
        {
            pair<int, string> prev;
            prev.first = seq.back().second;
            prev.second = seq.back().first.first;
            int prevBurst = prev.first;
            if (current.first > prevBurst)
            {
                current.first = prev.first;
                current.second = prev.second;
            }
        }
        int currentBurst = current.first;
        string currentProcess = current.second;
        currentBurst--;
        nxt++;
        seq.push_back({{currentProcess, nxt}, currentBurst});
        input[allArrivalTime[currentProcess]] = {currentBurst, currentProcess};
    }
}

void processRemainingTask()
{
    for (int i = 0; i < (int)seq.size() - 1; i++)
    {
        if (seq[i].first.first == seq[i + 1].first.first)
            continue;
        else
            ans.push_back({seq[i].first.first, seq[i].first.second});
    }
    ans.push_back({seq[(int)seq.size() - 1].first.first, seq[(int)seq.size() - 1].first.second});

    for (auto it : input)
        pq.push({it.second.first, it.second.second});

    int lastArriveProcessTime = (pq.top().first + ans.back().second);
    string p = ans.back().first;
    pq.pop();
    ans.pop_back();
    ans.push_back({p, lastArriveProcessTime});

    while (!pq.empty())
    {
        pair<int, string> current = pq.top();
        int totalBurstTime = (current.first + ans.back().second);
        ans.push_back({current.second, totalBurstTime});
        pq.pop();
    }
}

void calculateTurnAroundTimeWaitingTimeAndAverageTime()
{
    map<string, int> allExitTime;
    for (auto [f, s] : ans)
        allExitTime[f] = max(allExitTime[f], s);
    cout << '\n';
    double totalWaitingTime = 0.0, totalTurnAroundTime = 0.0;
    cout << '\n'
         << "Individual Calculation : " << '\n';
    for (auto [f, s] : allExitTime)
    {
        string process;
        int arrivalTime, exitTime, turnAroundTime, burstTime, waitingTime;
        process = f;
        arrivalTime = allArrivalTime[process];
        exitTime = s;
        turnAroundTime = (exitTime - arrivalTime);
        waitingTime = (turnAroundTime - allBurstTime[process]);
        waitingTimeAndTurnAroundTime.push_back({process, {waitingTime, turnAroundTime}});
        totalWaitingTime += waitingTime;
        totalTurnAroundTime += turnAroundTime;
    }
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
    for (int i = 1; i <= ((int)ans.size() * 2) + 3; i++)
        cout << "-";
    cout << "Gantt Chart";
    for (int i = 1; i <= ((int)ans.size() * 2) + 3; i++)
        cout << "-";
    cout << '\n';

    for (int i = 1; i <= (int)ans.size(); i++)
        cout << "________";
    cout << '\n';
    for (int i = 0; i < (int)ans.size(); i++)
        cout << "|   " << ans[i].first << "  ";
    cout << "|\n|_______|";
    for (int i = 1; i <= ((int)ans.size() - 1); i++)
        cout << "_______|";
    cout << '\n';
    cout << 0 << "       ";
    for (int i = 0; i < (int)ans.size(); i++)
    {
        if (i == (int)ans.size() - 2)
            cout << ans[i].second << "      ";
        else
            cout << ans[i].second << "       ";
    }
    cout << '\n';
}

int main()
{
    takeInput();
    processTillMaxArrivalTime();
    processRemainingTask();
    calculateTurnAroundTimeWaitingTimeAndAverageTime();
    printGanttChart();
    return 0;
}
