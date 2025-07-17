#pragma once
#include <string>
#include <ctime>
using namespace std;

struct HistoryEntry {
    string actionId;
    time_t timestamp;

    HistoryEntry(const string& actionId)
        : actionId(actionId), timestamp(time(nullptr)) {}
};