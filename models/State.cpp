#include "State.h"
using namespace std;

State::State(const string& id, const string& name, bool isInitial, bool isFinal, bool enabled)
    : Id(id), Name(name), IsInitial(isInitial), IsFinal(isFinal), Enabled(enabled) {}
