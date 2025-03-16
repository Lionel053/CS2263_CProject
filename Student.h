#ifndef STUDENT_H
#define STUDENT_H
#define MAX_CHARS_NAME 50

typedef struct Student {

}Student;

//TODO Student specific routines as specified in the UML diagram

//main routines
Student** init_student_data(char** filename);
void create_student_routine(Student** list);
void view_student_routine(Student** list);
void delete_student_routine(Student** list);

#endif

