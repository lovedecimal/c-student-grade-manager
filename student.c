#include <stdio.h>
#include <string.h>
#include "student.h"

// 自动评定成绩等级
void setGrade(Student *s) {
    s->total = s->chinese + s->math + s->english;
    if (s->total >= 270) strcpy(s->grade, "A");
    else if (s->total >= 240) strcpy(s->grade, "B");
    else if (s->total >= 210) strcpy(s->grade, "C");
    else strcpy(s->grade, "D");
}

// 展示成绩排名
void showRank(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    printf("\n===== 成绩排名榜 =====\n");
    printf("名次\t学号\t姓名\t班级\t总成绩\t等级\n");
    printf("-------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\t%.1f\t%s\n",
               i+1, students[i].id, students[i].name,
               students[i].className, students[i].total, students[i].grade);
    }
}

// 按班级筛选学生
void filterByClass(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    char targetClass[MAX_CLASS_LEN];
    printf("请输入要筛选的班级名称: ");
    scanf("%s", targetClass);

    printf("\n===== %s 班级学生列表 =====\n", targetClass);
    printf("学号\t姓名\t语文\t数学\t英语\t总成绩\t等级\n");
    printf("--------------------------------------------------\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].className, targetClass) == 0) {
            printf("%s\t%s\t%.1f\t%.1f\t%.1f\t%.1f\t%s\n",
                   students[i].id, students[i].name,
                   students[i].chinese, students[i].math, students[i].english,
                   students[i].total, students[i].grade);
            found = 1;
        }
    }
    if (!found) printf("未找到该班级学生！\n");
}

// 添加学生信息
void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("学生数量已达上限！\n");
        return;
    }

    Student s;
    printf("请输入学号: ");
    scanf("%s", s.id);
    printf("请输入姓名: ");
    scanf("%s", s.name);
    printf("请输入班级: ");
    scanf("%s", s.className);
    printf("请输入语文成绩: ");
    scanf("%f", &s.chinese);
    printf("请输入数学成绩: ");
    scanf("%f", &s.math);
    printf("请输入英语成绩: ");
    scanf("%f", &s.english);
    setGrade(&s);

    students[*count] = s;
    (*count)++;
    printf("学生信息添加成功！\n");
}

// 查询学生信息
void queryStudent(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    int type;
    char keyword[MAX_NAME_LEN];
    printf("请选择查询方式：1-按学号 2-按姓名: ");
    scanf("%d", &type);
    printf("请输入查询关键词: ");
    scanf("%s", keyword);

    int found = 0;
    printf("\n===== 查询结果 =====\n");
    printf("学号\t姓名\t班级\t总成绩\t等级\n");
    printf("-------------------------\n");
    for (int i = 0; i < count; i++) {
        if ((type == 1 && strcmp(students[i].id, keyword) == 0) ||
            (type == 2 && strcmp(students[i].name, keyword) == 0)) {
            printf("%s\t%s\t%s\t%.1f\t%s\n",
                   students[i].id, students[i].name, students[i].className,
                   students[i].total, students[i].grade);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到该学生信息！\n");
    }
}

// 修改学生成绩
void modifyStudentScore(Student students[], int count) {
    if (count == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    char id[20];
    printf("请输入要修改的学生学号: ");
    scanf("%s", id);

    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            printf("当前成绩：语文=%.1f, 数学=%.1f, 英语=%.1f\n",
                   students[i].chinese, students[i].math, students[i].english);
            printf("请输入新的语文成绩: ");
            scanf("%f", &students[i].chinese);
            printf("请输入新的数学成绩: ");
            scanf("%f", &students[i].math);
            printf("请输入新的英语成绩: ");
            scanf("%f", &students[i].english);
            setGrade(&students[i]);
            printf("成绩修改成功！新等级：%s\n", students[i].grade);
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 删除学生信息
void deleteStudent(Student students[], int *count) {
    if (*count == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    char id[20];
    printf("请输入要删除的学生学号: ");
    scanf("%s", id);

    for (int i = 0; i < *count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("学生信息删除成功！\n");
            return;
        }
    }
    printf("未找到该学生！\n");
}

// 按总成绩排序
void sortStudentsByScore(Student students[], int count) {
    if (count <= 1) {
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].total < students[j + 1].total) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 保存数据到文件
void saveStudentsToFile(Student students[], int count) {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("文件打开失败，保存失败！\n");
        return;
    }
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
}

// 从文件加载数据
void loadStudentsFromFile(Student students[], int *count) {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        *count = 0;
        return;
    }
    *count = fread(students, sizeof(Student), MAX_STUDENTS, fp);
    fclose(fp);
    printf("成功加载 %d 条学生信息！\n", *count);
}