#pragma once
#include <string>
#include <vector>

struct Action {
    std::string Id;
    std::string Name;
    std::vector<std::string> FromStates;
    std::string ToState;
    bool Enabled;

    Action(const std::string& id, const std::string& name, bool enabled,
           const std::vector<std::string>& fromStates, const std::string& toState);
};

