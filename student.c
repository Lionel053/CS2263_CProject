#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

void load_file(char *filename, Student **students, int *studentCount) {

}

void save_file(char *filename, Student **students, int *studentCount) {
  
}

Student *create_student(int id, char *name, float *grades) {
    Student *s = (Student *)malloc(sizeof(Student));
    if (!s) {
       printf("Memory allocation failed for Student.\n");
       return NULL;
    }
    
    // Assign student ID
    s->id = id;
    
    s->name = (char *)malloc(100 * sizeof(char));
    if (!s->name) {
        printf("Memory allocation failed for Student name.\n");
        return NULL;
    }
    strcpy(s->name, name);
    
    // Allocate and copy grades. Needs CSV import implementation. TODO.
    s->grades = malloc(MAX_GRADES * sizeof(float));
    if (!s->grades) {
        printf("Memory allocation failed for Student grades.\n");
        return NULL;
    }
    memcpy(s->grades, grades, MAX_GRADES * sizeof(float));

    printf("Student %s created.\n\n", s->name);
    return s;
}

void add_student(Student **students, int *studentCount, Student *s){
  if (*studentCount >= MAX_STUDENTS) {
    printf("Too many students!\n");
    return;
  }
  
  if (!s) {
    printf("No student found.\n");
    return;
  }
  
  students[*studentCount] = s;
  (*studentCount)++;
  
  printf("Student %s added to list.\n", s->name);
}

void view_student(Student **students) {
    //TODO
    printf("This is the view student routine box\n");
}

void edit_student(Student **students) {
    //TODO
    printf("This is the edit student routine box\n");
}

void delete_student(Student **students) {
    //TODO
    printf("This is the delete student routine box\n");
}

void view_list(Student **students, int studentCount) {
  printf("\nStudent List:\n\n");
    for (int i = 0; i < studentCount; i++) {
        Student *s = students[i];
        printf("ID: %d\n", s->id);
        printf("Name: %s\n", s->name);
        for (int j = 0; j < MAX_GRADES; j++) {
            printf("%.2f ", s->grades[j]);
        }
        printf("\nGPA: %.2f\n\n", s->gpa);
    }
}