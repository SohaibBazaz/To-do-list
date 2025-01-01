#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
<<<<<<< HEAD
#include <windows.h>
=======
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7

using namespace std;

struct Task {
    int id;
    string name;
    string description;
    int priority; // 1 (high), 2 (medium), 3 (low)
    int dueDate; // in (YYMMDD)
    string progress; // "in progress" or "completed"
    Task* prev;
    Task* next;

    Task(int id, string name, string description, int priority, int dueDate) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->priority = priority;
        this->dueDate = dueDate;
        this->progress = "in progress"; // Default value
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
string currentUsername;

<<<<<<< HEAD
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setUsername() {
    setColor(10); // Green
    cout << "\nEnter your username: ";
    setColor(7); // White
    getline(cin, currentUsername);
    ifstream file(currentUsername + ".txt");
    if (!file.is_open()) {
        ofstream newFile(currentUsername + ".txt");
        newFile.close();
        setColor(14); // Yellow
        cout << "New file created for user \"" << currentUsername << "\".\n";
    }
    else {
        setColor(11); // Cyan
        cout << "Welcome back, \"" << currentUsername << "\".\n";
    }
    setColor(7); // Reset to White
}

=======
void setUsername() {
    cout << "Enter your username: ";
    getline(cin, currentUsername);
    ifstream file(currentUsername + ".txt");
    if (!file.is_open()) {
        ofstream newFile(currentUsername + ".txt");
        newFile.close();
        cout << "New file created for user \"" << currentUsername << "\".\n";
    }
    else {
        cout << "Welcome back, \"" << currentUsername << "\".\n";
    }
}

>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
void saveToFile() {
    if (currentUsername.empty()) return;
    ofstream file(currentUsername + ".txt");
    if (!file.is_open()) {
<<<<<<< HEAD
        setColor(12); // Red
        cout << "Error: Could not open file to save data.\n";
        setColor(7); // Reset
=======
        cout << "Error: Could not open file to save data.\n";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
        return;
    }
    Task* current = head;
    while (current != nullptr) {
        file << current->id << "," << current->name << "," << current->description << ","
            << current->priority << "," << current->dueDate << "," << current->progress << "\n";
        current = current->next;
    }
    file.close();
}

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
<<<<<<< HEAD
=======

>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
bool isIdPresent(int id) {
    Task* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void addTask(int id, string name, string description, int priority, int dueDate) {
    if (isIdPresent(id)) {
        cout << "Error: Task with ID " << id << " already exists." << endl;
        return;
    }
<<<<<<< HEAD

    Task* newTask = new Task(id, name, description, priority, dueDate);

    if (head == nullptr) {
        head = tail = newTask;
    }
    else if (newTask->priority < head->priority) {
        newTask->next = head;
        head->prev = newTask;
        head = newTask;
    }
    else {
        Task* current = head;
        while (current->next != nullptr && current->next->priority <= newTask->priority) {
            current = current->next;
        }

        newTask->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = newTask;
        }
        else {
            tail = newTask;
        }
        current->next = newTask;
        newTask->prev = current;
    }


    cout << "Task added successfully!" << endl;
=======
    Task* newTask = new Task(id, name, description, priority, dueDate);
    if (head == nullptr) {
        head = tail = newTask;
    }
    else {
        tail->next = newTask;
        newTask->prev = tail;
        tail = newTask;
    }
    sortTask();
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
    saveToFile();
}

void search() {
    int choice;
    cout << "Search by:\n 1. Due Date\n 2. Task Priority\n 3. Task ID" << endl;
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
                cout << "Progress: " << current->progress << endl;
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
        if (pr == "high" || pr == "High")
            priority = 1;
        else if (pr == "medium" || pr == "Medium")
            priority = 2;
        else if (pr == "low" || pr == "Low")
            priority = 3;

        Task* current = head;
        while (current != nullptr) {
            if (current->priority == priority) {
                cout << "Task Found:" << endl;
                cout << "ID: " << current->id << endl;
                cout << "Name: " << current->name << endl;
                cout << "Description: " << current->description << endl;
                cout << "Priority: " << current->priority << endl;
                cout << "Due Date: " << current->dueDate << endl;
                cout << "Progress: " << current->progress << endl;
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
                cout << "Progress: " << current->progress << endl;
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
            cout << "Current Progress (in progress, completed): " << current->progress << endl;
            cout << "Enter new Progress (or press Enter to keep unchanged): ";
            string newProgress;
            getline(cin, newProgress);
            if (!newProgress.empty()) {
                current->progress = newProgress;
            }
            sortTask();
            cout << "Task updated successfully!" << endl;
<<<<<<< HEAD
            saveToFile();
=======
            saveToFile(); 
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
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
            saveToFile();
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

void markCompleted(int id) {
    Task* current = head;
    while (current) {
        if (current->id == id) {
            current->progress = "completed";
            cout << "Task marked as completed.\n";
            saveToFile();
            return;
        }
        current = current->next;
    }
    cout << "Task not found.\n";
}

<<<<<<< HEAD

void display(Task* head) {
    setColor(13); // Light Purple
    cout << "\n================== Task List ==================\n";
    setColor(7); // White

    Task* current = head;
    while (current != nullptr) {
        setColor(11); // Cyan
        cout << "\n----------------------------------------------\n";
        setColor(14); // Yellow
        cout << "ID: " << current->id << "\n";
        cout << "Name: " << current->name << "\n";
        cout << "Description: " << current->description << "\n";
        setColor(10); // Green
        cout << "Priority: " << (current->priority == 1 ? "High" : (current->priority == 2 ? "Medium" : "Low")) << "\n";
        cout << "Due Date: " << current->dueDate << "\n";
        cout << "Progress: " << current->progress << "\n";
        setColor(11); // Cyan
        cout << "----------------------------------------------\n";
=======
void display(Task* head) {
    cout << "Tasks in the list (sorted by priority):\n";
    Task* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id << ", Name: " << current->name << ", Description: " << current->description
            << ", Priority: " << current->priority << ", Due Date: " << current->dueDate
            << ", Progress: " << current->progress << endl;
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
        current = current->next;
    }
    setColor(13); // Light Purple
    cout << "==============================================\n\n";
    setColor(7); // Reset to White
}

void loadFromFile() {
    if (currentUsername.empty()) return;
    ifstream file(currentUsername + ".txt");
    if (!file.is_open()) {
<<<<<<< HEAD
        setColor(14); // Yellow
        cout << "No existing data for user \"" << currentUsername << "\". A new file will be created.\n";
        setColor(7); // Reset
=======
        cout << "No existing data for user \"" << currentUsername << "\". A new file will be created.\n";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int id, priority, dueDate;
        string name, description, progress;

<<<<<<< HEAD
        ss >> id;
        ss.ignore();
        getline(ss, name, ',');
        getline(ss, description, ',');
        ss >> priority;
        ss.ignore();
        ss >> dueDate;
        ss.ignore();
        getline(ss, progress);

=======

        ss >> id;              
        ss.ignore();           
        getline(ss, name, ','); 
        getline(ss, description, ','); 
        ss >> priority;      
        ss.ignore();           
        ss >> dueDate;         
        ss.ignore();           
        getline(ss, progress);  

        
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
        addTask(id, name, description, priority, dueDate);
        Task* lastTask = tail;
        if (lastTask) lastTask->progress = progress;
    }
    file.close();
}

int main() {
<<<<<<< HEAD
    setColor(13); // Light Purple
    cout << "\n\n\n\t\t\t\t---------------------------------\n";
    Sleep(350);
    setColor(11); // Cyan
    cout << "\t\t\t\t\tSmart To-Do List\n";
    Sleep(350);
    setColor(13); // Light Purple
    cout << "\t\t\t\t---------------------------------\n";
    setColor(7); // Reset
    cout << endl;
    Sleep(350);

=======
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
    setUsername();
    loadFromFile();

    int choice;
    do {
<<<<<<< HEAD
        setColor(11); // Cyan
        cout << "\n\t\t\t\t================== Task Management System ==================\n";
        setColor(7); // White
        cout << "\n\t\t\t\t\t--------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t||1. Add Task               ||   \n";
        cout << "\t\t\t\t\t\t||2. Edit Task              ||   \n";
        cout << "\t\t\t\t\t\t||3. Mark Task as Completed ||   \n";
        cout << "\t\t\t\t\t\t||4. Delete Task            ||   \n";
        cout << "\t\t\t\t\t\t||5. Search Task            ||   \n";
        cout << "\t\t\t\t\t\t||6. Undo Last Operation    ||   \n";
        cout << "\t\t\t\t\t\t||7. Display Tasks          ||   \n";
        cout << "\t\t\t\t\t\t||8. Exit                   ||   \n";
        cout << "\t\t\t\t\t---------------------------------------------" << endl;
        cout << "\nEnter your choice: ";

        setColor(14); // Yellow
=======
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Search Task\n";
        cout << "6. Undo Last Operation\n";
        cout << "7. Display Tasks\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
        cin >> choice;
        setColor(7); // Reset

        switch (choice) {
        case 1: {
            int id, priority, dueDate;
            string name, description;
<<<<<<< HEAD
            setColor(10); // Green
=======
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            cout << "Enter Task ID: ";
            setColor(7); // White
            cin >> id;
            cin.ignore();
<<<<<<< HEAD
            setColor(10);
=======
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            cout << "Enter Task Name: ";
            setColor(7);
            getline(cin, name);
            setColor(10);
            cout << "Enter Task Description: ";
            setColor(7);
            getline(cin, description);
<<<<<<< HEAD
            setColor(10);
            cout << "Enter Task Priority (1 for High, 2 for Medium, 3 for Low): ";
            setColor(7);
            cin >> priority;
            setColor(10);
            cout << "Enter Due Date (YYMMDD): ";
            setColor(7);
=======
            cout << "Enter Task Priority (1 for High, 2 for Medium, 3 for Low): ";
            cin >> priority;
            cout << "Enter Due Date (YYMMDD): ";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            cin >> dueDate;
            addTask(id, name, description, priority, dueDate);
            break;
        }
        case 2:
<<<<<<< HEAD
            //editTask;
=======
            editTask;
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            editTask(head);
            break;
        case 3: {
            int id;
<<<<<<< HEAD
            setColor(10);
            cout << "Enter task ID to mark as completed: ";
            setColor(7);
=======
            cout << "Enter task ID to mark as completed: ";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            cin >> id;
            markCompleted(id);
            break;
        }
        case 4: {
            int id;
<<<<<<< HEAD
            setColor(10);
            cout << "Enter Task ID to delete: ";
            setColor(7);
=======
            cout << "Enter Task ID to delete: ";
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
            cin >> id;
            deleteTask(id);
            break;
        }
        case 5:
            search();
            break;
        case 6:
            undo();
            break;
        case 7:
            display(head);
            break;
        case 8:
<<<<<<< HEAD
            setColor(12); // Red
            cout << "Exiting...\n";
            setColor(7); // Reset
            break;
        default:
            setColor(12); // Red
            cout << "Invalid choice, please try again.\n";
            setColor(7); // Reset
        }
    } while (choice != 8);
}
=======
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
>>>>>>> 6a0e3d1c813fad069d764f508e45330c0e94a2f7
