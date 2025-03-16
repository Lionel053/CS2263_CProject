#ifndef STUDENT_H
#define STUDENT_H
#define ID_LENGTH 8

typedef struct Student {
//TODO
}Student;

//TODO Student specific routines as specified in the UML diagram


//main routines
Student** init_student(char* filename);
void create_student(Student** list);
void view_student(Student** list);
void delete_student(Student** list);
void edit_student(Student** list);
void view_list(Student** list);


#endif

