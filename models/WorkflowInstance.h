#pragma once
#include <string>
#include <vector>
#include <chrono>

struct ActionHistoryEntry {
    std::string ActionId;
    std::chrono::system_clock::time_point Timestamp;
};

class WorkflowInstance {
public:
    std::string Id;
    std::string WorkflowDefinitionId;
    std::string CurrentStateId;
    std::vector<ActionHistoryEntry> History;

    WorkflowInstance(const std::string& id, const std::string& workflowDefinitionId, const std::string& initialStateId);
};


