#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[10];
char currentUser[50];


// Function declarations
int loginSystem();
void mainMenu();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void displayTopper();


// MAIN FUNCTION
int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}


// LOGIN SYSTEM
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];

    printf("===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            printf("\nLogin Successful! Welcome %s (%s)\n\n", currentUser, currentRole);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


// MAIN MENU
void mainMenu() {
    int choice;

    while (1) {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");

        if (strcmp(currentRole, "admin") == 0)
            printf("5. Delete Student\n");

        printf("6. Display Topper (New Feature)\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: addStudent(); break;
        case 2: displayStudents(); break;
        case 3: searchStudent(); break;
        case 4: updateStudent(); break;

        case 5:
            if (strcmp(currentRole, "admin") == 0)
                deleteStudent();
            else
                printf("\nOnly admin can delete records!\n");
            break;

        case 6: displayTopper(); break;
        case 7: exit(0);

        default: printf("Invalid choice!\n");
        }
    }
}


// ADD STUDENT
void addStudent() {
    struct student st;

    printf("\nEnter Roll No: ");
    scanf("%d", &st.roll);

    printf("Enter Name: ");
    scanf("%s", st.name);

    printf("Enter Marks: ");
    scanf("%f", &st.marks);

    FILE *fp = fopen(STUDENT_FILE, "a");
    fprintf(fp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student added successfully!\n");
}


// DISPLAY ALL STUDENTS
void displayStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct student st;

    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    printf("\n===== STUDENT LIST =====\n");
    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
}


// SEARCH STUDENT
void searchStudent() {
    int roll;
    struct student st;
    int found = 0;

    printf("\nEnter roll to search: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll == roll) {
            printf("Record Found: Roll: %d | Name: %s | Marks: %.2f\n",
                   st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Record not found!\n");
}


// UPDATE STUDENT
void updateStudent() {
    int roll, found = 0;
    struct student st;

    printf("\nEnter roll to update: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll == roll) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", st.name);
            printf("Enter new marks: ");
            scanf("%f", &st.marks);
        }
        fprintf(temp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student updated successfully!\n");
    else
        printf("Record not found!\n");
}


// DELETE STUDENT
void deleteStudent() {
    int roll, found = 0;
    struct student st;

    printf("\nEnter roll to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll != roll) {
            fprintf(temp, "%d %s %.2f\n", st.roll, st.name, st.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found!\n");
}


// DISPLAY TOPPER (NEW FEATURE)
void displayTopper() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    struct student st, topper;
    int first = 1;

    if (!fp) {
        printf("No student records found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (first) {
            topper = st;
            first = 0;
        }
        if (st.marks > topper.marks) {
            topper = st;
        }
    }

    fclose(fp);

    printf("\n===== TOPPER =====\n");
    printf("Roll: %d | Name: %s | Marks: %.2f\n",
           topper.roll, topper.name, topper.marks);
}
