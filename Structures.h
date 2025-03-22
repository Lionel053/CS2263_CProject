#ifndef STRUCTURES_H
#define STRUCTURES_H

//Structs def at the top. I guess order matters, I was getting errors because declarations were too late.
typedef struct {

    char* title;
    int grade;

}Course;

typedef struct crselistnode {

    struct crselistnode* next;
    Course* course;

}CourseNode;

typedef struct {

    char* name;
    int id;
    CourseNode* courses;
    int numGrades; //corresponds to num of courses
    float gpa;

}Student;

typedef struct studlistnode {

    struct studlistnode* next;
    Student* stud;

}StudNode;

//Regular procedures associated with Course
Course* construct_course(const char* title, int grade);
void free_course(Course* course);
void print_course(Course* course);

//Helper methods to calculate GPA after reading in Array of courses
float* getGradePoints(CourseNode* list, int numGrades);
float convertToGradePoint(int grade);
float calculateGPA(float gpa[], int numGrades);

//Regular procedures associated with CourseNode - ie LinkedList
CourseNode* insert_course(CourseNode* list, Course* course);
void print_course_list(CourseNode* list);
void clear_course_list(CourseNode* list);


//Regular procedures associated with Student
Student* construct_stud(const char* name, CourseNode* course_list, int id, float gpa, int numGrades);
void free_stud(Student* stud);
void print_stud(Student* stud);

// File operations for reading and writing students from CSV
StudNode* read_students_from_csv(const char* filename, int* student_count);
void write_students_to_csv(const char* filename, StudNode* stud_list, int student_count);

//Operations associated with StudNode - ie LinkedList
//static StudNode* construct_list(Student* stud);//should only be used by insert_stud. That's why it's static.
StudNode* remove_stud(StudNode* list, Student* stud);//TODO
StudNode* insert_stud(StudNode* list, Student* stud);//constructs a new node and inserts into list
Student* find_stud_by_name(StudNode* list, char name);//TODO
Student* find_stud_by_id(StudNode* list, int id);//TODO
void sort_list_by_name(StudNode* list);//TODO
void sort_list_by_id(StudNode* list);//TODO
void sort_list_by_gpa(StudNode* list);//TODO
void print_stud_list(StudNode* list);
void clear_stud_list(StudNode* list);


#endif