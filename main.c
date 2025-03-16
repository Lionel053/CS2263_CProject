#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv) {

    while (1) {

        printf("Welcome to the Grade Management System!\n");
        printf("Please choose from one of the following options:\n");
        printf("1: Add a new Student\n");
        printf("2: View info for an existing Student\n");
        printf("3: Exit\n");

        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("Invalid entry, try another selection");
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                create_student_routine();
                break;
            case 2:
                view_student_routine();
                break;
            case 3:
                return EXIT_SUCCESS;
            default:
                printf("Invalid entry, try another selection");
                continue;
        }
            
    }

}