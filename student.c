#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "student.h"

static int nextID = 1;

void load_file(char *filename, Student **students, int *studentCount) {

}

void save_file(char *filename, Student **students, int *studentCount) {
  
}

void add_student(Student **students, int *studentCount) {
    Student *s = (Student *)malloc(sizeof(Student));
    if (!s) {
       printf("Memory allocation failed for Student.\n");
       return;
    }
    
    // Assign student ID
    s->id = nextID++;
    
    // Scan, allocate, and copy the Student's name
    char name[100];
    printf("\nName: ");
    scanf("%s", name);
    
    s->name = (char *)malloc(100 * sizeof(char));
    if (!s->name) {
        printf("Memory allocation failed for Student name.\n");
        return;
    }
    strcpy(s->name, name);
    
    // Allocate and copy grades
    s->grades = malloc(MAX_GRADES * sizeof(float));
    if (!s->grades) {
        printf("Memory allocation failed for Student grades.\n");
        return;
    }
    
    s->gpa = 0.0;
    
    // Add Student to array and increment count
    students[*studentCount] = s;
    (*studentCount)++;
    printf("Student %s successfully added.\n\n", name);
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
        printf("GPA: %.2f\n\n", s->gpa);
    }
}