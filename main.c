#include<stdlib.h>
#include<stdio.h>
#include "Student.h"

int main(int argc, char **argv) {

    char** filename = "student_info.csv";
    Student** list = init_student_data(filename);
    if (list == NULL) {
        perror("Failed connnecting to database, contact your IT admin for absolutely no help\n");
        return EXIT_FAILURE;
    }

    int choice;

    while (1) {

        printf("Welcome to the Grade Management System!\n");
        printf("Please choose from one of the following options:\n");
        printf("1: Add a new Student\n");
        printf("2: View info for an existing Student\n");
        printf("3: Delete student data\n");
        printf("4: Exit\n");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid entry, try another selection");
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                create_student_routine(list);
                break;
            case 2:
                view_student_routine(list);
                break;
            case 3:
                delete_student_routine(list);
                break;
            case 4:
                return EXIT_SUCCESS;
            default:
                printf("Invalid entry, try another selection");
                continue;
        }
            
    }

}