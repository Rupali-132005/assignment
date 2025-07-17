#pragma once
#include <string>
#include <vector>
#include "State.h"
#include "Action.h"

class WorkflowDefinition {
public:
    std::string Id;
    std::string Name;
    std::vector<State> States;
    std::vector<Action> Actions;

    WorkflowDefinition(const std::string& id, const std::string& name,
                       const std::vector<State>& states, const std::vector<Action>& actions);

    bool IsValid() const;  // check for exactly one initial state, no duplicates, etc.
};
