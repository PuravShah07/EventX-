# EventX – Event Management System (C++)

EventX is a console-based Event Management System developed in C++ using Object-Oriented Programming (OOP) principles and file handling. The application enables organizers to create and manage events, while customers can view events and book tickets through a menu-driven interface.

---

## Features

### User Management

* Sign up and sign in functionality
* Role-based access control:

  * Organizer
  * Customer
* User credentials stored using file handling

---

### Organizer Features

* Create and list new events
* View all listed events
* Automatic management of ticket availability

---

### Customer Features

* View available events
* Book tickets for events
* View booked tickets for the current session

---

### File Handling

* users.txt stores user credentials and roles
* events.txt stores event details and ticket availability
* Data persists across multiple executions of the program

---

## Technologies Used

* Programming Language: C++
* Concepts and Tools:

  * Object-Oriented Programming (OOP)
  * Classes and Inheritance
  * File Handling using ifstream and ofstream
  * Vectors and Strings
  * Menu-driven console application design

---

## Project Structure

```
EventX/
│
├── main.cpp        // Source code
├── users.txt       // User data (auto-generated)
├── events.txt      // Event data (auto-generated)
└── README.md       // Project documentation
```

---

## How to Run

### Compile the Program

```
g++ main.cpp -o EventX
```

### Run the Executable

```
./EventX
```

---

## Program Workflow

1. Select user type (Organizer or Customer)
2. Log in or automatically create a new account
3. Display role-specific menu options
4. Perform selected operations such as listing events or booking tickets
5. Log out and exit the system

---

## Data Storage Format

### users.txt

```
username password isOrganizer
```

### events.txt

```
eventName date totalTickets availableTickets
```

---

## Limitations

* Event names must be single words without spaces
* Customer ticket bookings are not stored permanently
* Passwords are stored in plain text for educational purposes

---

## Future Enhancements

* Secure password storage using hashing
* Persistent customer booking history
* Event cancellation and modification features
* Support for booking multiple tickets
* Date validation and event sorting
* Administrative dashboard

---

## Learning Outcomes

* Practical implementation of Object-Oriented Programming in C++
* Hands-on experience with file handling for persistent storage
* Design of a role-based application
* Development of a structured, menu-driven console program

---

## Author

EventX was developed as an academic project to demonstrate the application of C++ Object-Oriented Programming and file handling concepts.
