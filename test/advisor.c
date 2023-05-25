#include <stdio.h>

const int MAX_COURSES = 100;
const int MAX_NAME_LENGTH = 5;
const int MAX_GROUPS = 7;
int coursename[MAX_COURSES][MAX_NAME_LENGTH];
int courseData[MAX_COURSES][4];
int courseread[MAX_COURSES];
int group[MAX_COURSES][MAX_GROUPS][MAX_GROUPS];
int courseCount = 0;

int mystrcmp(int a[], int b[])
{
	int i = 0;
	while (a[i] != 0 || b[i] != 0)
	{
		if (a[i] != b[i])
		{
			return 0;
		}
		i = i + 1;
	}
	return 1;
}

int gethash(int temp[])
{
	int i = 0;
	while (coursename[i][0] != 0)
	{
		int flag = mystrcmp(coursename[i], temp);
		if (flag == 1)
			return i;
		i = i + 1;
	}
	int j = 0;
	while (temp[j] != 0)
	{
		coursename[i][j] = temp[j];
		j = j + 1;
	}
	return i;
}

int isInHash(int temp)
{
	int i = 0;
	while (i < courseCount)
	{
		if (courseData[i][0] == temp)
			return 1;
		i = i + 1;
	}
	return 0;
}

void printname(int name[])
{
	int i = 0;
	while (name[i] != 0)
	{
		putchar(name[i]);
		i = i + 1;
	}
	return;
}

//输入
void init()
{
	int courseIndex = 0;

	// 解析输入
	int c;
	int fieldIndex = 0; // 当前字段的索引，0表示课程名称，1表示学分，2表示前置课程，3表示成绩
	int nameIndex = 0; // 当前课程名称的字符索引
	int fieldValue = 0; // 当前字段的值
	int readingCourseName = 1; // 标志位，表示当前是否正在读取课程名称
	int inputEnded = 0; // 标志位，表示输入是否结束
	int andindex = 0;
	int orindex = 0;
	int readingPrecourse = 0;
	int groupmember = 0;

	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int y = 0;
	int temp[MAX_NAME_LENGTH];
	//初始化数组
	while (i < MAX_COURSES)
	{
		j = 0;
		while (j < 4)
		{
			courseData[i][j] = -1;
			j = j + 1;
		}
		k = 0;
		while (k < MAX_NAME_LENGTH)
		{
			// 初始化课程数据数组
			coursename[i][k] = 0;
			k = k + 1;
		}
		x = 0;
		while (x < MAX_GROUPS)
		{
			y = 0;
			while (y < MAX_GROUPS)
			{
				group[i][x][y] = -1;
				y = y + 1;
			}
			x = x + 1;
		}
		i = i + 1;
	}
	i = 0;
	while (i < MAX_NAME_LENGTH)
	{
		temp[i] = 0;
		i = i + 1;
	}
	i = 0;
	while ((c = getchar()) != EOF) 
    {
		if (c == 10) //\n
        {
			if (fieldIndex == 0 && nameIndex == 0) {
				// 遇到空行，表示输入结束
				inputEnded = 1;
				break;
			}

			// 遇到换行符，表示一门课程输入结束
			courseData[courseIndex][fieldIndex] = fieldValue;
			fieldIndex = 0;
			nameIndex = 0;
			fieldValue = 0;
			readingCourseName = 1;
			orindex = 0;
			andindex = 0;
			groupmember = 0;
			courseIndex = courseIndex + 1;
			courseCount = courseCount + 1;
			int i = 0;
			while (i < MAX_NAME_LENGTH)
			{
				temp[i] = 0;
				i = i + 1;
			}
			continue;
		}

		if (c == 124) //|
        { 
			// 遇到竖线，表示当前字段结束
			if (readingCourseName)
			{
				// 处理课程名称字段
				fieldValue = gethash(temp); // 将课程名称长度存储在字段值中
				readingCourseName = 0;
			}
			if (readingPrecourse)
			{
				if (temp[0] != 0)
					fieldValue = gethash(temp);
				else
					fieldValue = -1;
				group[courseIndex][orindex][andindex] = fieldValue;
				fieldValue = groupmember + 1;
				andindex = 0;
				readingPrecourse = 0;
			}

			courseData[courseIndex][fieldIndex] = fieldValue;
			fieldIndex = fieldIndex + 1;
			fieldValue = 0;
			nameIndex = 0;
			if (fieldIndex == 2)
			{
				readingPrecourse = 1;
				int i = 0;
				while (i < MAX_NAME_LENGTH)
				{
					temp[i] = 0;
					i = i + 1;
				}
			}
			continue;
		}

		if (c == 44)  //,
		{
			fieldValue = gethash(temp);
			group[courseIndex][orindex][andindex] = fieldValue;
			andindex = andindex + 1;
			groupmember = groupmember + 1;
			nameIndex = 0;
			int i = 0;
			while (i < MAX_NAME_LENGTH)
			{
				temp[i] = 0;
				i = i + 1;
			}
			continue;
		}
		if (c == 59) //;
		{
			fieldValue = gethash(temp);
			group[courseIndex][orindex][andindex] = fieldValue;
			andindex = 0;
			orindex = orindex + 1;
			groupmember = groupmember + 1;
			nameIndex = 0;
			int i = 0;
			while (i < MAX_NAME_LENGTH)
			{
				temp[i] = 0;
				i = i + 1;
			}
			continue;
		}

		if (readingCourseName || readingPrecourse) {
			// 处理课程名称字段
			if (nameIndex < MAX_NAME_LENGTH - 1) {
				// 将字符存储在课程名称数组中
				temp[nameIndex] = c;
				nameIndex = nameIndex + 1;
			}
		}
		else {
			// 处理其他字段
			if (fieldIndex == 1)
				fieldValue = fieldValue * 10 + (c - 48);
			else if (fieldIndex == 3)
				fieldValue = c;
		}
	}
}
// 计算总学分
int calculateTotalCredits(int courseCount) {
	int totalCredits = 0;
	int i = 0;
	while (i < courseCount)
	{
		int credit = courseData[i][1];
		totalCredits += credit;
		i = i + 1;
	}

	return totalCredits;
}

