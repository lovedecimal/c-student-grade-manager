#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define MAX_CLASS_LEN 50

// 学生结构体定义
typedef struct {
    char id[20];
    char name[MAX_NAME_LEN];
    char className[MAX_CLASS_LEN]; // 班级名称
    float chinese;
    float math;
    float english;
    float total;
    char grade[3]; // 成绩等级 A/B/C/D
} Student;

// 函数声明
void showRank(Student students[], int count);
void filterByClass(Student students[], int count);
void setGrade(Student *s);
void addStudent(Student students[], int *count);
void queryStudent(Student students[], int count);
void modifyStudentScore(Student students[], int count);
void deleteStudent(Student students[], int *count);
void sortStudentsByScore(Student students[], int count);
void saveStudentsToFile(Student students[], int count);
void loadStudentsFromFile(Student students[], int *count);

#endif