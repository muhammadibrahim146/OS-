#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Process {
    int pid;
    int executionTime;
    int remainingTime;
    int waitingTime;
    int turnAroundTime;
};

int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Execution Time for Process P" << i + 1 << ": ";
        cin >> p[i].executionTime;
        p[i].remainingTime = p[i].executionTime;
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int currentTime = 0;
    bool done;

    vector<int> executionOrder;
    int lastPid = -1;

    do {
        done = true;

        for (int i = 0; i < n; i++) {
            if (p[i].remainingTime > 0) {
                done = false;

                // Record only when process changes
                if (p[i].pid != lastPid) {
                    executionOrder.push_back(p[i].pid);
                    lastPid = p[i].pid;
                }

                if (p[i].remainingTime > quantum) {
                    currentTime += quantum;
                    p[i].remainingTime -= quantum;
                }
                else {
                    currentTime += p[i].remainingTime;
                    p[i].turnAroundTime = currentTime;
                    p[i].waitingTime = p[i].turnAroundTime - p[i].executionTime;
                    p[i].remainingTime = 0;
                }
            }
        }

    } while (!done);

    float totalWT = 0, totalTAT = 0;

    cout << "\nRound Robin Scheduling Results\n";
    cout << "----------------------------------------\n";
    cout << "Process\tET\tWT\tTAT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].executionTime << "\t"
             << p[i].waitingTime << "\t"
             << p[i].turnAroundTime << endl;

        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnAroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time    = " << totalWT / n << endl;
    cout << "Average Turnaround Time = " << totalTAT / n << endl;

    // Execution Order
    cout << "\nExecution Order: ";
    for (int i = 0; i < executionOrder.size(); i++) {
        cout << "P" << executionOrder[i];
        if (i + 1 < (int)executionOrder.size()) cout << " -> ";
    }
    cout << endl;

    return 0;
}