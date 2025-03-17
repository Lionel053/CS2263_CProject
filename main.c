#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int main() {
    int studentCount = 0;
    Student **students = malloc(MAX_STUDENTS * sizeof(Student *));
    if (!students) {
        printf("Failed to allocate memory for students list.\n");
        return EXIT_FAILURE;
    }
    
    int choice;

    while (1) {

        printf("Welcome to the Grade Management System!\n");
        printf("Please choose from one of the following options:\n");
        printf("1: Create a new student\n");
        printf("2: View info for an existing Student\n");
        printf("3: Modify student data\n");
        printf("4: Delete existing student\n");
        printf("5: View complete list of students\n");
        printf("6: Exit\n");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid entry, try another selection\n");
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                add_student(students, &studentCount, create_student());
                break;
            case 2:
                view_student(students);
                break;
            case 3:
                edit_student(students);
                break;
            case 4:
                delete_student(students);
                break;
            case 5:
                view_list(students, studentCount);
                break;
            case 6:
                return EXIT_SUCCESS;
            default:
                printf("Invalid entry, try another selection\n");
                continue;
        }
            
    }

}