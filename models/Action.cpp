#include "Action.h"

Action::Action(const std::string& id, const std::string& name, bool enabled,
               const std::vector<std::string>& fromStates, const std::string& toState)
    : Id(id), Name(name), Enabled(enabled), FromStates(fromStates), ToState(toState) {}