// 计算尝试学分
int calculateAtemptCredits(int courseCount) {
	int attemptCredits = 0;

	int i = 0;
	while (i < courseCount)
	{
		if (courseData[i][3] != 0)
		{
			int credit = courseData[i][1];
			attemptCredits += credit;
		}
		i = i + 1;
	}

	return attemptCredits;
}

// 计算已修学分
int calculateCompletedCredits(int courseCount) {
	int completedCredits = 0;

	int i = 0;
	while (i < courseCount)
	{
		if (courseData[i][3] != 0 && courseData[i][3] != 70)
		{
			int credit = courseData[i][1];
			completedCredits += credit;
		}
		i = i + 1;
	}

	return completedCredits;
}

// 计算GPA
int calculateGPA(int courseCount) {
	int totalScore = 0;
	int totalCredits = calculateAtemptCredits(courseCount);
	int i = 0;
	while (i < courseCount)
	{
		int credit = courseData[i][1];
		int score = courseData[i][3];
		if (score == 0)
		{
			i = i + 1;
			continue;
		}
		else if (score == 70) //F
			score = 0;
		else if (score == 68) //D
			score = 10;
		else if (score == 67) //C
			score = 20;
		else if (score == 66) //B
			score = 30;
		else if (score == 65) //A
			score = 40;

		totalScore += score * credit;
		i = i + 1;
	}

	// 计算带有1位小数的GPA表示
	if (totalCredits == 0)
		return 0;
	int roundedGPA = (totalScore * 10) / totalCredits;
	int decimalPart = roundedGPA % 10;
	if (decimalPart >= 5)
	{
		roundedGPA += 10 - decimalPart;
	}
	else
	{
		roundedGPA -= decimalPart;
	}

	return roundedGPA / 10;
}

// 打印课程推荐
void printCourseRecommendation(int courseCount) {
	int i = 0;
	while (i < MAX_COURSES)
	{
		courseread[i] = 0;
		i = i + 1;
	}
	int num = 0;
	i = 0;
	while (i < courseCount)
	{
		num = courseData[i][0];
		if (courseData[i][3] != 0 && courseData[i][3] != 70) //F
		{
			courseread[num] = 1;
		}
		i = i + 1;
	}
	i = 0;
	int orindex = 0;
	int andindex = 0;
	int flag = 1;
	while (i < courseCount)
	{
		num = courseData[i][0];
		if (courseData[i][3] == 0 || courseData[i][3] == 70)
		{
			if (group[i][0][0] == -1)
			{
				putchar(32);
				putchar(32); //space
				printname(coursename[num]);
				putchar(10); //\n
			}
			else
			{
				orindex = 0;
				while (orindex < MAX_GROUPS && group[i][orindex][0] != -1)
				{
					flag = 1;
					andindex = 0;
					while (andindex < MAX_GROUPS && group[i][orindex][andindex] != -1)
					{
						if (isInHash(group[i][orindex][andindex]) == 0 || courseread[group[i][orindex][andindex]] != 1)
						{
							flag = 0;
							break;
						}
						andindex = andindex + 1;
					}
					if (flag)
					{
						putchar(32);
						putchar(32); //space
						printname(coursename[num]);
						putchar(10); //\n
						break;
					}
					orindex = orindex + 1;
				}
			}
		}
		i = i + 1;
	}
}

