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
float* getGradePoints(CourseNode* list, int numGrades) {

    float* gradePoints = malloc(sizeof(float) * numGrades);
    CourseNode* current = list;

    for (int i = 0; i < numGrades; i++) {
        int grade = current -> course -> grade;
        float gp = convertToGradePoint(grade);
        gradePoints[i] = gp;
        current = current -> next;
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

    float sum = 0.00;                       //Primitive types must be initialized - this is where I generated a bug by not initializing
    for (int i = 0; i < numGrades; i++) {
        sum += gpa[i];
    }
    return sum/numGrades;

}

////////////////////////Student related procedures//////////////////////
//Memory for courses have already been allocated. The free_stud procedure will iterate and free the courses when called.
Student* construct_stud(const char* name, CourseNode* course_list, int id, float gpa, int numGrades) {

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

    stud -> courses = course_list;

    return stud;

}

void free_stud(Student* stud) {

    if (stud != NULL) {
        CourseNode* current = stud -> courses;
        CourseNode* prev;
        while (current != NULL) {
            free_course(current -> course);
            prev = current;
            current = current -> next;
            free(prev);
        }
        free(stud -> name);
        free(stud);
    }

}

void print_stud(Student* stud) {

    printf("Student name: %s\n", stud -> name);
    printf("Student ID: %d\n", stud -> id);

    print_course_list(stud -> courses);

    printf("GPA: %.2f\n", stud -> gpa);
    printf("\n");

}

//////////////////////// CSV File Operations /////////////////////////////
StudNode* read_students_from_csv(const char* filename, int* student_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }
    
    *student_count = 0;

    StudNode* stud_list = NULL;//Must be set to NULL. This constructs an empty list.
    
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        char* name = strdup(token);//strdup allocates memory, must be freed
        token = strtok(NULL, ",");
        int id = atoi(token);

        //Course** courses = (Course**) malloc(sizeof(Course*) * 4);
        CourseNode* course_list = NULL;//Must be set to NULL. This constructs an empty list
        Course* course;
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ",");
            char* course_title = strdup(token);//allocate memory must be freed everytime
            token = strtok(NULL, ",");
            int grade = atoi(token);
            course = construct_course(course_title, grade);
            course_list = insert_course(course_list, course);
            free(course_title);//free course_title
        }

        float* grade_points = getGradePoints(course_list, 4);
        float gpa = calculateGPA(grade_points, 4);
        free(grade_points);
        Student* stud = construct_stud(name, course_list, id, gpa, 4);
        stud_list = insert_stud(stud_list, stud);
        free(name);//freed name
        (*student_count)++;
    }
    fclose(file);
    return stud_list;
}

void write_students_to_csv(const char* filename, StudNode* list, int student_count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s,%d,%.2f\n", list -> stud -> name, list -> stud -> id, list -> stud -> gpa);
    }
    fclose(file);
}

///////////////////////////////Course Node Linked List Operations///////////////////////////
static CourseNode* construct_course_node(Course* course) {

    CourseNode* this = malloc(sizeof(CourseNode));
    this -> course = course;
    return this;

}

CourseNode* insert_course(CourseNode* list, Course* course) {

    CourseNode* this = construct_course_node(course);
    this -> next = list;
    return this;

}

void print_course_list(CourseNode* list) {

    CourseNode* runner = list;
    while (runner != NULL) {
        print_course(runner -> course);
        runner = runner -> next;
    }

}

void clear_course_list(CourseNode* list) {

    CourseNode* runner = list;
    CourseNode* prev;
    while (runner != NULL) {
        free_course(runner -> course);
        prev = runner;
        runner = runner -> next;
        free(prev);
    }

}

///////////////////////////////Student Linked List Operations//////////////////////////////

static StudNode* construct_stud_node(Student* stud) {

    StudNode* this = malloc(sizeof(StudNode));
    this -> stud = stud;
    return this;
    
}

void clear_stud_list(StudNode* list) {

    StudNode* runner = list;
    StudNode* prev;
    while (runner != NULL) {
        free_stud(runner -> stud);
        prev = runner;
        runner = runner -> next;
        free(prev);
    }

}

//For first entry, list must be set to NULL before inserting first entry - see StudentTest
StudNode* insert_stud(StudNode* list, Student* stud) {

    StudNode* this = construct_stud_node(stud);
    this -> next = list;
    
    return this;

}

StudNode* remove_stud(StudNode* list, Student* stud) {
    //TODO
    return NULL;
}

void print_stud_list(StudNode* list) {

    StudNode* runner = list;
    while (runner != NULL) {
        print_stud(runner -> stud);
        runner = runner -> next;
    }
    
}