# University Result Management System

A console-based **University Result Management System** developed in C as a first-year Project Based Learning (PBL) project.

The system is designed to manage student academic records, calculate CGPA, and generate individual report cards while providing restricted access for administrators and students.

## Features

* Administrator and student login
* Add student records
* Delete student records
* View student profiles
* Binary search for student records
* Automatic grade and grade-point calculation
* Automatic CGPA calculation based on subject credits
* Generate individual student report cards
* Persistent storage using binary files
* Dynamic memory allocation using `malloc()` and `realloc()`
* Sorted student records based on Student ID

## Subjects

The system currently manages results for seven subjects:

| Subject                    | Credits |
| -------------------------- | ------: |
| Computer Science           |       4 |
| Mathematics                |       4 |
| Physics                    |       3 |
| Chemistry                  |       3 |
| Professional Communication |       2 |
| Electrical                 |       3 |
| Electronics                |       3 |

## Grade System

|    Marks | Grade Point | Grade |
| -------: | ----------: | :---: |
|   90–100 |          10 |   O   |
|    80–89 |           9 |   A   |
|    70–79 |           8 |   B   |
|    60–69 |           7 |   C   |
|    50–59 |           6 |   D   |
|    40–49 |           5 |   E   |
| Below 40 |           0 |   F   |

CGPA is calculated using the weighted average of grade points according to the credits of each subject.

## How It Works

When the program starts, it checks for an existing database file. If records are present, they are loaded into dynamically allocated memory using binary file operations.

Student records are maintained in sorted order according to Student ID. This allows the program to use binary search when looking for a particular student.

Administrators can add and delete student records and view student profiles. Students can log in using their credentials to view their profile and generate their report card.

Before the program terminates, the current records are written back to the database file so that they can be retrieved the next time the program is run.

## File Structure

```text
University-Result-Management-System/
│
├── main.c
├── README.md
├── database.dat
└── <StudentID>_ReportCard.txt
```

`database.dat` is created by the program and stores the student records.

Individual report cards are generated as text files using the student's ID, for example:

```text
101_ReportCard.txt
```

## Concepts Used

This project uses fundamental C programming concepts, including:

* Structures
* Arrays
* Pointers, Double pointers
* Functions
* Dynamic memory allocation
* `malloc()` and `realloc()`
* File handling
* `fread()` and `fwrite()`
* Binary search
* Sorted insertion
* String manipulation
* Menu-driven programming

## Sample Report Card

The program generates a formatted report card containing subject-wise marks, credits, maximum marks, grades, grade points, CGPA, and result status.

```text
=========== REPORT CARD ===========
Student ID   : 101
Student Name : Example Student
-----------------------------------

SUBJECT                     CREDITS    MARKS      MAX MARKS    GRADE      GRADE POINT
---------------------------------------------------------------------------------------
Computer Science            4          92         100          O          10          
Mathematics                 4          85         100          A+         9           
Physics                     3          78         100          A          8           
Chemistry                   3          85         100          A+         9           
Professional Communication  2          80         100          A+         9           
Electrical                  3          86         100          A+         9           
Electronics                 3          98         100          O          10    
---------------------------------------------------------------------------------------
Result : Pass
CGPA   : 9.18
===================================
```

## Project Scope

This project was developed as a first-year college Project Based Learning project with the goal of applying fundamental C programming concepts to a practical problem.

It is a standalone, console-based application and does not use any network connection, external database or user authentication.

## Future Improvements

Possible improvements include:

* Editing existing student records
* Improved input validation
* Password encryption
* Database integration
* Graphical User Interface
* More detailed result analytics

## Author

Developed as a first-year **Project Based Learning (PBL)** project using C.
