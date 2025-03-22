#ifndef STRUCTURES_H
#define STRUCTURES_H
//Structs def at the top. I guess order matters, I was getting errors because declarations were too late.
typedef struct {

    char* title;
    int grade;

}Course;

typedef struct {

    char* name;
    int id;
    Course** courses;
    int numGrades; //corresponds to num of courses
    float gpa;

}Student;

typedef struct listnode {

    struct listnode* next;
    Student* stud;

} Node;

//Regular procedures associated with Course
Course* construct_course(const char* title, int grade);
void free_course(Course* course);
void print_course(Course* course);

//Helper methods to calculate GPA after reading in Array of courses
float* getGradePoints(Course** courses, int numGrades);
float convertToGradePoint(int grade);
float calculateGPA(float gpa[], int numGrades);

//Regular procedures associated with Student
Student* construct_stud(const char* name, Course** courses, int id, float gpa, int numGrades);
void free_stud(Student* stud);
void print_stud(Student* stud);

// File operations for reading and writing students from CSV
Node* read_students_from_csv(const char* filename, int* student_count);
void write_students_to_csv(const char* filename, Node* stud_list, int student_count);

//Operations associated with Node - ie LinkedList
static Node* construct_list(Student* stud);//should only be used by insert_stud. That's why it's static.
Node* remove_stud(Node* list, Student* stud);
Node* insert_stud(Node* list, Student* stud);//constructs a new node and inserts into list
Student* find_stud_by_name(Node* list, char name);
Student* find_stud_by_id(Node* list, int id);
void sort_list_by_name(Node* list);
void sort_list_by_id(Node* list);
void sort_list_by_gpa(Node* list);
void print_list(Node* list);
void clear_list(Node* list);


#endif