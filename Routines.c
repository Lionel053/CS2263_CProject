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

Course* copy_course(Course* course) {

    if (course == NULL) {
        return NULL;
    } else {
        Course* new_course = construct_course(course -> title, course -> grade);
        return new_course;
    }

}

void free_course(Course* course) {

    if (course != NULL) {
        free(course -> title);
        free(course);
    }

}

void print_course(Course* course) {

    int grade = course -> grade;
    char bar[11];
    for (int i = 0; i < 10; i++)
        if (i < grade / 10)
            bar[i] = '#';
        else
            bar[i] = ' ';
    printf("%-10s| %s (%d)\n", course->title, bar, grade);

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
    if (grade >= 90) {
        return 4.3;
    } else if (grade >= 85) {
        return 4.0;
    } else if (grade >= 80) {
        return 3.7;
    } else if (grade >= 75) {
        return 3.3;
    } else if (grade >= 70) {
        return 3.0;
    } else if (grade >= 65) {
        return 2.7;
    } else if (grade >= 60) {
        return 2.3;
    } else if (grade >= 55) {
        return 2.0;
    } else if (grade >= 50) {
        return 1.0;
    } else {
        return 0.0;
    }
}

float calculateGPA(float gpa[], int numGrades) {

    float sum = 0.00;                       //Primitive types must be initialized - this is where I generated a bug by not initializing
    for (int i = 0; i < numGrades; i++) {
        sum += gpa[i];
    }
    return sum/numGrades;

}

float get_GPA(CourseNode* list) {

    int numGrades = get_course_count(list);
    if (numGrades == 0) {
        return 0.00;
    }
    float* grade_points = getGradePoints(list, numGrades);
    float gpa = calculateGPA(grade_points, numGrades);
    free(grade_points);
    return gpa;

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

Student* copy_stud(Student* stud) {

    if (stud == NULL) {
        return NULL;
    } else {
        CourseNode* new_list = copy_course_list(stud -> courses);
        Student* new_stud = construct_stud(stud -> name, new_list, stud -> id, stud -> gpa, stud -> numGrades);
        return new_stud;
    }

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

    printf("\n\n%-20s : %-5s : %-4s\n", "Name", "ID", "GPA");
    printf("-------------------------------------\n");
    print_stud_brief(stud);
    printf("\n");
    
    print_course_list(stud -> courses);

    printf("\n");

}

void print_stud_brief(Student* stud) {

    if (stud == NULL) {
        return;
    }
    if (stud->gpa >= 3.7) {
        printf("%-20s : %-5d : \x1b[32m%-4.2f\x1b[0m\n", stud -> name, stud -> id, stud -> gpa);
    }
    else if (stud->gpa <= 1.0) {
        printf("%-20s : %-5d : \x1b[31m%-4.2f\x1b[0m\n", stud -> name, stud -> id, stud -> gpa);
    }
    else if (stud->gpa < 2.0) {
        printf("%-20s : %-5d : \x1b[33m%-4.2f\x1b[0m\n", stud -> name, stud -> id, stud -> gpa);
    }
    else {
        printf("%-20s : %-5d : %-4.2f\n", stud -> name, stud -> id, stud -> gpa);
    }
    
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
        line[strcspn(line, "\n")] = '\0';
        char* token = strtok(line, ",");
        char* name = strdup(token);//strdup allocates memory, must be freed
        token = strtok(NULL, ",");
        int id = atoi(token);

        CourseNode* course_list = NULL;//Must be set to NULL. This constructs an empty list
        Course* course;
        while (1) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                break;
            }
            char* course_title = strdup(token);//allocate memory must be freed everytime
            token = strtok(NULL, ",");
            int grade = atoi(token);
            course = construct_course(course_title, grade);
            course_list = insert_course(course_list, course);
            free(course_title);//free course_title
        }
        int numGrades = get_course_count(course_list);
        float gpa = get_GPA(course_list);
        Student* stud = construct_stud(name, course_list, id, gpa, numGrades);
        stud_list = insert_stud(stud_list, stud);
        free(name);//freed name
        (*student_count)++;
    }
    fclose(file);
    return stud_list;
}

