#include <iostream>
#include <string>
using namespace std;

struct Task {
	string name;
	string description;
	int priority;
	int dueDate; //in (YYMMDD)
	Task* prev;
	Task* next;

	Task(string name, string description, int priority, int dueDate) {
		this->name = name;
		this->description = description;
		this->priority = priority;
		this->dueDate = dueDate;
	}
	};

void addTask(Task*& head, Task*& tail, string name, string description, int priority, int dueDate) {
	Task* newTask = new Task(name, description, priority, dueDate);
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
		else if (current==head) {
			newTask->next = head;
			head->prev = newTask;
			head = newTask;
		}
		else {
			newTask->next = current;
			current->prev = newTask;
			current->prev->next = newTask;
			newTask->prev = current->prev;
		}
	}
}
int main() {
	Task* head = nullptr; // Head of the doubly linked list
	Task* tail = nullptr; // Tail of the doubly linked list

	// Adding tasks to the list
	addTask(head, tail, "Task 1", "Complete the project report", 2, 241130); // Low priority
	addTask(head, tail, "Task 2", "Prepare for the presentation", 5, 241128); // High priority
	addTask(head, tail, "Task 3", "Respond to emails", 3, 241129); // Medium priority

	// Displaying the tasks
	cout << "Tasks in the list (sorted by priority):\n";
	Task* current = head;
	while (current != nullptr) {
		cout << "Name: " << current->name << ", Description: " << current->description
			<< ", Priority: " << current->priority << ", Due Date: " << current->dueDate << endl;
		current = current->next;
	}

	return 0;
}