int main() {

	init();
	// 计算并输出GPA
	int gpa = calculateGPA(courseCount);
	// printf("GPA: %d.%d\n", gpa / 10, gpa % 10);
	putchar(71); // 'G'
	putchar(80); // 'P'
	putchar(65); // 'A'
	putchar(58); // ':'
	putchar(32); // ' '
	putint(gpa / 10);
	putchar(46); // '.'
	putint(gpa % 10);
	putchar(10); // '\n'


	// 输出总学分
	int attempt = calculateAtemptCredits(courseCount);
	// printf("Hours Attempted: %d\n", attempt);
	putchar(72); // 'H'
	putchar(111); // 'o'
	putchar(117); // 'u'
	putchar(114); // 'r'
	putchar(115); // 's'
	putchar(32); // ' '
	putchar(65); // 'A'
	putchar(116); // 't'
	putchar(116); // 't'
	putchar(101); // 'e'
	putchar(109); // 'm'
	putchar(112); // 'p'
	putchar(116); // 't'
	putchar(101); // 'e'
	putchar(100); // 'd'
	putchar(58); // ':'
	putchar(32); // ' '
	putint(attempt);
	putchar(10); // '\n'


	int completed = calculateCompletedCredits(courseCount);
	// printf("Hours Completed: %d\n", completed);
	putchar(72); // 'H'
	putchar(111); // 'o'
	putchar(117); // 'u'
	putchar(114); // 'r'
	putchar(115); // 's'
	putchar(32); // ' '
	putchar(67); // 'C'
	putchar(111); // 'o'
	putchar(109); // 'm'
	putchar(112); // 'p'
	putchar(108); // 'l'
	putchar(101); // 'e'
	putchar(116); // 't'
	putchar(101); // 'e'
	putchar(100); // 'd'
	putchar(58); // ':'
	putchar(32); // ' '
	putint(completed);
	putchar(10); // '\n'


	int remaining = calculateTotalCredits(courseCount) - calculateCompletedCredits(courseCount);
	// printf("Credits Remaining: %d\n", remaining);
	putchar(67); // 'C'
	putchar(114); // 'r'
	putchar(101); // 'e'
	putchar(100); // 'd'
	putchar(105); // 'i'
	putchar(116); // 't'
	putchar(115); // 's'
	putchar(32); // ' '
	putchar(82); // 'R'
	putchar(101); // 'e'
	putchar(109); // 'm'
	putchar(97); // 'a'
	putchar(105); // 'i'
	putchar(110); // 'n'
	putchar(105); // 'i'
	putchar(110); // 'n'
	putchar(103); // 'g'
	putchar(58); // ':'
	putchar(32); // ' '
	putint(remaining);
	putchar(10); // '\n'


	//打印课程推荐
	// printf("\nPossible Courses to Take Next\n");
	putchar(10); // '\n'
	putchar(80); // 'P'
	putchar(111); // 'o'
	putchar(115); // 's'
	putchar(115); // 's'
	putchar(105); // 'i'
	putchar(98); // 'b'
	putchar(108); // 'l'
	putchar(101); // 'e'
	putchar(32); // ' '
	putchar(67); // 'C'
	putchar(111); // 'o'
	putchar(117); // 'u'
	putchar(114); // 'r'
	putchar(115); // 's'
	putchar(101); // 'e'
	putchar(115); // 's'
	putchar(32); // ' '
	putchar(116); // 't'
	putchar(111); // 'o'
	putchar(32); // ' '
	putchar(84); // 'T'
	putchar(97); // 'a'
	putchar(107); // 'k'
	putchar(101); // 'e'
	putchar(32); // ' '
	putchar(78); // 'N'
	putchar(101); // 'e'
	putchar(120); // 'x'
	putchar(116); // 't'
	putchar(10); // '\n'
	if (remaining != 0)
		printCourseRecommendation(courseCount);
	else
		// printf("  None - Congratulations!\n");
	{
		putchar(32); // ' '
		putchar(32); // ' '
		putchar(78); // 'N'
		putchar(111); // 'o'
		putchar(110); // 'n'
		putchar(101); // 'e'
		putchar(32); // ' '
		putchar(45); // '-'
		putchar(32); // ' '
		putchar(67); // 'C'
		putchar(111); // 'o'
		putchar(110); // 'n'
		putchar(103); // 'g'
		putchar(114); // 'r'
		putchar(97); // 'a'
		putchar(116); // 't'
		putchar(117); // 'u'
		putchar(108); // 'l'
		putchar(97); // 'a'
		putchar(116); // 't'
		putchar(105) ;//i
		putchar(111) ;//o
		putchar(110) ;//n
		putchar(115) ;//s
		putchar(10) ;//'\n'
	}

	return 0;
}
