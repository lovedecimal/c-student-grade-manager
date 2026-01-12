#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // 新增：strlen所需头文件
#include <ctype.h>   // 新增：isdigit所需头文件
#include "student.h"

int main() {
    int choice;
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    char className[50] = "建筑环境2班";

    loadStudentsFromFile(students, &studentCount);

    while (1) {
        printf("\n=============================================\n");
        printf("     %s 学生成绩管理系统 V1.0\n", className);
        printf("=============================================\n");
        printf("  1. 添加学生信息      2. 查询学生信息\n");
        printf("  3. 修改学生成绩      4. 删除学生信息\n");
        printf("  5. 按成绩排序排名    6. 按班级筛选\n");
        printf("  7. 保存并退出\n");
        printf("=============================================\n");
        printf("请输入操作序号: ");
        
        char input[10];
        scanf("%s", input);
        if (strlen(input) != 1 || !isdigit(input[0])) {
            printf("请输入1-7之间的单个数字！\n");
            while (getchar() != '\n');
            continue;
        }
        choice = atoi(input);

        switch (choice) {
            case 1: addStudent(students, &studentCount); break;
            case 2: queryStudent(students, studentCount); break;
            case 3: modifyStudentScore(students, studentCount); break;
            case 4: deleteStudent(students, &studentCount); break;
            case 5: sortStudentsByScore(students, studentCount); showRank(students, studentCount); break;
            case 6: filterByClass(students, studentCount); break;
            case 7: saveStudentsToFile(students, studentCount); printf("数据已保存，感谢使用！\n"); exit(0);
            default: printf("输入无效，请重新选择！\n");
        }
    }
    return 0;
}