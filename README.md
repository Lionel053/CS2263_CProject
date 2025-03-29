# Student Grade Management
This system currently only supports adding students and viewing the list of students. Further development to come.

Last update:
Removed all previous files, updated this README file
Added the necessary files Structures.h, Routines.c, and StudentTest.c to deliver v1.0 of this program. Minimal functionality now exists.

Latest update:
Added read and write routines in Routines - declared in Structs. This version is 1.1 and defines additional basic features such as read/write data from file and gives
the executor the option to load their own data - provided it is formatted correctly.

Latest update: v2.0
Functionality added: Reading and writing zero as a many courses on the file up to a maximum of 256 characters for student data (may cause issues if line is longer)
			Can now add and delete students
			Can now add and delete course records for students (dynamic update of gpa included)
			Menu interface implemented to include...
				sorting by id, gpa, name
				finding a particular student
				Adding a new student record (and deleting one)
				Modifying the student record (ie adding and removing courses)