void write_students_to_csv(const char* filename, StudNode* list) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing: %s\n", filename);
        return;
    }
    CourseNode* courses;
    while (list != NULL) {
        fprintf(file, "%s,%d,", list -> stud -> name, list -> stud -> id);
        courses = list -> stud -> courses;
        while (courses != NULL) {
            fprintf(file, "%s,%d,", courses -> course -> title, courses -> course -> grade);
            courses = courses -> next;
        }
        fprintf(file, "\n");
        list = list -> next;
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
    if (this -> next != NULL) {
        this -> next -> prev = this;
    }
    this -> prev = NULL;
    return this;

}

//Deep copy
CourseNode* copy_course_list(CourseNode* courses) {

    if (courses == NULL) {
        return NULL;
    } else {
        CourseNode* new_list = NULL;
        while (courses != NULL) {
            Course* new_copy = copy_course(courses -> course);
            new_list = insert_course(new_list, new_copy);
            courses = courses -> next;
        }
        return new_list;
    }

}

void print_course_list(CourseNode* list) {
    printf("%-10s: %-9s: %s\n", "Course", "Graph", "Percentage");
    printf("-------------------------------------\n");
    CourseNode* runner = list;
    while (runner != NULL) {
        print_course(runner -> course);
        runner = runner -> next;
    }

}

CourseNode* delete_course(CourseNode* list, char* title) {

    if (list == NULL) {
        return NULL;
    }
    CourseNode* o_g = list;
    while (list != NULL) {
        if (strcmp(list -> course -> title, title) == 0) {
            break;
        }
        list = list -> next;
    }
    if (list == NULL) {
        return o_g;
    } else {
        free_course(list -> course);
        if (list -> prev == NULL && list -> next == NULL) {
            free(list);
            return NULL;
        } else if (list -> prev == NULL && list -> next != NULL) {
            o_g = list -> next;
            free(list);
            return o_g;
        } else if (list -> prev != NULL && list -> next == NULL) {
            list -> prev -> next = NULL;
            free(list);
            return o_g;
        } else {
            list -> prev -> next = list -> next;
            list -> next -> prev = list -> prev;
            free(list);
            return o_g;
        }
    }
}

void clear_course_list(CourseNode* list) {

    CourseNode* runner = list;
    CourseNode* previous;
    while (runner != NULL) {
        free_course(runner -> course);
        previous = runner;
        runner = runner -> next;
        free(previous);
    }

}

///////////////////////////////Student Linked List Operations//////////////////////////////

static StudNode* construct_stud_node(Student* stud) {

    StudNode* this = malloc(sizeof(StudNode));
    this -> stud = stud;
    return this;
    
}

//For first entry, list must be set to NULL before inserting first entry - see StudentTest
StudNode* insert_stud(StudNode* list, Student* stud) {

    StudNode* this = construct_stud_node(stud);
    this -> next = list;
    if (this -> next != NULL) {
        this -> next -> prev = this;
    }
    this -> prev = NULL;
    return this;

}

//Deep copy
StudNode* copy_stud_list(StudNode* list) {

    if (list == NULL) {
        return NULL;
    } else {
        StudNode* new_stud_list = NULL;
        while (list != NULL) {
            Student* new_stud = copy_stud(list -> stud);
            new_stud_list = insert_stud(new_stud_list, new_stud);
            list = list -> next;
        }
        return new_stud_list;
    }

}

void print_stud_list(StudNode* list) {
    if (list == NULL) {
        printf("\nEmpty list!\n");
        return;
    }
    StudNode* runner = list;
    while (runner != NULL) {
        print_stud(runner -> stud);
        runner = runner -> next;
    }
    
}

