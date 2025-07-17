#include <iostream>
#include "C:\Users\Kishor\.vscode\assignment\models\State.h"
#include "C:\Users\Kishor\.vscode\assignment\models\Action.h"
#include "C:\Users\Kishor\.vscode\assignment\models\WorkflowDefinition.h"
#include "C:\Users\Kishor\.vscode\assignment\services\WorkflowService.h"

int main() {
    // Create states
    State s1("s1", "Start", true, false, true);
    State s2("s2", "In Progress", false, false, true);
    State s3("s3", "Completed", false, true, true);

    std::vector<State> states = { s1, s2, s3 };

    // Create actions (transitions)
    Action a1("a1", "Start to Progress", true, {"s1"}, "s2");
    Action a2("a2", "Progress to Complete", true, {"s2"}, "s3");

    std::vector<Action> actions = { a1, a2 };

    // Create workflow definition
    WorkflowDefinition workflowDef("wf1", "Simple Workflow", states, actions);

    // Create workflow service
    WorkflowService service;

    // Add workflow definition
    if (!service.CreateWorkflowDefinition(workflowDef)) {
        std::cerr << "Failed to create workflow definition\n";
        return 1;
    }

    std::cout << "Workflow definition created.\n";

    // Start a workflow instance
    auto instanceOpt = service.StartWorkflowInstance("wf1");
    if (!instanceOpt.has_value()) {
        std::cerr << "Failed to start workflow instance\n";
        return 1;
    }

    auto instance = instanceOpt.value();
    std::cout << "Started workflow instance with ID: " << instance.Id << "\n";
    std::cout << "Current state: " << instance.CurrentStateId << "\n";

    // Execute action a1
    if (service.ExecuteActionOnInstance(instance.Id, "a1")) {
        std::cout << "Executed action a1\n";
    } else {
        std::cerr << "Failed to execute action a1\n";
    }

    // Get updated instance info
    instanceOpt = service.GetWorkflowInstance(instance.Id);
    if (instanceOpt.has_value()) {
        instance = instanceOpt.value();
        std::cout << "Current state after a1: " << instance.CurrentStateId << "\n";
    }

    // Execute action a2
    if (service.ExecuteActionOnInstance(instance.Id, "a2")) {
        std::cout << "Executed action a2\n";
    } else {
        std::cerr << "Failed to execute action a2\n";
    }

    // Get updated instance info again
    instanceOpt = service.GetWorkflowInstance(instance.Id);
    if (instanceOpt.has_value()) {
        instance = instanceOpt.value();
        std::cout << "Current state after a2: " << instance.CurrentStateId << "\n";
    }

    // Print action history
    std::cout << "Action history:\n";
    for (const auto& entry : instance.History) {
        std::time_t tt = std::chrono::system_clock::to_time_t(entry.Timestamp);
        std::cout << " - Action ID: " << entry.ActionId << ", Timestamp: " << std::ctime(&tt);
    }

    return 0;
}
