#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Structures.h"

//////////////////////////Course related procedures////////////////////////////

Course* construct_course(const char* title, int grade) {

    Course* course = (Course*) malloc(sizeof(Course));
    if (course == NULL) {
        printf("Memory allocation failed bro\n");
        return NULL;
    }
    course -> title = (char*) malloc(strlen(title) + 1);
    if (course -> title == NULL) {
        printf("Memory allocation failed bro\n");
        free(course);
        return NULL;
    }
    strcpy(course -> title, title);
    course -> grade = grade;

    return course;

}

void free_course(Course* course) {

    if (course != NULL) {
        free(course -> title);
        free(course);
    }

}

void print_course(Course* course) {

    int grade = course -> grade;
    printf("%s\t| ", course -> title);
    for (int i = 0; i < grade; i += 10)
        printf("#");
    printf("\t(%d)\n", grade);

}

////////////////////////Helper to Student related procedures///////////////////
//If you use this function, don't forget to free float* when you're done with it!
float* getGradePoints(Course** courses, int numGrades) {

    float* gradePoints = malloc(sizeof(float) * numGrades);
    Course* current;

    for (int i = 0; i < numGrades; i++) {
        current = *courses;
        int grade = current -> grade;
        float gp = convertToGradePoint(grade);
        gradePoints[i] = gp;
        *courses++;
    }

    return gradePoints;
}

float convertToGradePoint(int grade) {
    if (grade < 50) {
        return 0.0;
    } else if (grade < 60) {
        return 1.0;
    } else if (grade < 65) {
        return 2.0;
    } else if (grade < 70) {
        return 2.3;
    } else if (grade < 75) {
        return 2.7;
    } else if (grade < 80) {
        return 3.0;
    } else if (grade < 85) {
        return 3.5;
    } else if (grade < 90) {
        return 3.7;
    } else if (grade < 95) {
        return 4.0;
    } else if (grade < 100) {
        return 4.3;
    } else {
        return 4.5;
    }
}

float calculateGPA(float gpa[], int numGrades) {

    float sum;
    for (int i = 0; i < numGrades; i++) {
        sum += gpa[i];
    }
    return sum/numGrades;

}

////////////////////////Student related procedures//////////////////////
//Memory for courses have already been allocated. The free_stud procedure will iterate and free the courses when called.
Student* construct_stud(const char* name, Course** courses, int id, float gpa, int numGrades) {

    Student* stud = (Student*) malloc(sizeof(Student));

    if (stud == NULL) {
        printf("Memory allocation failed bro\n");
        return NULL;
    }

    stud -> name = (char*) malloc(strlen(name) + 1);
    if (stud -> name == NULL) {
        printf("Memory allocation failed bro\n");
        free(stud);
        return NULL;
    }
    strcpy(stud -> name, name);
    stud -> id = id;
    stud -> gpa = gpa;
    stud -> numGrades = numGrades;

    stud -> courses = courses;

    return stud;

}

void free_stud(Student* stud) {

    if (stud != NULL) {
        Course** courses = stud -> courses;
        Course* current;
        for (int i = 0; i < stud -> numGrades; i++) {
            current = *courses;
            free_course(current);
            courses++;
        }
        free(stud -> courses);
        free(stud -> name);
        free(stud);
    }

}

void print_stud(Student* stud) {

    printf("Student name: %s\n", stud -> name);
    printf("Student ID: %d\n", stud -> id);
    Course** courses = stud -> courses;
    Course* current;
    for (int i = 0; i < stud -> numGrades; i++) {
        current = *courses;
        print_course(current);
        courses++;
    }
    printf("GPA: %.2f\n", stud -> gpa);
    printf("\n");

}



