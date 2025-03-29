#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Structures.h"

#define DEFAULT_CSV_FILE "students.csv"

int main(int argc, char** argv) {

    const char* csv_filename;
    if (argc < 2) {
        printf("No CSV file provided. Using default: %s\n", DEFAULT_CSV_FILE);
        csv_filename = DEFAULT_CSV_FILE;
    } else {
        csv_filename = argv[1];
    }
    StudNode* main_stud_list = init_stud_list(csv_filename);
    int choice = 0;
    printf("Welcome to the Archaic Student Grade Management System!\n");
    printf("Buckle up and hop into our time machine where you get to track student progress like its 1987!\n\n\n");

    while(1) {

        printf("\n===========Archaic Student Grade Management System (ASGMS)==========\n");
        printf("1. Sort Student records alphabetically\n");
        printf("2. Sort Student records by ID\n");
        printf("3. Sort Student records by GPA\n");
        printf("4. View list of all student records\n");
        printf("5. Find Student record\n");
        printf("6. Add New Student record\n");
        printf("7. Delete a Student record\n");
        printf("8. Add or Delete course from Student record\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        //Check for valid input before proceeding
        if (scanf("%d", &choice) != 1) {
            printf("Something went wrong!\n");
            clear_stud_list(main_stud_list);
            return EXIT_FAILURE;
        }

        switch (choice) {
            case 1:
                sort_by_stud_name(main_stud_list);
                printf("\nList is sorted alphabetically!\n");
                break;
            case 2:
                sort_by_stud_id(main_stud_list);
                printf("\nList is sorted by ID!\n");
                break;
            case 3:
                sort_by_stud_gpa(main_stud_list);
                printf("\nList is sorted by GPA!\n");
                break;
            case 4:
                printf("\n\tName : ID : GPA\n");
                print_stud_list_brief(main_stud_list);
                press_enter_to_continue();
                break;
            case 5:
                StudNode* sub_list = find_stud(main_stud_list);
                clear_stud_list(sub_list);
                break;
            case 6:
                main_stud_list = add_new_stud(main_stud_list);
                press_enter_to_continue();
                break;
            case 7:
                main_stud_list = delete_stud(main_stud_list);
                press_enter_to_continue();
                break;
            case 8:
                main_stud_list = modify_stud_record(main_stud_list);
                press_enter_to_continue();
                break;
            case 9:
                write_students_to_csv(DEFAULT_CSV_FILE, main_stud_list);
                clear_stud_list(main_stud_list);
                return EXIT_SUCCESS;
            default:
                printf("Nothing happened...try something else?\n");
        }

    }
}