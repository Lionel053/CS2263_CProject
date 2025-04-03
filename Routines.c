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
    StudNode* stud_list = NULL;  // Empty list
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        // Remove the newline at the end, if any.
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0') {  // Skip empty lines
            continue;
        }
        
        // Get the student name.
        char* token = strtok(line, ",");
        if (token == NULL) {
            continue;  // Skip if line malformed
        }
        char* name = strdup(token);
        if (name == NULL) {
            printf("Memory allocation failed for name.\n");
            continue;
        }
        
        // Get the student ID.
        token = strtok(NULL, ",");
        if (token == NULL) {
            free(name);
            continue;
        }
        int id = atoi(token);

        // Process the courses.
        CourseNode* course_list = NULL;  // Start with an empty course list.
        while (1) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                break;  // No more tokens.
            }
            // Token is the course title.
            char* course_title = strdup(token);
            if (course_title == NULL) {
                printf("Memory allocation failed for course title.\n");
                break;
            }
            
            // Get the course grade.
            token = strtok(NULL, ",");
            if (token == NULL) {  
                free(course_title);
                break;  // Malformed line, stop processing courses.
            }
            int grade = atoi(token);
            Course* course = construct_course(course_title, grade);
            if (course == NULL) {
                printf("Failed to construct course for %s\n", course_title);
                free(course_title);
                continue;
            }
            course_list = insert_course(course_list, course);
            free(course_title);
        }
        
        int numGrades = get_course_count(course_list);
        float gpa = get_GPA(course_list);
        Student* stud = construct_stud(name, course_list, id, gpa, numGrades);
        stud_list = insert_stud(stud_list, stud);
        free(name);
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
    while (list != NULL) {
        // Print the student's name and id.
        fprintf(file, "%s,%d", list->stud->name, list->stud->id);
        CourseNode* courses = list->stud->courses;
        // For each course, prepend a comma then print the course title and grade.
        while (courses != NULL) {
            fprintf(file, ",%s,%d", courses->course->title, courses->course->grade);
            courses = courses->next;
        }
        // End the line for the student.
        fprintf(file, "\n");
        list = list->next;
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

int compare_by_name(Student* a, Student* b) {
    return strcmp(a->name, b->name);
}

int compare_by_id(Student* a, Student* b) {
    return a->id - b->id;
}

int compare_by_gpa(Student* a, Student* b) {
    if (a->gpa == b->gpa) {
        return 0;
    }
    return (a->gpa > b->gpa) ? -1 : 1;
}

StudNode* split(StudNode* head) {
    if (!head || !head->next) {
        return NULL;
    }

    StudNode* slow = head;
    StudNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    StudNode* second_half = slow->next;
    slow->next = NULL;
    if (second_half) {
        second_half->prev = NULL;
    }
    return second_half;
}

StudNode* merge(StudNode* left, StudNode* right, Comparator cmp) {
    if (!left) {
        return right;
    }
    if (!right) {
        return left;
    }

    if (cmp(left->stud, right->stud) <= 0) {
        left->next = merge(left->next, right, cmp);
        if (left->next) {
            left->next->prev = left;
        }
        left->prev = NULL;
        return left;
    } else {
        right->next = merge(left, right->next, cmp);
        if (right->next) {
            right->next->prev = right;
        }
        right->prev = NULL;
        return right;
    }
}

StudNode* stud_merge_sort(StudNode* list, Comparator cmp) {
    if (!list || !list->next) {
        return list;
    }

    StudNode* second_half = split(list);
    list = stud_merge_sort(list, cmp);
    second_half = stud_merge_sort(second_half, cmp);
    return merge(list, second_half, cmp);
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

void find_stud(StudNode* list) {
    while (1) {
        printf("\nFind student by:\n");
        printf("1. Name\n");
        printf("2. ID\n");
        printf("\nEnter your choice: ");
        
        StudNode* sub_list = NULL;
        int count = 0;
        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        switch (choice) {
            case 1: {
                char name[100];
                printf("\nEnter name: ");
                scanf(" %[^\n]", name);
                while (getchar() != '\n' && getchar() != EOF);
                sub_list = find_stud_by_name(list, name);
                count = get_list_count(sub_list);
                printf("\n\n%d matches found\n\n", count);
                print_stud_list(sub_list);
                return;
            }
            
            case 2: {
                int id;
                printf("\nEnter ID: ");
                scanf("%d", &id);
                while (getchar() != '\n' && getchar() != EOF);
                sub_list = find_stud_by_id(list, id);
                count = get_list_count(sub_list);
                printf("\n\n%d matches found\n\n", count);
                print_stud_list(sub_list);
                return;
            }
            
            default:
                printf("Invalid input. Please try again.\n");
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


int get_new_id(StudNode* list) {
    int max_id = 101;
    for (StudNode* curr = list; curr != NULL; curr = curr->next) {
        if (curr->stud->id > max_id) {
            max_id = curr->stud->id;
        }
    }
    return max_id + 1;
}

CourseNode* get_course_input() {
    CourseNode* list = NULL;
    int grade = 0;
    char choice;
    while (1) {
        printf("Enter the course title: ");
        char temp[100];
        if (fgets(temp, sizeof(temp), stdin)) {
            temp[strcspn(temp, "\n")] = '\0';
        } else {
            printf("Error reading course title.\n");
            continue;
        }
        
        char* title = malloc(strlen(temp) + 1);
        if (title == NULL) {
            printf("Memory allocation failed for course title.\n");
            continue;
        }
        strcpy(title, temp);
        
        printf("Enter the grade (in percent): ");
        if (scanf("%d", &grade) != 1) {
            printf("Invalid grade input.\n");
            free(title);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        Course* new_course = construct_course(title, grade);
        free(title);
        if (new_course == NULL) {
            printf("Failed to construct course record.\n");
            continue;
        }
        list = insert_course(list, new_course);
        
        printf("Add another course? (y)es or (n)o: ");
        if (scanf("%c", &choice) != 1) {
            printf("Input error!\n");
            break;
        }

        while ((c = getchar()) != '\n' && c != EOF);
        if (choice == 'n')
            break;
    }
    return list;
}



StudNode* add_new_stud(StudNode* list) {
    char buffer[100];
    printf("\nEnter the student's name: ");
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
    }
    char* name = (char*)malloc(strlen(buffer) + 1);
    if (name == NULL) {
        printf("Memory allocation failed for name.\n");
        return list;
    }
    strcpy(name, buffer);
    
    int id = get_new_id(list);
    CourseNode* courses = get_course_input(); // Make sure to trim newline in get_course_input as well
    int numGrades;
    float gpa;
    if (courses != NULL) {
        int count = 0;
        CourseNode* runner = courses;
        while (runner != NULL) {
            count++;
            runner = runner->next;
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
    printf("Enter the Student ID number now: ");
    if (scanf("%d", &input) != 1) {
        printf("\n\nSomething went wrong here\n\n");
        while (getchar() != '\n');
        return list;
    }
    while (getchar() != '\n');

    StudNode* copy = find_stud_by_id(list, input);
    if (copy == NULL) {
        printf("\nStudent not found!\n");
        return list;
    }
    print_stud_list(copy);
    
    printf("Are you sure you want to delete this student? Enter (y) to confirm: ");
    char c;
    if (scanf(" %c", &c) != 1 || c != 'y') {
        printf("\nOperation cancelled!\n");
        while (getchar() != '\n'); // **Clear buffer after char input**
        free_stud(copy->stud);
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
    free_stud(copy->stud);
    free(copy);
    
    while (getchar() != '\n'); // **Ensure buffer is clear before returning**
    return list;
}

StudNode* modify_stud_record(StudNode* list) {
    int input = 0;
    printf("Enter the student ID: ");
    if (scanf("%d", &input) != 1) {
        printf("\n\nInvalid input.\n\n");
        // Clear input buffer
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return list;
    }
    // Clear input buffer after reading integer.
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    StudNode* runner = list;
    while (runner != NULL) {
        if (runner->stud->id == input) {
            break;
        }
        runner = runner->next;
    }
    if (runner == NULL) {
        printf("\n\nStudent not found. Try again\n");
        return list;
    }
    CourseNode* stud_courses = runner->stud->courses;
    printf("\nDo you want to (a)dd or (r)emove courses? ");
    
    // Use scanf with " %c" to skip any whitespace:
    char c;
    if (scanf(" %c", &c) != 1) {
        printf("\nInvalid input.\n");
        // Clear buffer
        while ((ch = getchar()) != '\n' && ch != EOF);
        return list;
    }
    // Clear buffer after reading the character.
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    if (c == 'a') {
        stud_courses = add_course_record(stud_courses);
    } else if (c == 'r') {
        stud_courses = delete_course_record(stud_courses);
    } else {
        printf("\nInvalid input.\n");
    }
    float new_gpa = get_GPA(stud_courses);
    runner->stud->gpa = new_gpa;
    runner->stud->courses = stud_courses; // Update the head of the list to include the new additions
    return list;
}

CourseNode* add_course_record(CourseNode* course_list) {
    int before = 0;
    int after = 0;
    while (1) {
        int grade = 0;
        printf("Enter the name of the course: ");

        char buffer[100]; 
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        char* name = (char*)malloc(strlen(buffer) + 1);
        if (!name) {
            printf("Memory allocation failed!\n");
            return course_list;
        }
        strcpy(name, buffer); 

        printf("\nEnter the grade (in percent): ");
        if (scanf("%d", &grade) != 1) {
            printf("\n\nSomething went wrong here\n\n");
            free(name);  // Free allocated memory on error
        } else {
            before = get_course_count(course_list);
            Course* new_course = construct_course(name, grade);
            course_list = insert_course(course_list, new_course);
            after = get_course_count(course_list);
            if (before < after) {
                printf("\nCourse record successfully added.\n");
            } else {
                printf("\nCourse record not found\n");
            }
        }

        while (getchar() != '\n');

        printf("Continue adding course information? (y)es or (n)o: ");
        char c = getchar();
        while (getchar() != '\n');

        if (c != 'y') {
            return course_list;
        }
    }
}


CourseNode* delete_course_record(CourseNode* course_list) {
    int before = 0;
    int after = 0;
    print_course_list(course_list);
    before = get_course_count(course_list);
    printf("Name of course to delete: ");
    char course[100];
    fgets(course, sizeof(course), stdin);
    course[strcspn(course, "\n")] = '\0';
    course_list = delete_course(course_list, course);
    after = get_course_count(course_list);
    if (before > after) {
        printf("\nSuccessfully deleted course record.\n");
    } else {
        printf("\nCourse record not found\n");
    }
    return course_list;
}