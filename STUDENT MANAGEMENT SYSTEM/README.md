# Student Management System in C

A console-based **Student Management System** developed using the **C programming language**. This project performs basic **CRUD (Create, Read, Update, Delete)** operations on student records and uses **file handling** to store data permanently.

---

## Features

- Add new student records
- Display all students
- Search student by roll number
- Update existing student details
- Delete student records
- Prevent duplicate roll numbers
- Automatically save records to a file
- Automatically load records when the program starts
- Support multi-word names and course names
- Formatted tabular display of student records

---

## Technologies Used

- C Programming
- Structures
- Arrays
- Functions
- File Handling
- String Handling

---

## Concepts Implemented

- Structures (`struct Student`)
- Arrays
- Functions
- File Handling (`fopen()`, `fread()`, `fwrite()`, `fclose()`)
- Searching and Updating Records
- Array Manipulation for Deletion
- Input Validation

---

## Project Structure

```
Student Management System/
│
├── Student_Management_Sys.c
├── README.md
└── students.dat (generated automatically)
```

---

## Student Record Format

| Field | Description |
|-------|-------------|
| Roll Number | Unique student ID |
| Name | Student name |
| Age | Student age |
| Course | Enrolled course |

---

## How to Run

### Clone the repository

```bash
git clone https://github.com/Varbz-arch/TRIAL.git
```

### Navigate to the project folder

```bash
cd "STUDENT MANAGEMENT SYSTEM"
```

### Compile the program

Using GCC:

```bash
gcc Student_Management_Sys.c -o StudentManagement
```

### Run the program

**Windows**

```bash
StudentManagement.exe
```

**Linux / macOS**

```bash
./StudentManagement
```

---

## Program Menu

```
========== STUDENT MANAGEMENT SYSTEM ==========

1. Add Student
2. Display Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit

===============================================
```
<img width="1336" height="653" alt="image" src="https://github.com/user-attachments/assets/d210b0cc-146f-4dba-8a23-7a5421038c62" />

<img width="672" height="575" alt="image" src="https://github.com/user-attachments/assets/ae54d2a8-0368-449c-aecd-9b40d7a41735" />

---

## File Handling

The program stores student records in a binary file named:

```
students.dat
```

- Records are automatically loaded when the application starts.
- Any changes (Add, Update, or Delete) are automatically saved to the file.

---

## Future Improvements

- Login authentication system
- Dynamic memory allocation
- Sorting students by name or roll number
- Search by student name
- Export records to CSV
- Database integration (MySQL)
- Graphical User Interface (GUI)

---

## Author

**Archisha Borah**  
B.Tech Computer Science Engineering

---

## License

This project is intended for educational and learning purposes.
