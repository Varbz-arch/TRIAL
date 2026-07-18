// STUDENT MANAGEMENT SYSTEM 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNo;
    char name[50];
    int age;
    char course[50];
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;


// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
int checkDuplicateRoll(int roll);


// Check duplicate roll number
int checkDuplicateRoll(int roll) {

    for(int i = 0; i < studentCount; i++) {

        if(students[i].rollNo == roll)
            return 1;
    }

    return 0;
}


// Save students to file
void saveToFile() {

    FILE *fp = fopen("students.dat", "wb");

    if(fp == NULL) {
        printf("File error!\n");
        return;
    }


    fwrite(&studentCount, sizeof(int), 1, fp);

    fwrite(students, sizeof(struct Student),
           studentCount, fp);


    fclose(fp);
}


// Load students from file
void loadFromFile() {

    FILE *fp = fopen("students.dat", "rb");


    if(fp == NULL)
        return;


    fread(&studentCount, sizeof(int), 1, fp);

    fread(students, sizeof(struct Student),
          studentCount, fp);


    fclose(fp);
}



// Add Student
void addStudent() {


    if(studentCount >= MAX_STUDENTS) {

        printf("Database Full!\n");
        return;
    }


    struct Student s;


    printf("\nEnter Roll Number: ");
    scanf("%d",&s.rollNo);


    if(checkDuplicateRoll(s.rollNo)) {

        printf("Roll Number already exists!\n");
        return;
    }


    getchar();


    printf("Enter Name: ");
    fgets(s.name,50,stdin);

    s.name[strcspn(s.name,"\n")] = '\0';



    printf("Enter Age: ");
    scanf("%d",&s.age);


    getchar();


    printf("Enter Course: ");
    fgets(s.course,50,stdin);

    s.course[strcspn(s.course,"\n")] = '\0';



    students[studentCount++] = s;


    saveToFile();


    printf("\nStudent Added Successfully!\n");

}



// Display Students
void displayStudents() {


    if(studentCount == 0) {

        printf("\nNo Students Found!\n");
        return;
    }


    printf("\n------------------------------------------------------\n");

    printf("%-10s %-25s %-10s %-20s\n",
           "Roll",
           "Name",
           "Age",
           "Course");


    printf("------------------------------------------------------\n");


    for(int i=0;i<studentCount;i++) {


        printf("%-10d %-25s %-10d %-20s\n",
               students[i].rollNo,
               students[i].name,
               students[i].age,
               students[i].course);

    }


    printf("------------------------------------------------------\n");

}



// Search Student
void searchStudent() {


    int roll;


    printf("\nEnter Roll Number: ");
    scanf("%d",&roll);



    for(int i=0;i<studentCount;i++) {


        if(students[i].rollNo == roll) {


            printf("\nStudent Found\n");

            printf("Roll : %d\n",students[i].rollNo);
            printf("Name : %s\n",students[i].name);
            printf("Age  : %d\n",students[i].age);
            printf("Course : %s\n",students[i].course);


            return;
        }

    }


    printf("Student Not Found!\n");

}



// Update Student
void updateStudent() {


    int roll;


    printf("\nEnter Roll Number to Update: ");
    scanf("%d",&roll);


    for(int i=0;i<studentCount;i++) {


        if(students[i].rollNo == roll) {


            getchar();


            printf("Enter New Name: ");
            fgets(students[i].name,50,stdin);

            students[i].name[strcspn(students[i].name,"\n")] = '\0';



            printf("Enter New Age: ");
            scanf("%d",&students[i].age);


            getchar();


            printf("Enter New Course: ");
            fgets(students[i].course,50,stdin);

            students[i].course[strcspn(students[i].course,"\n")] = '\0';



            saveToFile();


            printf("Student Updated Successfully!\n");

            return;
        }

    }


    printf("Student Not Found!\n");

}



// Delete Student
void deleteStudent() {


    int roll;
    int found=0;


    printf("\nEnter Roll Number to Delete: ");
    scanf("%d",&roll);



    for(int i=0;i<studentCount;i++) {


        if(students[i].rollNo == roll) {


            found=1;


            for(int j=i;j<studentCount-1;j++) {

                students[j]=students[j+1];

            }


            studentCount--;


            saveToFile();


            printf("Student Deleted Successfully!\n");


            break;

        }

    }


    if(!found)
        printf("Student Not Found!\n");

}



// Main Function
int main() {


    int choice;


    loadFromFile();



    while(1) {


        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");


        printf("Enter Choice: ");
        scanf("%d",&choice);



        switch(choice) {


            case 1:
                addStudent();
                break;


            case 2:
                displayStudents();
                break;


            case 3:
                searchStudent();
                break;


            case 4:
                updateStudent();
                break;


            case 5:
                deleteStudent();
                break;


            case 6:
                printf("Exiting Program...\n");
                exit(0);


            default:
                printf("Invalid Choice!\n");

        }

    }


    return 0;
}