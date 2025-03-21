#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {

    char* title;
    int grade;

}Course;

Course* construct_course(const char* title, int grade);
void free_course(Course* course);
void print_course(Course* course);

typedef struct {

    char* name;
    int id;
    Course** courses;
    int numGrades; //corresponds to num of courses
    float gpa;

}Student;

//Helper methods to calculate GPA after reading in Array of courses
float* getGradePoints(Course** courses, int numGrades);
float convertToGradePoint(int grade);
float calculateGPA(float gpa[], int numGrades);

//Regular procedures associated with Student
Student* construct_stud(const char* name, Course** courses, int id, float gpa, int numGrades);
void free_stud(Student* stud);
void print_stud(Student* stud);

// File operations for reading and writing students from CSV
Student** read_students_from_csv(const char* filename, int* student_count);
void write_students_to_csv(const char* filename, Student** students, int student_count);


#endif