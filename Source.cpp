#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string name;
    string description;
    int priority; // 1 (high), 2 (medium), 3 (low)
    int dueDate; // in (YYMMDD)
    Task* prev;
    Task* next;

    Task(int id, string name, string description, int priority, int dueDate) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->priority = priority;
        this->dueDate = dueDate;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

struct StackNode {
    Task taskData;
    StackNode* next;
};

StackNode* stackTop = nullptr;

Task* head = nullptr;
Task* tail = nullptr;

void sortTask() {
    if (head == nullptr || head->next == nullptr)
        return;

    bool swapped = true;

    while (swapped) {
        swapped = false;
        Task* current = head;

        while (current->next) {
            if (current->priority > current->next->priority) {

                int tempPriority = current->priority;
                current->priority = current->next->priority;
                current->next->priority = tempPriority;
                swapped = true;
            }
            current = current->next;
        }
    }
}

void addTask(int id, string name, string description, int priority, int dueDate) {
    Task* newTask = new Task(id, name, description, priority, dueDate);
    if (head == nullptr)
        head = tail = newTask;
    else {
        tail->next = newTask;
        newTask->prev = tail;
        tail = newTask;
    }
    sortTask();
}

void search() {
    int choice;
    cout << "Search by:\n  1. Due Date\n  2. Task Priority\n  3. Task ID" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1: {
        int dueDate;
        cout << "Enter Due Date (YYMMDD): ";
        cin >> dueDate;
        Task* current = head;
        while (current != nullptr) {
            if (current->dueDate == dueDate) {
                cout << "Task Found:" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Description: " << current->description << endl;
                cout << "Priority: " << current->priority << endl;
                cout << "Due Date: " << current->dueDate << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task with Due Date " << dueDate << " not found." << endl;
        break;
    }
    case 2: {
        int priority;
        cout << "Enter Priority (Low, Medium, High): ";
        string pr;
        cin >> pr;
        if (pr == "high" || pr == "High") priority = 1;
        else if (pr == "medium" || pr == "Medium") priority = 2;
        else if (pr == "low" || pr == "Low") priority = 3;

        Task* current = head;
        while (current != nullptr) {
            if (current->priority == priority) {
                cout << "Task Found:" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Description: " << current->description << endl;
                cout << "Priority: " << current->priority << endl;
                cout << "Due Date: " << current->dueDate << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task with Priority " << priority << " not found." << endl;
        break;
    }
    case 3: {
        int id;
        cout << "Enter Task ID: ";
        cin >> id;
        Task* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "Task Found:" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Description: " << current->description << endl;
                cout << "Priority: " << current->priority << endl;
                cout << "Due Date: " << current->dueDate << endl;
                return;
            }
            current = current->next;
        }
        cout << "Task with ID " << id << " not found." << endl;
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        break;
    }
}


void pushToStack(Task task) {
    StackNode* newNode = new StackNode{ task, stackTop };
    stackTop = newNode;
}


Task popFromStack() {
    if (!stackTop) {
        cout << "Undo stack is empty.\n";
        return Task{ -1, "", "", -1, -1 };
    }

    StackNode* temp = stackTop;
    Task taskData = stackTop->taskData;
    stackTop = stackTop->next;
    delete temp;
    return taskData;
}
void editTask(Task* head) {
    int id;
    cout << "Enter the ID of the task you want to edit: ";
    cin >> id;

    Task* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            pushToStack(*current);
            cout << "Editing Task: " << endl;
            cout << "Current Name: " << current->name << endl;
            cout << "Enter new Name (or press Enter to keep unchanged): ";
            cin.ignore();
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                current->name = newName;
            }

            cout << "Current Description: " << current->description << endl;
            cout << "Enter new Description (or press Enter to keep unchanged): ";
            string newDescription;
            getline(cin, newDescription);
            if (!newDescription.empty()) {
                current->description = newDescription;
            }

            cout << "Current Priority (High, Medium, Low): " << current->priority << endl;
            cout << "Enter new Priority (or press Enter to keep unchanged): ";
            string newPriority;
            getline(cin, newPriority);
            if (!newPriority.empty()) {
                current->priority = stoi(newPriority);
            }

            cout << "Current Due Date (YYMMDD): " << current->dueDate << endl;
            cout << "Enter new Due Date (or press Enter to keep unchanged): ";
            string newDueDate;
            getline(cin, newDueDate);
            if (!newDueDate.empty()) {
                current->dueDate = stoi(newDueDate);
            }
            sortTask();
            cout << "Task updated successfully!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Task with ID " << id << " not found." << endl;
}


void deleteTask(int id) {
    Task* current = head;

    while (current) {
        if (current->id == id) {

            pushToStack(*current);

            if (current == head && current == tail) {

                head = tail = nullptr;
            }
            else if (current == head) {

                head = head->next;
                head->prev = nullptr;
            }
            else if (current == tail) {

                tail = tail->prev;
                tail->next = nullptr;
            }
            else {

                current->prev->next = current->next;
                current->next->prev = current->prev;
            }

            delete current;
            cout << "Task deleted successfully." << endl;
            return;
        }
        current = current->next;
    }
    cout << "Task not found." << endl;
}


void undo() {
    Task restoredTask = popFromStack();

    if (restoredTask.id != -1) {
        addTask(restoredTask.id, restoredTask.name, restoredTask.description, restoredTask.priority, restoredTask.dueDate);
        cout << "Task restored successfully." << endl;
    }
    else {
        cout << "No task to restore." << endl;
    }
}
void display(Task* head) {
    cout << "Tasks in the list (sorted by priority):\n";
    Task* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id << ", Name: " << current->name << ", Description: " << current->description
            << ", Priority: " << current->priority << ", Due Date: " << current->dueDate << endl;
        current = current->next;
    }
}

int main() {
    // Add tasks to test adding functionality
    addTask(1, "Task 1", "Description 1", 1, 241130);
    addTask(2, "Task 2", "Description 2", 2, 241201);
    addTask(3, "Task 3", "Description 3", 3, 241225);

    // Display tasks to verify they are added and sorted by priority
    cout << "\nDisplaying tasks after adding:\n";
    display(head);

    // Test search functionality
    cout << "\nTesting search functionality:\n";
    search();

    // Test edit functionality
    cout << "\nTesting edit functionality:\n";
    editTask(head);

    // Display tasks after editing to verify changes
    cout << "\nDisplaying tasks after editing:\n";
    display(head);

    // Test delete functionality
    cout << "\nDeleting task with ID 2:\n";
    deleteTask(2);

    // Display tasks after deletion
    cout << "\nDisplaying tasks after deleting Task 2:\n";
    display(head);

    // Test undo functionality (should restore the last deleted task)
    cout << "\nTesting undo functionality:\n";
    popFromStack();

    // Display tasks after undo
    cout << "\nDisplaying tasks after undo:\n";
    display(head);

    return 0;
}