#pragma once
#include <string>
using namespace std;

class State {
public:
    string Id;
    string Name;
    bool IsInitial;
    bool IsFinal;
    bool Enabled;

    State(const string& id, const string& name, bool isInitial, bool isFinal, bool enabled);
};
