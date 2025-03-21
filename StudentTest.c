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
 
    int student_count;

    Student** students = read_students_from_csv(csv_filename, &student_count);

    if (!students) {

        return EXIT_FAILURE;

    }
 
    printf("Successfully read %d students from %s\n", student_count, csv_filename);

    // Print student details for verification

    for (int i = 0; i < student_count; i++) {

        print_stud(students[i]);

    }
 
    // Write student data to output.csv

    write_students_to_csv("output.csv", students, student_count);

    printf("Student data written to output.csv\n");
 
    // Free allocated memory

    for (int i = 0; i < student_count; i++) {

        free_stud(students[i]);

    }

    free(students);
 
    return EXIT_SUCCESS;

}

 
