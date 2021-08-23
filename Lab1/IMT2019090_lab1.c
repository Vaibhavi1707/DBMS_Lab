# include <stdio.h> 
# include <string.h>


typedef struct student {
  int rollnum;
  char name[30];
  int age;
} StudentRecord;

int NO_OF_STUDENTS = 5; // no. of student records
int NO_OF_INTS = 20; // no. of numbers to be stored and read 

/**
 * Generates a list of NO_OF_STUDENTS students
 * @param students: empty list of student records to which student records are
 *          to be added.
 * @return 0 on success non-zero on failure 
 */
int generate_students(StudentRecord *students) {
  for (int i = 0; i < NO_OF_STUDENTS; i ++) {
    char name[30] = {'A' + i};
    students[i].rollnum = i + 1;
    students[i].age = i + 18;
    strcpy(students[i].name, name);
  }

  return 0;
}

/**
 * Prints details of all students on stdout
 * @param students: List of all student records to be displayed
 * @return 0 on success non-zero on failure
 */
int display_students(StudentRecord *students) {
  for (int i = 0; i < NO_OF_STUDENTS; i ++) {
    StudentRecord student = students[i];
    printf("%d %s %d\n", student.rollnum, student.name, student.age);
  }

  return 0;
}

/**
 * Prints details of all numbers on stdout
 * @param nums: List of all numbers to be displayed
 * @return 0 on success non-zero on failure
 */
int display_nums(int *nums) {
  for (int i = 0; i < NO_OF_INTS; i ++) {
    int num = nums[i];
    printf("%d\n", num);
  }

  return 0;
}

/**
 * Generates and stores NO_OF_INTS numbers in the text format in a file
 * @param filename: Name of the file where the numbers are to be stored
 * @return 0 on success non-zero on failure
 */
int save_num_text( char *filename ) { 
  FILE *number_file = fopen(filename, "w");
  
  for (int i = 0; i < NO_OF_INTS; i ++) {
    fprintf (number_file, "%d\n", i);
  }
  
  fclose(number_file);

  return 0;
}

/**
 * Reads and displays to stdout, all numbers stored in the text format, from a file
 * @param filename: Name of the file from where numbers are to be read
 * @return 0 on success non-zero on failure
 */ 
int read_num_text( char *filename ) { 
  FILE *number_file = fopen(filename, "r");
  
  if (!number_file) {
    fprintf(stderr, "File not found\n");
    return 1;
  }

  while (!feof(number_file)) {
    int n;
    fscanf(number_file, "%d\n", &n);
    printf("%d\n", n);
  }
  
  fclose(number_file);

  return 0;
}

/**
 * Stores student details in the text format in a file
 * @param filename: Name of the file where the student details are to be stored
 * @return 0 on success non-zero on failure
 */
int save_struct_text( char *filename ) { 
  FILE *student_records = fopen(filename, "w");
  StudentRecord students[NO_OF_STUDENTS];
  int status = generate_students(students);
  
  for (int i = 0; i < NO_OF_STUDENTS; i ++) {
    fprintf(student_records, "%d %s %d\n", students[i].rollnum, students[i].name, students[i].age);
  }

  fclose(student_records);
  
  return 0;
}

/**
 * Reads and displays to stdout, all student details stored in text format, from a file 
 * @param filename: Name of the file from where student details are to be read
 * @return 0 on success non-zero on failure
 */
int read_struct_text( char *filename ) {
  FILE *student_records = fopen(filename, "r");
  
  if (!student_records) {
    fprintf(stderr, "File not found\n");
    return 1;
  }

  while (!feof(student_records)) {
    int rollnum, age;
    char name[30];
    fscanf(student_records, "%d %s %d\n", &rollnum, name, &age);
    printf("%d %s %d\n", rollnum, name, age);
  }

  fclose(student_records);

  return 0;
}

/**
 * Stores numbers in a binary format in a file
 * @param filename: Name of the file where the numbers are to be stored
 * @return 0 on success non-zero on failure
 */
int save_num_binary( char *filename ) { 
  FILE *binary_nums = fopen(filename, "wb");
  
  for (int i = 0; i < NO_OF_INTS; i ++) {
    fwrite(&i, sizeof(int), 1, binary_nums);
  }
  
  fclose(binary_nums);

  return 0;
}

/**
 * Reads and displays to stdout, all numbers stored in binary format, from a file
 * @param filename: Name of the file from where the numbers are to be read
 * @return 0 on success non-zero on failure
 */ 
int read_num_binary( char *filename ) {
  FILE *binary_nums = fopen(filename, "rb");
  
  if (!binary_nums) {
    fprintf(stderr, "File not found\n");
    return 1;
  }
  
  int nums[NO_OF_INTS];

  fread(&nums, NO_OF_INTS * sizeof(int), NO_OF_INTS, binary_nums);
  int status = display_nums(nums);

  fclose(binary_nums);

  return 0;
}

/**
 * Stores student details in binary format in a file
 * @param filename: Name of the file where the student details are to be stored
 * @return 0 on success non-zero on failure
 */ 
int save_struct_binary( char *filename ) {
  FILE *binary_student = fopen(filename, "wb");
  StudentRecord students[NO_OF_STUDENTS];
  int status = generate_students(students);

  for (int i = 0; i < NO_OF_STUDENTS; i ++) {
    fwrite(&students[i], sizeof(StudentRecord), 1, binary_student);
  }
  
  fclose(binary_student);

  return 0;
}

/**
 * Reads and displays to stdout, all the student details stored in binary format, from a file
 * @param filename: Name of the file from where the student details are to be read
 * @return 0 on success non-zero on failure
 */
int read_struct_binary( char *filename ) {
  FILE *binary_students = fopen(filename, "rb");
  
  if (!binary_students) {
    fprintf(stderr, "File not found\n");
    return 1;
  }
  
  StudentRecord students[NO_OF_STUDENTS];

  fread(&students, NO_OF_STUDENTS * sizeof(StudentRecord), 5, binary_students);
  int status = display_students(students);
  
  fclose(binary_students);
  
  return status;
}