void print_stud_list_brief(StudNode* list) {
    if (list == NULL) {
        printf("\nEmpty list!\n");
        return;
    }
    while (list != NULL) {
        print_stud_brief(list -> stud);
        list = list -> next;
    }

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

/////////////////////////Sorting routines//////////////////////////////

void swap(StudNode* curr, StudNode* curr_plus_one) {
    
    Student* temp = curr -> stud;
    curr -> stud = curr_plus_one -> stud;
    curr_plus_one -> stud = temp;
    
}

StudNode* sort_by_stud_name(StudNode* list) {
    
    int swapped = 0;
    StudNode* runner;
    int result = 0;
    do {
        runner = list;//reset pointer for next iteration
        swapped = 0;//reset swapped check variable
        while (runner -> next != NULL) {
            result = strcmp(runner -> stud -> name, runner -> next -> stud -> name);
            if (result > 0) {
                swap(runner, runner -> next);
                swapped = 1;
            }
            runner = runner -> next;
        }
    }while (swapped);

    return list;

}

StudNode* sort_by_stud_id(StudNode* list) {
    
    int swapped = 0;
    StudNode* runner;
    do {
        runner = list;//reset pointer for next iteration
        swapped = 0;//reset swapped check variable
        while (runner -> next != NULL) {
            if (runner -> stud -> id > runner -> next -> stud -> id) {
                swap(runner, runner -> next);
                swapped = 1;
            }
            runner = runner -> next;
        }
    }while (swapped);

    return list;

}

StudNode* sort_by_stud_gpa(StudNode* list) {
    
    int swapped = 0;
    StudNode* runner;
    do {
        runner = list;//reset pointer for next iteration
        swapped = 0;//reset swapped check variable
        while (runner -> next != NULL) {
            if (runner -> stud -> gpa < runner -> next -> stud -> gpa) {
                swap(runner, runner -> next);
                swapped = 1;
            }
            runner = runner -> next;
        }
    }while (swapped);

    return list;

}

////////////////////////Sublisting routines for searching (provides a deep copy, must be freed independently)/////////////

//returns empty list if not found
StudNode* find_stud_by_name(StudNode* list, char* name) {

    if (list == NULL) {
        return NULL;
    }
    StudNode* sub_list = NULL;
    Student* stud_copy;
    while (list != NULL) {
        if (strcmp(list -> stud -> name, name) == 0) {
            stud_copy = copy_stud(list -> stud);
            sub_list = insert_stud(sub_list, stud_copy);
        }
        list = list -> next;
    }
    return sub_list;

}

//returns empty list if not found
//Returns a copy of the stud by id
StudNode* find_stud_by_id(StudNode* list, int id) {

    if (list == NULL) {
        return NULL;
    }
    StudNode* sub_list = NULL;
    Student* stud_copy;
    while (list != NULL) {
        if (list -> stud -> id == id) {
            stud_copy = copy_stud(list -> stud);
            sub_list = insert_stud(sub_list, stud_copy);
        }
        list = list -> next;
    }
    return sub_list;

}

////////////////High level routines//////////////////////
StudNode* init_stud_list(const char* file) {

    int student_count;

    StudNode* stud_list = read_students_from_csv(file, &student_count);
    if (!stud_list) {
        return NULL;
    }
    printf("\nSuccessfully read %d students from %s\n", student_count, file);

    return stud_list;

}

StudNode* find_stud(StudNode* list) {

    StudNode* sub_list = NULL;
    int choice = 0;
    int id = 0;
    int count = 0;
    while (1) {
        printf("\nFind student by\n");
        printf("1. Name\n");
        printf("2. ID\n");
        printf("Enter the corresponding number to your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nSomething went wrong!\n");
            while (getchar() != '\n' && getchar() != EOF) {}
            return NULL;
        }
        switch (choice) {
            // You cannot declare variables in a case without {}, or gcc throws an error.
            case 1: {
                char prompt[] = "Enter name: ";
                char* name = get_string_input(prompt, 1);
                sub_list = find_stud_by_name(list, name);
                free(name);
                count = get_list_count(sub_list);
                printf("\n\n%d matches found\n\n", count);
                print_stud_list(sub_list);
                press_enter_to_continue();
                return sub_list;
            }
            case 2:
                while (getchar() != '\n' && getchar() != EOF) {}
                printf("\nEnter ID: ");
                scanf("%d", &id);
                sub_list = find_stud_by_id(list, id);
                count = get_list_count(sub_list);
                printf("\n\n%d matches found\n\n", count);
                print_stud_list(sub_list);
                press_enter_to_continue();
                return sub_list;
            default:
                printf("Nothing happened...try something else?\n");
        }
    }

}

int get_list_count(StudNode* list) {

    int count = 0;
    while (list != NULL) {
        count++;
        list = list -> next;
    }
    return count;

}

