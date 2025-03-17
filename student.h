#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME 100
#define MAX_GRADES 5
#define MAX_STUDENTS 100

typedef struct {
    int id;
    char *name;
    float *grades;
    float gpa;
} Student;

// main functions
void load_file(char *filename, Student **students, int *studentCount);
void save_file(char *filename, Student **students, int *studentCount);
void add_student(Student **students, int *studentCount, Student *s);
Student *create_student(int id, char *name, float *grades);
void delete_student(Student **students);
void edit_student(Student **students);
void view_student(Student **students);
void view_list(Student **students, int studentCount);

#endif