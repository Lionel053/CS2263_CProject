#include<stdlib.h>
#include<stdio.h>
#include "Student.h"

Student** init_student_data(char** filename) {
    //TODO
    return NULL;
}

void create_student_routine(Student** list) {
    //TODO
}

void view_student_routine(Student** list) {
    //TODO
    int choice;
    while (1) {
        printf("Choose one of the following options:\n");
        printf("1: Search by name\n");
        printf("2: Search by ID\n");
        printf("3: Go back\n");

        if (scanf("%d", &choice) != 1) {
            perror("Invalid choice, try again");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                search_by_name(list);
                break;
            case 2:
                search_by_id(list);
                break;
            case 3:
                return;
            default:
                perror("Invalid choice, try again :(\n");
                continue;
        }
        break; //allow for return to caller
    }
    
}

void seach_by_name(Student** list) {

    char choice[MAX_CHARS_NAME];
    while(1) {
        printf("Enter the name of student you are looking for: \n");
        if (fgets(choice, MAX_CHARS_NAME, stdin) != NULL) {
            size_t charCount = strlen(choice);
            if (charCount = MAX_CHARS_NAME - 1 && choice[charCount - 1] != '\n') {
                perror("Name is way too long to be real\n");
                //need to handle flushing the input
                continue;
            } else {
                if (charCount > 0 && choice[charCount - 1] == '\n') {
                    choice[charCount - 1] = '\0';
                }
                //input must be valid if if statement was not triggered
            }
        } else {
            perror("Error reading name\n");
            //need to handle flushing the input
            continue;
        }
        //TODO once we have the name, we need to go to the next activity ie what do we want to view about this student
        break; // used only to allow for return to caller - testing purposes only for now - don't forget to remove
    }

    
}

void delete_student_routine(Student** list) {
    //TODO
    
}