int get_course_count(CourseNode* list) {

    int count = 0;
    while (list != NULL) {
        count++;
        list = list -> next;
    }
    return count;

}

//Must free returned value when done
char* get_string_input(char* prompt, int validate) {

    char* input = (char*) malloc(sizeof(char) * 50);
    char choice;
    while (1) {
        while (getchar() != '\n' && getchar() != EOF) {}
        printf("%s", prompt);
        if (fgets(input, 50, stdin)) {
            input[strcspn(input, "\n")] = '\0';
        } else {
            free(input);
            continue;
        }
        if (!validate) {
            return input;
        }
        printf("\nYou entered: %s\nIs this correct? y or n\n", input);
        if (scanf("%c", &choice) != 1) {
            printf("Something went wrong!\n");
            return NULL;
        }
        switch(choice) {
            case 'y':
                return input;
            case 'n':
                continue;
            default:
                printf("I didn't get that, try again\n");
        }
    }

}

int get_new_id(StudNode* list) {

    list = sort_by_stud_id(list);
    while (list -> next != NULL) {
        list = list -> next;
    }
    return list -> stud -> id + 1;

}

CourseNode* get_course_input() {

    CourseNode* list = NULL;
    Course* course;
    int grade = 0;
    char choice;
    printf("\nDo you want to add courses? ");
    while (getchar() != '\n' && getchar() != EOF) {}
    scanf("%c", &choice);
    if (!choice) {
        return NULL;
    }
    while (1) {
        char prompt[] = "\nWhat is the course title? ";
        char* title = get_string_input(prompt, 1);
        printf("\nWhat grade did they get? ");
        while (getchar() != '\n' && getchar() != EOF) {}
        scanf("%d", &grade);
        course = construct_course(title, grade);
        free(title);
        list = insert_course(list, course);
        printf("Add another course? y or n\n");
        while (getchar() != '\n' && getchar() != EOF) {}
        if (scanf("%c", &choice) != 1) {
            printf("Something went wrong!\n");
            return NULL;
        }
        switch(choice) {
            case 'n':
                return list;
            case 'y':
                continue;
            default:
                printf("I didn't get that, try again\n");
        }
    }

}

StudNode* add_new_stud(StudNode* list) {
    
    char* name = get_string_input("Please enter the student's full name: ", 1);
    int id = get_new_id(list);
    CourseNode* courses = get_course_input();
    int numGrades;
    float gpa;
    if (courses != NULL) {
        CourseNode* runner = courses;
        int count = 0;
        while (runner != NULL) {
            count++;
            runner = runner -> next;
        }
        numGrades = count;
        float* grade_points = getGradePoints(courses, numGrades);
        gpa = calculateGPA(grade_points, numGrades);
        free(grade_points);
    } else {
        numGrades = 0;
        gpa = 0.00;
    }

    Student* new_stud = construct_stud(name, courses, id, gpa, numGrades);
    free(name);
    list = insert_stud(list, new_stud);
    printf("Student successfully added to system!\n");
    return list;

}

StudNode* remove_stud_by_id(StudNode* list, int id) {

    if (list == NULL) {
        return NULL;
    }
    StudNode* o_g = list;
    while (list != NULL) {
        if (list -> stud -> id == id) {
            break;
        }
        list = list -> next;
    }
    if (list == NULL) {
        return o_g;
    } else {
        free_stud(list -> stud);
        if (list -> prev == NULL && list -> next == NULL) {
            free(list);
            return NULL;
        } else if (list -> prev == NULL && list -> next != NULL) {
            o_g = list -> next;
            free(list);
            return o_g;
        } else if (list -> prev != NULL && list -> next == NULL) {
            list -> prev -> next = NULL;
            free(list);
            return o_g;
        } else {
            list -> prev -> next = list -> next;
            list -> next -> prev = list -> prev;
            free(list);
            return o_g;
        }
    }
    
}

