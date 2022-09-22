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
	// char name[capacity][sizeof(char*)] 2�����迭? �̶� �����ϸ� �ɱ�?
	names = (char**)malloc(capacity * sizeof(char*)); 
	numbers = (char**)malloc(capacity * sizeof(char*));
}

int read_line(char* str, int limitlen)
{
	int ch = 0, i = 0;

	//���ۿ� �ԷµǾ� �ִ°� �ϳ��� ��������
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
			//break�ʹ� �޸� �ݺ��� ó������ ���ư���. continue �ؿ��� �����ϰ� �ݺ����� �����Ѵٴ� ��
			//readline = 0�̶�� �Է¹����� ������ �ٽ� �Է� ����
		command = strtok(inputline, delim);
		if (command == NULL) continue;
			//command�� ������ �ٽ� �Է� ����

		// command�� ���������� �Է� ����
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

void add(char* addname, char* addnumber)//�ڿ��� ���� ���� �ٷ� ��ĭ�� ������ �ȴ�
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

	//FILE *fp : ���ϱ���ü�� ���� ������
	FILE* fp = fopen(filename, "r");//������ ������ null ?
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
			//������ error ó���� �ϱ����ؼ��� 	fscanf�� return ����
		//0 �϶�(% s ��ȯ error) �� -1(EOF)�϶�, �� file������ error
		//ó���� �����ؼ� �� �ʿ䵵 �ֽ��ϴ�
		//fscanf(����������, ����, ������ �ּ�1, �������ּ� 2,....)
	while ((fscanf(fp, "%s", buf1) != EOF))//while ������ buf1�� �̹� ������ �ް�����
	{
		fscanf(fp, "%s", buf2);//�ι�° ���ڿ� ������ buf2�� ����
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

