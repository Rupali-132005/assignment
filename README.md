Configurable Workflow Engine (State-Machine API)

A minimal backend service in **.NET 8 / C#** that allows defining and executing configurable workflows using a state-machine model. Built for clarity, correctness, and extensibility within a **2-hour timebox**.

---

 Objective

This API enables clients to:

- ✅ Define workflows as state machines (states + transitions/actions)
- ✅ Start workflow instances
- ✅ Execute transitions with validation
- ✅ Inspect definitions and instance state/history

---

Core Concepts

| Concept             | Required Attributes |
|---------------------|----------------------|
| **State**           | `id`, `name`, `isInitial`, `isFinal`, `enabled` |
| **Action (transition)** | `id`, `name`, `enabled`, `fromStates` (array), `toState` |
| **Workflow Definition** | List of states and actions, must include exactly one initial state |
| **Workflow Instance** | Reference to a definition, current state, action history with timestamps |

---

 Project Structure

```
ConfigurableWorkflowEngine/
├── Models/
│   ├── WorkflowDefinition.cs
│   ├── WorkflowInstance.cs
│   ├── State.cs
│   └── Action.cs
├── Services/
│   └── WorkflowService.cs
├── Program.cs
└── README.md
```

---

## 🛠 Technology Stack

- **Language:** C#
- **Framework:** ASP.NET Core (.NET 8)
- **Architecture:** Minimal API
- **Persistence:** In-memory (no database)
- **Dependencies:** None (only built-in .NET libraries)

---

## ⚙️ Running the API

### 🧾 Prerequisites

- [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0)



> The API will start at `https://localhost:5001` or `http://localhost:5000`.

---

API Endpoints

 Create a workflow definition

```http
POST /workflows
```

```json
{
  "id": "leave-approval",
  "name": "Leave Approval",
  "states": [
    { "id": "pending", "name": "Pending", "isInitial": true },
    { "id": "approved", "name": "Approved", "isFinal": true },
    { "id": "rejected", "name": "Rejected", "isFinal": true }
  ],
  "actions": [
    { "id": "approve", "name": "Approve", "fromStates": ["pending"], "toState": "approved", "enabled": true },
    { "id": "reject", "name": "Reject", "fromStates": ["pending"], "toState": "rejected", "enabled": true }
  ]
}
```

---

Start a workflow instance

```http
POST /workflows/leave-approval/instances
```

**Response:**
```json
{
  "id": "instance-abc123",
  "definitionId": "leave-approval",
  "currentState": "pending"
}
```

---

 Execute an action

```http
POST /instances/instance-abc123/actions/approve
```

**Validation ensures:**
- Action exists and is enabled
- Current state is allowed in `fromStates`
- Instance is not in a final state

---

### 🔍 Get instance state and history

```http
GET /instances/instance-abc123
```

```json
{
  "id": "instance-abc123",
  "definitionId": "leave-approval",
  "currentState": "approved",
  "history": [
    { "action": "approve", "timestamp": "2025-07-18T10:45:23Z" }
  ]
}
```

---

 Validation Rules

- Only one initial state allowed per workflow
- All referenced states and actions must exist
- No duplicate IDs (states or actions)
- Final states do not allow further transitions
- Action execution only succeeds if:
  - Action is enabled
  - It applies from current state
  - The target state exists

---

 Assumptions

- State/action IDs must be unique within a workflow
- No persistence across restarts (in-memory only)
- Single-threaded use expected (no concurrency handling)
- No authentication/authorization

---

 Known Limitations / TODOs

- [ ] Add JSON file-based persistence
- [ ] Improve validation error messages (structured responses)
- [ ] Add unit tests for workflow execution and validation logic
- [ ] Add retry-safe concurrency support (e.g., locking)

---

 Author

Made by Rupali Hingankar — for demo and evaluation purposes.
