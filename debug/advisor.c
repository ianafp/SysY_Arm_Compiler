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

int main()
{
    return 1;
}