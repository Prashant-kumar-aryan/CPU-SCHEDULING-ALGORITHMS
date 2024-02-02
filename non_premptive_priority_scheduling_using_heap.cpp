
// Contributed BY Prashant Kumar Aryan
// Mail me for any bugs found in this code -prashantkr2698@gmail.com
// if u want to know the implementaion of this code u can use gpt for that i am not adding any comment lines
#include <bits/stdc++.h>
using namespace std;
struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int finish_time;
    int turnaround_time;
    int waiting_time;
};
class myComparator
{
public:
    int operator()(struct Process &p1, const Process &p2)
    {
        return p1.arrival_time > p2.arrival_time;
    }
};
class ready_queue_comp
{
public:
    int operator()(struct Process &p1, const Process &p2)
    {
        return p1.priority > p2.priority;
    }
};
class compans
{
public:
    int operator()(struct Process &p1, const Process &p2)
    {
        return p1.id > p2.id;
    }
};
priority_queue<Process, vector<Process>, myComparator> proc;
priority_queue<Process, vector<Process>, ready_queue_comp> ready_queue;
vector<Process> ans;
int main()
{
    int n;
    cout << "Enter the no of processes : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Process p1;
        cout << "P " << i + 1;
        p1.id = i + 1;
        cout << "Arrival Time: ";
        cin >> p1.arrival_time;
        cout << "Burst Time: ";
        cin >> p1.burst_time;
        cout << "Priority: ";
        cin >> p1.priority;
        proc.push(p1);
    }
    int curr = 0; // curr time of the gannt chart
    int NOP = n;
    cout << endl
         << endl
         << "-----Gantt Chart -----" << endl
         << endl;
    while (!proc.empty())
    {
        Process p = proc.top();

        while (p.arrival_time <= curr)
        {
            ready_queue.push(proc.top());
            proc.pop();
            if (!(proc.empty()))
            {
                p = proc.top();
            }
            else
            {
                break;
            }
        }
        if (ready_queue.empty())
        {
            cout << "|IDLE for (" << p.arrival_time - curr << ") sec |";
            curr = p.arrival_time;
        }
        else
        {
            Process next = ready_queue.top();
            cout << "| P " << next.id << "(" << curr << " - ";
            ready_queue.pop();

            next.finish_time = curr + next.burst_time;
            curr = next.finish_time;

            next.turnaround_time = next.finish_time - next.arrival_time;

            next.waiting_time = next.turnaround_time - next.burst_time;

            cout << curr << ") |";
            ans.push_back(next);
        }
    }
    while (!ready_queue.empty())
    {

        Process next = ready_queue.top();
        cout << "| P " << next.id << " " << curr << " - ";
        ready_queue.pop();

        next.finish_time = curr + next.burst_time;
        curr = next.finish_time;

        next.turnaround_time = next.finish_time - next.arrival_time;

        next.waiting_time = next.turnaround_time - next.burst_time;

        cout << curr << " | ";
        ans.push_back(next);
    }
    printf("\n\n\nProcess\t Arrival Time\t Burst Time\t Priority\t Finish Time\t Turnaround Time\t Waiting Time\n");
    for (auto &it : ans)
    {
        cout << endl
             << it.id << "\t\t" << it.arrival_time << "\t\t" << it.burst_time << "\t\t" << it.priority << "\t\t" << it.finish_time << "\t\t" << it.turnaround_time << "\t\t" << it.waiting_time;
    }
    int average_tat = 0;
    int average_wt = 0;
    for (int i = 0; i < n; i++)
    {
        average_tat += ans[i].turnaround_time;
        average_wt += ans[i].waiting_time;
    }
    cout << "\n\nAverage Turn Around Time :" << (double)average_tat / (double)n;
    cout << "\nAverage waiting Time :" << (double)average_wt / (double)n;

    return 0;
}
