#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include "C:\Users\Kishor\.vscode\assignment\models\WorkflowDefinition.h"
#include "C:\Users\Kishor\.vscode\assignment\models\WorkflowInstance.h"
#include "C:\Users\Kishor\.vscode\assignment\models\Action.h"

class WorkflowService {
private:
    std::unordered_map<std::string, WorkflowDefinition> definitions;
    std::unordered_map<std::string, WorkflowInstance> instances;

public:
    bool CreateWorkflowDefinition(const WorkflowDefinition& def);
    std::optional<WorkflowDefinition> GetWorkflowDefinition(const std::string& id) const;

    std::optional<WorkflowInstance> StartWorkflowInstance(const std::string& workflowDefinitionId);
    bool ExecuteActionOnInstance(const std::string& instanceId, const std::string& actionId);
    std::optional<WorkflowInstance> GetWorkflowInstance(const std::string& instanceId) const;
};
