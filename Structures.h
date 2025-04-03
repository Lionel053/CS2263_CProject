#ifndef STRUCTURES_H
#define STRUCTURES_H

//Structs def at the top. I guess order matters, I was getting errors because declarations were too late.
typedef struct {

    char* title;
    int grade;

}Course;

typedef struct crselistnode {

    struct crselistnode* next;
    struct crselistnode* prev;
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
    struct studlistnode* prev;
    Student* stud;

}StudNode;

typedef int (*Comparator)(Student* a, Student* b);

//Regular procedures associated with Course
Course* construct_course(const char* title, int grade);
void free_course(Course* course);
void print_course(Course* course);
Course* copy_course(Course* course);//Returns deep copy

//Helper methods to calculate GPA after reading in Array of courses
float* getGradePoints(CourseNode* list, int numGrades);
float convertToGradePoint(int grade);
float calculateGPA(float gpa[], int numGrades);

//Regular procedures associated with CourseNode - ie LinkedList
CourseNode* insert_course(CourseNode* list, Course* course);
void print_course_list(CourseNode* list);
CourseNode* delete_course(CourseNode* list, char* title);
void clear_course_list(CourseNode* list);
CourseNode* copy_course_list(CourseNode* list);//Returns deep copy of student course list

//Regular procedures associated with Student
Student* construct_stud(const char* name, CourseNode* course_list, int id, float gpa, int numGrades);
void free_stud(Student* stud);
void print_stud(Student* stud);
void print_stud_brief(Student* stud);//prints student name and id only
Student* copy_stud(Student* stud);//returns a deep copy of the given student

// File operations for reading and writing students from CSV
StudNode* read_students_from_csv(const char* filename, int* student_count);//creates master list of students at beginning
void write_students_to_csv(const char* filename, StudNode* stud_list);//writes master list of students at end of program

//Operations associated with StudNode - ie LinkedList
StudNode* insert_stud(StudNode* list, Student* stud);//constructs a new node and inserts into list given an existing student
void print_stud_list(StudNode* list);
void print_stud_list_brief(StudNode* list);//Prints abbreviated list, names and ids only
void clear_stud_list(StudNode* list);
StudNode* copy_stud_list(StudNode* list);//Returns deep copy of student list

//Sublisting methods, returns subset of the master list based on criteria (deep copy, must be freed after use)
StudNode* find_stud_by_name(StudNode* list, char* name);
StudNode* find_stud_by_id(StudNode* list, int id);//Should only return a list containing one node since the id is unique (can be used to detect duplicates)

//Sorting
int compare_by_name(Student* a, Student* b);
int compare_by_id(Student* a, Student* b);
int compare_by_gpa(Student* a, Student* b);
StudNode* stud_merge_sort(StudNode* list, Comparator cmp);

//High level routines for use cases
StudNode* init_stud_list(const char* file);
void find_stud(StudNode* list);
StudNode* add_new_stud(StudNode* list);
int get_new_id(StudNode* list);
CourseNode* get_course_input();
StudNode* delete_stud(StudNode* list);
StudNode* remove_stud_by_id(StudNode* list, int id);
int get_list_count(StudNode* list);
int get_course_count(CourseNode* list);
StudNode* modify_stud_record(StudNode* list);
CourseNode* delete_course_record(CourseNode* course_list);
CourseNode* add_course_record(CourseNode* course_list);
CourseNode* remove_course_by_name(CourseNode* head, const char* course_name);


#endif