#include <stdio.h>
#include <string.h>
#define capacity 100
#define buffer_size 20

//char* name[capacity];
//char* number[capacity];

char** names;
char** numbers;
int n = 0;
char delim[] = " ";

void init_directory();
void initphonebook();
void add(char* name, char* number);
void find();
void removename();
void status();
void load();
void save();
void freebook();

void init_directory()
{
	// char name[capacity][sizeof(char*)] 2차원배열? 이라 생각하면 될까?
	names = (char**)malloc(capacity * sizeof(char*)); 
	numbers = (char**)malloc(capacity * sizeof(char*));
}

int read_line(char* str, int limitlen)
{
	int ch = 0, i = 0;

	//버퍼에 입력되어 있는것 하나씩 가져오기
	while ((ch = getchar()) != '\n')
	{
		str[i++] = ch;
	}
	return i;
}

void line_command()
{
	char inputline[buffer_size];
	char* command;char* buf1;	char* buf2;

	while (1)
	{
		printf("$ ");

		if (read_line(inputline, buffer_size) <=0) continue;
			//break와는 달리 반복문 처음으로 돌아간다. continue 밑에는 무시하고 반복문을 실행한다는 뜻
			//readline = 0이라면 입력받은게 없으니 다시 입력 실행
		command = strtok(inputline, delim);
		if (command == NULL) continue;
			//command가 없으니 다시 입력 실행

		// command가 정상적으로 입력 시작
		if (strcmp(command, "add") == 0)	// add name number
		{
			buf1 = strtok(NULL, delim);
			buf2 = strtok(NULL, delim);
			if (buf1 == NULL || buf2 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			add(buf1, buf2);
		}

		if (strcmp(command, "find") == 0)	// find name
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			find(buf1);
		}

		if (strcmp(command, "delete") == 0)	// delete name
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			removename(buf1);
		}

		if (strcmp(command, "status") == 0)	// status
		{
			status();
		}

		if (strcmp(command, "load") == 0)	// load filename
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			load(buf1);
		}

		if (strcmp(command, "save") == 0)	// save as filename
		{
			buf1 = strtok(NULL, delim);//as
			buf2 = strtok(NULL, delim);//filename

			if (buf1 == NULL || buf2 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			save(buf2);//save(filename)
		}
	}

}


int search(char* buf)
{
	int i = 0;
	while (i < n)
	{
		if (strcmp(buf,names[i]) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void freebook()
{
	for (int i = 0; i < capacity; i++)
	{
		free(names[i]);
		free(numbers[i]);
		names[i] = NULL;
		numbers[i] = NULL;
	}
}

void add(char* addname, char* addnumber)//뒤에서 부터 보면 바로 한칸씩 내리면 된다
{
	//char addname[buffer_size];
	//char addnumber[buffer_size];

	////printf("add : ");
	//scanf("%s", addname);
	//scanf("%s", addnumber);
	
	int i = n - 1;
	while (i>=0 && strcmp(addname, names[i]) < 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i+1] = strdup(addname);
	numbers[i+1] = strdup(addnumber);

	n++;


	printf("%s add is complete\n\n", addname);
}

void find(char* findname)
{
	/*char findname[10];
	scanf("%s", findname);*/

	int index = search(findname);
	if (index != -1)
	{
		printf("%s %s\n\n", names[index], numbers[index]);
		return;
	}
	printf("%s does not exist\n\n", findname);
}

void remove(char* delname)
{
	/*char deletename[10];
	scanf("%s", deletename);*/

	int index = search(delname);
	if (index != -1)
	{
		printf("%s delete  success\n\n", delname);
		while (index + 1 < n)
		{
			names[index] = names[index + 1];
			numbers[index] = numbers[index + 1];
		}
		n--;
		return;
	}
	printf("%s does not exist\n\n", delname);
}


void status()
{

	if (n == 0)
	{
		printf("No data\n\n");
		return;
	}
	else
	{
		int i = 0;
		while (i != n)
		{
			if (strcmp(names[i], "\0") == 0)
			{
				i++;
			}
			else
			{
				printf("%s %s\n", names[i], numbers[i]);
				i++;
			}
		}
		printf("Total %d people\n",n);
		return;
	}
}

//
//void initphonebook()
//{
//	while (1)
//	{
//		char fucn[10];
//		scanf("%s", fucn);
//
//		if (strcmp(fucn,"add") == 0)
//		{
//			add();
//		}
//		else if (strcmp(fucn, "find") == 0)
//		{
//			find();
//		}
//		else if (strcmp(fucn, "delete") == 0)
//		{
//			removename();
//		}
//		else if (strcmp(fucn, "status") == 0)
//		{
//			status();
//		}
//		else if (strcmp(fucn, "load") == 0)
//		{
//			load();
//		}
//		else if (strcmp(fucn, "save") == 0)
//		{
//			save();
//		}
//		else if (strcmp(fucn, "exit") == 0)
//		{
//			freebook();
//			printf("Program is terminated");
//			return;
//		}
//	}
//}

int main()
{
	initphonebook();


	return 0;
}

void load(char* filename)
{
	/*char filename[buffer_size];
	scanf("%s", filename);*/
	
	char buf1[buffer_size];
	char buf2[buffer_size];

	//FILE *fp : 파일구조체에 대한 포인터
	FILE* fp = fopen(filename, "r");//파일이 없으면 null ?
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
			//완전한 error 처리를 하기위해서는 	fscanf의 return 값이
		//0 일때(% s 변환 error) 와 -1(EOF)일때, 즉 file조작중 error
		//처리를 구분해서 할 필요도 있습니다
		//fscanf(파일포인터, 서식, 변수의 주소1, 변수의주소 2,....)
	while ((fscanf(fp, "%s", buf1) != EOF))//while 문에서 buf1에 이미 데이터 받고있음
	{
		fscanf(fp, "%s", buf2);//두번째 문자열 데이터 buf2에 누적
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	fclose(fp);
	printf("Load completed\n\n");
}

void save(char* filename)
{
	//char filename[buffer_size];
	// scanf("%s", filename);
	int i = 0;
		
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open failed\n");
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
	printf("Save completed\n");
}

