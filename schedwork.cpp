#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;
// Add prototypes for any helper functions here

// Create a new schedule
void newSched(AvailabilityMatrix& temp, const size_t dailyNeed, DailySchedule& sched);

// Helper to check if the worker can work more
bool workerHelper(DailySchedule& sched, size_t worker, const AvailabilityMatrix& avail, const size_t maxShifts);

bool ScheduleHelper(
        size_t day,
        size_t worker,
        AvailabilityMatrix& temp,
        const size_t maxShifts,
        const size_t dailyNeed,
        DailySchedule& sched,
        vector<size_t> workedID);

// Add your implementation of schedule() and other helper functions here
bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if (avail.size() == 0U) {
        return false;
    }
    sched.clear();
    // Add your code below
    AvailabilityMatrix temp = avail;
    vector<size_t> workedID(temp[0].size());
    newSched(temp, dailyNeed, sched);
    return ScheduleHelper(0, 0, temp, maxShifts, dailyNeed, sched, workedID);
}

void newSched(AvailabilityMatrix& temp, const size_t dailyNeed, DailySchedule& sched) {
    // create a new sched
    for (size_t i = 0; i < temp.size(); i++) {
        vector<Worker_T> vec(dailyNeed, temp[0].size() + 1);
        sched.push_back(vec);
    }
}

bool ScheduleHelper(
        size_t day,
        size_t worker,
        AvailabilityMatrix& temp,
        const size_t maxShifts,
        const size_t dailyNeed,
        DailySchedule& sched,
        vector<size_t> workedID) {

    if (worker == dailyNeed && day == temp.size() - 1) {
        return true;
    } else if (day != temp.size()) {
        size_t newDay = day;
        size_t newWorker = worker + 1;
        if (newWorker == sched[0].size()) {
            // if column value becomes the max available value , move to the next row, col starts at 0
            newDay++;
            newWorker = 0;
        }
        if (sched[day][worker] > temp[0].size() + 1) {
            // if the current position of the board is greater than the min val iterate to the next col
            return ScheduleHelper(newDay, newWorker, temp, maxShifts, dailyNeed, sched, workedID);
        }
        for (size_t i = 0; i < temp[0].size(); i++) {
            sched[day][worker] = i;
            if (maxShifts > workedID[i] && workerHelper(sched, i, temp, maxShifts)) {
                if ((temp[day][i] == 1)) {
                    workedID[i]++;
                    bool status = ScheduleHelper(newDay, newWorker, temp, maxShifts, dailyNeed, sched, workedID);
                    if (status) {
                        return true;
                    } else {
                        temp[day][i] = 1;
                        workedID[i]--;
                    }
                }
            }
        }
        // backtrack
        sched[day][worker] = temp[0].size() + 1;
        return false;
    }

    return true;
}

bool workerHelper(DailySchedule& sched, size_t worker, const AvailabilityMatrix& avail, const size_t maxShifts) {
    for (size_t i = 0; i < sched.size(); i++) {
        if (avail[i][worker] == 0) {
            continue;
        }
        if (count(sched[i].begin(), sched[i].end(), worker) > 1) {
            return false;
        }
    }
    return true;
}