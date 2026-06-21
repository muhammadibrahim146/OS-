#include <iostream>
#include <iomanip>
using namespace std;

struct Process {
    int pid;
    int executionTime;
    int waitingTime;
    int turnAroundTime;
    float responseRatio;
    bool completed;
};

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter Execution Time for Process P" << i + 1 << ": ";
        cin >> p[i].executionTime;

        p[i].completed = false;
        p[i].waitingTime = 0;
        p[i].turnAroundTime = 0;
    }

    int currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nExecution Order: ";

    for (int count = 0; count < n; count++) {

        int selected = -1;
        float highestRR = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed) {

                int waitingTime = currentTime;

                float rr = (float)(waitingTime + p[i].executionTime)
                           / p[i].executionTime;

                if (rr > highestRR) {
                    highestRR = rr;
                    selected = i;
                }
            }
        }

        p[selected].waitingTime = currentTime;
        p[selected].turnAroundTime =
            p[selected].waitingTime + p[selected].executionTime;
        p[selected].responseRatio = highestRR;

        currentTime += p[selected].executionTime;
        p[selected].completed = true;

        cout << "P" << p[selected].pid;
        if (count < n - 1)
            cout << " -> ";
    }

    cout << "\n\nProcess\tET\tWT\tTAT\tRR\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t"
             << p[i].executionTime << "\t"
             << p[i].waitingTime << "\t"
             << p[i].turnAroundTime << "\t"
             << fixed << setprecision(2)
             << p[i].responseRatio << endl;

        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnAroundTime;
    }

    cout << "\nAverage Waiting Time = "
         << fixed << setprecision(2)
         << totalWT / n << endl;

    cout << "Average Turnaround Time = "
         << fixed << setprecision(2)
         << totalTAT / n << endl;

    return 0;
}