#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
 
    //We should be careful to initialize primitive types because it will point to a garbage value if we don't. 
    //In this case, since the read function does initialize it to zero, it's a non issue.
    //I only mention it because I made that mistake with the calculate gpa function and had a hell of time
    //trying to figure it out. 
    int student_count;


    Node* stud_list = read_students_from_csv(csv_filename, &student_count);

    if (!stud_list) {

        return EXIT_FAILURE;

    }
 
    printf("Successfully read %d students from %s\n", student_count, csv_filename);

    // Print student details for verification

    print_list(stud_list);
 
    // Write student data to output.csv

    write_students_to_csv("output.csv", stud_list, student_count);

    printf("Student data written to output.csv\n");
 
    // Free allocated memory

    clear_list(stud_list);

    return EXIT_SUCCESS;

}