StudNode* delete_stud(StudNode* list) {

    int input = 0;
    printf("You must have the student id number. Enter the student id number now: ");
    if (scanf("%d", &input) != 1) {
        printf("\n\nSomething went wrong here\n\n");
        return list;
    }
    StudNode* copy = find_stud_by_id(list, input);
    if (copy == NULL) {
        printf("\nStudent not found!\n");
        return list;
    }
    print_stud_list(copy);
    char prompt[] = "Are you sure you want to delete this student? ";
    char* response = get_string_input(prompt, 0);
    printf("%s\n", response);
    if (strcmp(response, "y") != 0 && strcmp(response, "yes") != 0) {
        printf("\nOperation cancelled!\n");
        free(response);
        free_stud(copy -> stud);
        free(copy);
        return list;
    }
    int before = get_list_count(list);
    list = remove_stud_by_id(list, input);
    int after = get_list_count(list);
    if (before > after) {
        printf("\nStudent successfully deleted!\n");
    } else {
        printf("\nStudent not found, try again!\n");
    }
    free(response);
    free_stud(copy -> stud);
    free(copy);
    return list;

}

StudNode* modify_stud_record(StudNode* list) {

    //TODO
    int input = 0;
    printf("You must have the student id number. Enter the student id number now: ");
    if (scanf("%d", &input) != 1) {
        printf("\n\nSomething went wrong here\n\n");
        return list;
    }
    StudNode* runner = list;
    while (runner != NULL) {
        if (runner -> stud -> id == input) {
            break;
        }
        runner = runner -> next;
    }
    if (runner == NULL) {
        printf("\n\nStudent not found. Try again\n");
        return list;
    }
    CourseNode* stud_courses = runner -> stud -> courses;
    char prompt[] = "\nDo you want to add or remove courses? ";
    char* dec_input = get_string_input(prompt, 0);
    if (strcmp(dec_input, "a") == 0 || strcmp(dec_input, "add") == 0) {
        stud_courses = add_course_record(stud_courses);
    } else if (strcmp(dec_input, "r") == 0 || strcmp(dec_input, "remove") == 0) {
        stud_courses = delete_course_record(stud_courses);
    } else {
        printf("\nInvalid input, try again\n");
    }
    float new_gpa = get_GPA(stud_courses);
    runner -> stud -> gpa = new_gpa;
    runner -> stud -> courses = stud_courses;//Update the head of the list to include the new additions
    free(dec_input);
    return list;

}

CourseNode* add_course_record(CourseNode* course_list) {

    int before = 0;
    int after = 0;
    while (1) {
        
        char* input = get_string_input("What is the title of the course? ", 1);
        int grade = 0;
        printf("\nWhat grade do they have? ");
        if (scanf("%d", &grade) != 1) {
            printf("\n\nSomething went wrong here\n\n");
            free(input);
            continue;
        } else {
            before = get_course_count(course_list);
            Course* new_course = construct_course(input, grade);
            course_list = insert_course(course_list, new_course);
            after = get_course_count(course_list);
            if (before < after) {
                printf("\nCourse record successfully added.\n");
            } else {
                printf("\nCourse record not found\n");
            }
        }
        free(input);

        char* re_continue = get_string_input("Continue adding course information? y or n: ", 0);
        if (strcmp(re_continue, "y") == 0 || strcmp(re_continue, "yes") == 0) {
            free(re_continue);
            continue;
        } else {
            free(re_continue);
            return course_list;
        }
    }

}

CourseNode* delete_course_record(CourseNode* course_list) {

    int before = 0;
    int after = 0;
    while (1) {
            
        print_course_list(course_list);
        before = get_course_count(course_list);
        char* input = get_string_input("What is the title of the course you want to delete? ", 1);
        course_list = delete_course(course_list, input);
        after = get_course_count(course_list);
        if (before > after) {
            printf("\nSuccessfully deleted course record.\n");
        } else {
            printf("\nCourse record not found\n");
        }
        free(input);

        char* re_continue = get_string_input("Continue deleting course information? y or n: ", 0);
        if (strcmp(re_continue, "y") != 0 && strcmp(re_continue, "yes") != 0) {
            free(re_continue);
            return course_list;
        }
        free(re_continue);
    }
    return course_list;

}

void press_enter_to_continue() {

    while (getchar() != '\n' && getchar() != EOF) {}
    printf("\n\nPress the Enter button to continue...");
    getchar();

}