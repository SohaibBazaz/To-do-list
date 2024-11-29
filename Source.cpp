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
