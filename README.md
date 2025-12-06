Student Result Management System
 Project — Coding Skills (C Programming)

This project is developed as part of the Student Result Management System assignment where basic code was provided by faculty, and we were required to extend it with new features and upload the final project to GitHub along with a project report.

📖 Project Overview

The Student Result Management System is a C-language project that allows admin/teacher users to manage student academic records using secure login and file handling.

This program supports:

User authentication

Adding student records

Displaying all student data

Searching and updating student records

Deleting records (admin only)

Displaying the Topper (NEW FEATURE Added by me)

The system stores all data in text files for easy management and testing.

⭐ Features of the System
✔ Login System

Username, password, and role stored in credentials.txt

Supports multiple roles (Admin, Teacher)

Admin has full access including delete

✔ Student Management

Add new student

Display all students

Search student by roll number

Update student details

Delete student (admin only)

✔ ✨ New Feature Added: Display Topper

Shows the student with the highest marks in the entire database.

This was the feature added as part of the assignment requirement to improve the given base code.

📂 Project Structure
student-result-management-system/
│
├── main.c                # Main source code
├── students.txt          # Student records database
├── credentials.txt       # User login credentials
└── README.md             # Project documentation

🛠 How to Run the Program
1. Compile

Use GCC or any C compiler:

gcc main.c -o student

2. Run
./student

📄 File Details
students.txt

Stores student information:

roll_no name marks


Example:

101 Riya 89.5
102 Aarav 76
103 Tanvi 92

credentials.txt

Stores login data:

username password role


Example:

admin admin123 admin
teacher t123 teacher

📊 Sample Output
===== LOGIN =====
Username: admin
Password: *****
Login Successful!

===== MAIN MENU =====
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Display Topper
7. Logout

 Roles and Permissions
Role	Add	Display	Search	Update	Delete	Topper

 G.Sai Pravachana
Coding Skills – Project Submission
Student Result Management System

📜 License

This project is intended for academic use only.
