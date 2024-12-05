#include <iostream>
#include <string>
using namespace std;

// Structure for Task Nodes
struct Task {
    int id;
    string name;
    string description;
    int priority;
    Task* next;
    Task* prev;
};

// Head and Tail pointers for the Task Linked List
Task* head = nullptr;
Task* tail = nullptr;

// Stack for Undo Feature
struct StackNode {
    Task taskData;
    StackNode* next;
};

StackNode* stackTop = nullptr; // Top of the Stack

// Function to Add Task to Linked List
void addTask(int id, string name, string description, int priority) {
    Task* newTask = new Task{ id, name, description, priority, nullptr, nullptr };

    // If list is empty
    if (!head) {
        head = tail = newTask;
        return;
    }

    // Append at the end
    tail->next = newTask;
    newTask->prev = tail;
    tail = newTask;
}

// Function to Sort Linked List by Priority
void sortTasks() {
    if (!head || !head->next) return; // List is empty or has one node

    Task* current = head;
    bool swapped;

    do {
        swapped = false;
        current = head;

        while (current->next) {
            if (current->priority > current->next->priority) {
                // Swap data
                swap(current->id, current->next->id);
                swap(current->name, current->next->name);
                swap(current->description, current->next->description);
                swap(current->priority, current->next->priority);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Function to Edit a Task
void editTask(int id, string newName, string newDescription, int newPriority) {
    Task* current = head;
    while (current) {
        if (current->id == id) {
            current->name = newName;
            current->description = newDescription;
            current->priority = newPriority;
            sortTasks(); // Re-sort after editing
            cout << "Task updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Task not found.\n";
}

// Function to Push a Task to the Undo Stack
void pushToStack(Task task) {
    StackNode* newNode = new StackNode{ task, stackTop };
    stackTop = newNode;
}

// Function to Pop a Task from the Undo Stack
Task popFromStack() {
    if (!stackTop) {
        cout << "Undo stack is empty.\n";
        return Task{ -1, "", "", -1, nullptr, nullptr };
    }

    StackNode* temp = stackTop;
    Task taskData = stackTop->taskData;
    stackTop = stackTop->next;
    delete temp;
    return taskData;
}

// Function to Delete a Task
void deleteTask(int id) {
    Task* current = head;

    while (current) {
        if (current->id == id) {
            // Push deleted task to Undo Stack
            pushToStack(*current);

            // Remove the node
            if (current == head && current == tail) {
                // Only one node in the list
                head = tail = nullptr;
            }
            else if (current == head) {
                // Deleting head node
                head = head->next;
                head->prev = nullptr;
            }
            else if (current == tail) {
                // Deleting tail node
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                // Deleting middle node
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;
            cout << "Task deleted successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Task not found.\n";
}

// Function to Undo the Last Deletion
void undoDelete() {
    Task restoredTask = popFromStack();

    if (restoredTask.id != -1) {
        addTask(restoredTask.id, restoredTask.name, restoredTask.description, restoredTask.priority);
        sortTasks(); // Re-sort after restoration
        cout << "Task restored successfully.\n";
    }
}

// Function to Display All Tasks
void displayTasks() {
    if (!head) {
        cout << "No tasks available.\n";
        return;
    }

    Task* current = head;
    cout << "Tasks:\n";
    while (current) {
        cout << "ID: " << current->id
            << ", Name: " << current->name
            << ", Description: " << current->description
            << ", Priority: " << current->priority << endl;
        current = current->next;
    }
}

// Main Menu Function
void menu() {
    int choice;

    do {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Delete Task\n";
        cout << "4. Undo Last Deletion\n";
        cout << "5. Display All Tasks\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id, priority;
            string name, description;

            cout << "Enter Task ID: ";
            cin >> id;
            cin.ignore(); // Clear newline
            cout << "Enter Task Name: ";
            getline(cin, name);
            cout << "Enter Task Description: ";
            getline(cin, description);
            cout << "Enter Task Priority: ";
            cin >> priority;

            addTask(id, name, description, priority);
            sortTasks(); // Ensure sorting after addition
            break;
        }
        case 2: {
            int id, priority;
            string newName, newDescription;

            cout << "Enter Task ID to Edit: ";
            cin >> id;
            cin.ignore(); // Clear newline
            cout << "Enter New Task Name: ";
            getline(cin, newName);
            cout << "Enter New Task Description: ";
            getline(cin, newDescription);
            cout << "Enter New Task Priority: ";
            cin >> priority;

            editTask(id, newName, newDescription, priority);
            break;
        }
        case 3: {
            int id;
            cout << "Enter Task ID to Delete: ";
            cin >> id;

            deleteTask(id);
            break;
        }
        case 4:
            undoDelete();
            break;
        case 5:
            displayTasks();
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

// Main Function
int main() {
    menu();
    return 0;
}
