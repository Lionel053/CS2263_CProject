#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Structures.h"

//Hard coded for producing a list of 4 courses with customizable grades
Course** getCourses(int grade1, int grade2, int grade3, int grade4) {
    Course** courses = (Course**) malloc(sizeof(Course*) * 4);
    Course** original = courses;

    char* title = "Maths";
    int grade = grade1;
    *courses = construct_course(title, grade);
    courses++;

    title = "Science";
    grade = grade2;
    *courses = construct_course(title, grade);
    courses++;

    title = "Gym";
    grade = grade3;
    *courses = construct_course(title, grade);
    courses++;

    title = "Art";
    grade = grade4;
    *courses = construct_course(title, grade);
    courses++;

    courses = original;

    return courses;
}

//Hard coded to produce a list of 3 students
Student** getStuds() {
    Student** stud_list = (Student**) malloc(sizeof(Student*) * 3);
    Student** original = stud_list;

    Course** courses = getCourses(90, 70, 70, 80);
    float* grade_points = getGradePoints(courses, 4);
    float gpa = calculateGPA(grade_points, 4);
    *stud_list = construct_stud("Some Guy", courses, 1, gpa, 4);
    stud_list++;

    courses = getCourses(80, 70, 80, 100);
    grade_points = getGradePoints(courses, 4);
    gpa = calculateGPA(grade_points, 4);
    *stud_list = construct_stud("Other Dude", courses, 2, gpa, 4);
    stud_list++;

    courses = getCourses(85, 90, 90, 80);
    grade_points = getGradePoints(courses, 4);
    gpa = calculateGPA(grade_points, 4);
    *stud_list = construct_stud("Joe Schmo", courses, 3, gpa, 4);
    stud_list++;

    free(grade_points);

    stud_list = original;

    return stud_list;
}

void free_test_studs(Student** studs) {
    Student** original = studs;
    for (int i = 0; i < 3; i++) {
        free_stud(*studs);
        studs++;
    }
    studs = original;
    free(studs);
}

int main(int argc, char** argv) {
    
    Student** stud_list = getStuds();
    Student** original = stud_list;
    Student* current;

    for (int i = 0; i < 3; i++) {
        current = *stud_list;
        print_stud(current);
        stud_list++;
    }

    stud_list = original;

    for (int i = 0; i < 3; i++) {
        current = *stud_list;
        free_stud(current);
        stud_list++;
    }

    stud_list = original;
    free(stud_list);

    return EXIT_SUCCESS;
}