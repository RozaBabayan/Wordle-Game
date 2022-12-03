
// main() program to test your schedule function.
// Feel free to modify this program in any way you need for testing.
// It will not be graded.
#include "schedwork.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void printSchedule(const DailySchedule& sched);

int main() {
    // Replace the matrix below with your test case
    AvailabilityMatrix avail = {{1, 1, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 1}, {1, 0, 0, 1}};
    DailySchedule sched;
    bool solutionFound = schedule(avail, 2, 2, sched);
    if (solutionFound) {
        printSchedule(sched);
    } else {
        cout << "No solution found!" << endl;
    }
    return 0;
}

void printSchedule(const DailySchedule& sched) {
    int day = 0;
    for (auto s : sched) {
        cout << "Day " << day << ": ";
        for (auto nurse : s) {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}
