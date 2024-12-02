#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string name;
    string description;
    int priority; //1 (high), 2(medium), 3(low)
    int dueDate; //in (YYMMDD)
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

void addTask(Task*& head, Task*& tail, int id, string name, string description, int priority, int dueDate) {
    Task* newTask = new Task(id, name, description, priority, dueDate);
    if (head == nullptr)
        head = tail = newTask;
    else {
        Task* current = head;
        while (current != nullptr && current->priority < priority) {
            current = current->next;
        }
        if (current == nullptr) {
            tail->next = newTask;
            newTask->prev = tail;
            tail = newTask;
        }
        else if (current == head) {
            newTask->next = head;
            head->prev = newTask;
            head = newTask;
        }
        else {
            newTask->next = current;
            newTask->prev = current->prev; // Set the previous node for the new task
            current->prev->next = newTask; // Update the next pointer of the previous node
            current->prev = newTask;       // Update the previous pointer of the current node
        }
    }
}

void search(Task* head)
{
    int choice;
    cout << "Search by:\n  1. Due Date\n  2. Task Priority\n  3. Task ID" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int dueDate;
        cout << "Enter Due Date (YYMMDD): ";
        cin >> dueDate;
        Task* current = head;
        while (current != nullptr)
        {
            if (current->dueDate == dueDate)
            {
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
    case 2:
    {
        string pr;
        int priority;
        cout << "Enter Priority (Low, Medium, High): ";
        cin >> pr;
        if (pr == "high" || pr == "High")
        {
            priority = 1;
        }
        if (pr == "medium" || pr == "Medium")
        {
            priority = 2;
        }
        if (pr == "low" || pr == "Low")
        {
            priority = 3;
        }
        Task* current = head;
        while (current != nullptr)
        {
            if (current->priority == priority)
            {
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
    case 3:
    {
        int id;
        cout << "Enter Task ID: ";
        cin >> id;
        Task* current = head;
        while (current != nullptr)
        {
            if (current->id == id)
            {
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
void display() {

}
int main() {
    Task* head = nullptr;
    Task* tail = nullptr;

    addTask(head, tail, 1, "Task 1", "Description 1", 1, 241130);
    addTask(head, tail, 2, "Task 2", "Description 2", 2, 241201);
    addTask(head, tail, 3, "Task 3", "Description 3", 3, 241225);

    // Displaying the tasks
    cout << "Tasks in the list (sorted by priority):\n";
    Task* current = head;
    while (current != nullptr) {
        cout << "Name: " << current->name << ", Description: " << current->description
            << ", Priority: " << current->priority << ", Due Date: " << current->dueDate << endl;
        current = current->next;
    }

    search(head);


}