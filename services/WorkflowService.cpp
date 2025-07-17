#include "C:\Users\Kishor\.vscode\assignment\services\WorkflowService.h"
#include <iostream>
#include <chrono>
#include <algorithm>


bool WorkflowService::CreateWorkflowDefinition(const WorkflowDefinition& def) {
    if (!def.IsValid()) {
        std::cerr << "Invalid workflow definition\n";
        return false;
    }
    if (definitions.find(def.Id) != definitions.end()) {
        std::cerr << "Workflow definition already exists: " << def.Id << "\n";
        return false;
    }
    definitions[def.Id] = def;
    return true;
}

std::optional<WorkflowDefinition> WorkflowService::GetWorkflowDefinition(const std::string& id) const {
    auto it = definitions.find(id);
    if (it == definitions.end()) return std::nullopt;
    return it->second;
}

std::optional<WorkflowInstance> WorkflowService::StartWorkflowInstance(const std::string& workflowDefinitionId) {
    auto defIt = definitions.find(workflowDefinitionId);
    if (defIt == definitions.end()) {
        std::cerr << "Workflow definition not found: " << workflowDefinitionId << "\n";
        return std::nullopt;
    }
    const WorkflowDefinition& def = defIt->second;

    std::string initialStateId;
    for (const auto& state : def.States) {
        if (state.IsInitial && state.Enabled) {
            initialStateId = state.Id;
            break;
        }
    }
    if (initialStateId.empty()) {
        std::cerr << "No initial state found in workflow definition\n";
        return std::nullopt;
    }

    // Generate instance ID (in production, use a UUID or better)
    static int instanceCounter = 0;
    instanceCounter++;
    std::string instanceId = "instance_" + std::to_string(instanceCounter);

    WorkflowInstance instance(instanceId, workflowDefinitionId, initialStateId);
    instances[instanceId] = instance;

    return instance;
}

bool WorkflowService::ExecuteActionOnInstance(const std::string& instanceId, const std::string& actionId) {
    auto instIt = instances.find(instanceId);
    if (instIt == instances.end()) {
        std::cerr << "Instance not found: " << instanceId << "\n";
        return false;
    }
    WorkflowInstance& instance = instIt->second;

    auto defIt = definitions.find(instance.WorkflowDefinitionId);
    if (defIt == definitions.end()) {
        std::cerr << "Workflow definition not found for instance: " << instanceId << "\n";
        return false;
    }
    const WorkflowDefinition& def = defIt->second;

    // Find action by ID
    auto actionIt = std::find_if(def.Actions.begin(), def.Actions.end(),
                                 [&](const Action& a) { return a.Id == actionId; });
    if (actionIt == def.Actions.end()) {
        std::cerr << "Action not found: " << actionId << "\n";
        return false;
    }
    const Action& action = *actionIt;

    if (!action.Enabled) {
        std::cerr << "Action is disabled: " << actionId << "\n";
        return false;
    }

    // Check current state is in action's fromStates
    if (std::find(action.FromStates.begin(), action.FromStates.end(), instance.CurrentStateId) == action.FromStates.end()) {
        std::cerr << "Current state (" << instance.CurrentStateId << ") is not valid for this action\n";
        return false;
    }

    // Check if current state is final
    auto stateIt = std::find_if(def.States.begin(), def.States.end(),
                                [&](const State& s) { return s.Id == instance.CurrentStateId; });
    if (stateIt == def.States.end()) {
        std::cerr << "Current state not found in definition\n";
        return false;
    }
    if (stateIt->IsFinal) {
        std::cerr << "Cannot execute action from final state\n";
        return false;
    }

    // Move to new state
    instance.CurrentStateId = action.ToState;

    // Add history entry
    instance.History.push_back({ actionId, std::chrono::system_clock::now() });

    return true;
}

std::optional<WorkflowInstance> WorkflowService::GetWorkflowInstance(const std::string& instanceId) const {
    auto it = instances.find(instanceId);
    if (it == instances.end()) return std::nullopt;
    return it->second;
}
