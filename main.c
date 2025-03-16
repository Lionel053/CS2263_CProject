#include<stdlib.h>
#include<stdio.h>
#include "Student.h"

int main(int argc, char **argv) {

    char* filename = "student_info.csv";
    Student** list = init_student(filename);
    /*
    if (list == NULL) {
        printf("Failed connnecting to database, contact your IT admin for absolutely no help\n");
        return EXIT_FAILURE;
    }
    */
    int choice;

    while (1) {

        printf("Welcome to the Grade Management System!\n");
        printf("Please choose from one of the following options:\n");
        printf("1: Add a new student\n");
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
                create_student(list);
                break;
            case 2:
                view_student(list);
                break;
            case 3:
                edit_student(list);
                break;
            case 4:
                delete_student(list);
                break;
            case 5:
                view_list(list);
                break;
            case 6:
                return EXIT_SUCCESS;
            default:
                printf("Invalid entry, try another selection\n");
                continue;
        }
            
    }

}