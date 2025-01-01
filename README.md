# Smart To-Do List Application

A simple and efficient task management system built in C++ that allows users to add, edit, delete, and manage tasks using a linked list and stack data structure. The application supports user-specific task management by saving tasks to a file named after the username.

## Features

- **User  Authentication**: Create a new user or log in to an existing account (using file handling).
- **Task Management**: 
  - Add new tasks with unique IDs, names, descriptions, priorities, and due dates.
  - Edit existing tasks.
  - Mark tasks as completed.
  - Delete tasks.
  - Search for tasks by due date, priority, or ID.
  - Undo the last operation.
- **Data Persistence**: Tasks are saved to a file specific to each user, ensuring data is retained between sessions.
- **Color-Coded Console Output**: Enhanced user experience with color-coded terminal output for better visibility.


### Prerequisites

- A C++ compiler (e.g., g++, Visual Studio)
- Windows operating system (for `windows.h` usage)

### Contributions
- Contributions are welcome! If you have suggestions for improvements or new features, feel free to open an issue or submit a pull request.

# NOTE: 
- There are 2 files: Source.cpp (Which has a GUI Interface for advanced users) and to-do-list-application.cpp (without GUI interface for beginners)
