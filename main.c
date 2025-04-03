#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Structures.h"

#define DEFAULT_CSV_FILE "students.csv"

int main(int argc, char** argv) {

    const char* csv_filename;
    if (argc < 2) {
        printf("\nNo CSV filename in arguments. Using default: %s", DEFAULT_CSV_FILE);
        csv_filename = DEFAULT_CSV_FILE;
    } else {
        csv_filename = argv[1];
    }
    StudNode* main_stud_list = init_stud_list(csv_filename);
    printf("\n\n\nWelcome to the Archaic Student Grade Management System!\n");
    printf("Buckle up and hop into our time machine where you get to track student progress like its 1987!");

    while(1) {

        printf("\n\n\n===========Archaic Student Grade Management System (ASGMS)==========\n");
        printf("1. Sort Student records alphabetically\n");
        printf("2. Sort Student records by ID\n");
        printf("3. Sort Student records by GPA\n");
        printf("4. View list of all student records\n");
        printf("5. Find Student record\n");
        printf("6. Add New Student record\n");
        printf("7. Delete a Student record\n");
        printf("8. Add or Delete course from Student record\n");
        printf("9. Exit\n");
        printf("\nEnter your choice: ");
        
        int choice = 0;
        char buffer[10];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            sscanf(buffer, "%d", &choice);
        }

        switch (choice) {
            case 1:
                main_stud_list = stud_merge_sort(main_stud_list, compare_by_name);
                printf("\nList is sorted alphabetically!\n");
                break;
            case 2:
                main_stud_list = stud_merge_sort(main_stud_list, compare_by_id);
                printf("\nList is sorted by ID!\n");
                break;
            case 3:
                main_stud_list = stud_merge_sort(main_stud_list, compare_by_gpa);
                printf("\nList is sorted by GPA!\n");
                break;
            case 4:
                printf("\n\n%-20s : %-5s : %-4s\n", "Name", "ID", "GPA");
                printf("-------------------------------------\n");
                print_stud_list_brief(main_stud_list);
                break;
            // You cannot declare variables in a case without {}, or the compiler throws an error.
            case 5:
                find_stud(main_stud_list);
                break;
            case 6:
                main_stud_list = add_new_stud(main_stud_list);
                break;
            case 7:
                main_stud_list = delete_stud(main_stud_list);
                break;
            case 8:
                main_stud_list = modify_stud_record(main_stud_list);
                break;
            case 9:
                write_students_to_csv(csv_filename, main_stud_list);
                clear_stud_list(main_stud_list);
                return EXIT_SUCCESS;
            default:
                printf("\nInvalid input. Please try again.\n");
        }
    }
}