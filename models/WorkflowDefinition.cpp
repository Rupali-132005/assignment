#include "WorkflowDefinition.h"
#include <unordered_set>
#include <iostream>

WorkflowDefinition::WorkflowDefinition(const std::string& id, const std::string& name,
                                       const std::vector<State>& states, const std::vector<Action>& actions)
    : Id(id), Name(name), States(states), Actions(actions) {}

bool WorkflowDefinition::IsValid() const {
    int initialCount = 0;
    std::unordered_set<std::string> stateIds;
    for (const auto& s : States) {
        if (!s.Enabled) continue;
        if (stateIds.find(s.Id) != stateIds.end()) {
            std::cerr << "Duplicate state ID: " << s.Id << "\n";
            return false;
        }
        stateIds.insert(s.Id);
        if (s.IsInitial) initialCount++;
    }
    if (initialCount != 1) {
        std::cerr << "Workflow must have exactly one initial state, found: " << initialCount << "\n";
        return false;
    }
    // Could add more validation here (e.g., actions refer to valid states)
    return true;
}
