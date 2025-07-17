#include "WorkflowInstance.h"

WorkflowInstance::WorkflowInstance(const std::string& id, const std::string& workflowDefinitionId, const std::string& initialStateId)
    : Id(id), WorkflowDefinitionId(workflowDefinitionId), CurrentStateId(initialStateId) {}
