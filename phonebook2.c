#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CAPACITY 4
#define buffer_size 20

char** names;
char** numbers;
int n = 0;
int capacity = _CAPACITY;
char* delim = " ";

void init_directory();
void line_command();
void add(char* name, char* number);
void find(char* findname);
void removedata(char* delname);
void status();
void load(char* filename);
void save(char* filename);
void freebook();
void reallocate();

void reallocate()
{
	capacity = capacity * 2;

	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));
	memset(tmp1, NULL, capacity * sizeof(char*));
	memset(tmp2, NULL, capacity * sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}
	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}
void print_book()
{
	for (int i = 0; i < capacity; i++)
	{
		printf("BOOK[%d] = %s %s\n", i, names[i], numbers[i]);
	}
}

void init_directory()
{
	// char name[capacity][sizeof(char*)] 2�����迭? �̶� �����ϸ� �ɱ�?
	names = (char**)malloc(capacity * sizeof(char*));
	numbers = (char**)malloc(capacity * sizeof(char*));
	memset(names, NULL, capacity * sizeof(char*));
	memset(numbers, NULL, capacity * sizeof(char*));
							//capacity * 8
	printf("Current size %d\n", capacity);
}

int read_line(char* str, int limitlen)
{
	int ch = 0, i = 0;
a
	//���ۿ� �ԷµǾ� �ִ°� �ϳ��� ��������
	//���ۿ� �ƹ��͵� ���ٸ� ����(��\n��)�� �� ������ ����ڷκ��� ���ڸ� �޾Ƽ� ���ۿ� �����ϰ� ���� ���� �����͸� ��ȯ�Ѵ�
	//< ���� ���ڰ� ��1�� �̸� ���ۿ��� ��1���� ��\n���� ���ٰ� ��1���� ���ϵ� >
	while ((ch = getchar()) != '\n')
	{
		str[i++] = ch;
	}
	return i;
}

void line_command()
{
	char inputline[buffer_size] ="\0";
	char* command; char* buf1;	char* buf2;

	while (1)
	{
		memset(inputline, NULL, buffer_size);
		//command = "\0"; buf1 = "\0"; char* buf2 = "\0";
		printf("$ ");

		if (read_line(inputline, buffer_size) <= 0) continue;
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
			add(buf1, buf2); continue;
		}

		else if (strcmp(command, "find") == 0)	// find name
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			find(buf1); continue;
		}

		else if (strcmp(command, "delete") == 0)	// delete name
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			removedata(buf1); continue;
		}

		else if (strcmp(command, "status") == 0)	// status
		{
			status(); continue;
		}

		else if (strcmp(command, "printbook") == 0)	// status
		{
			print_book(); continue;
		}

		else if (strcmp(command, "load") == 0)	// load filename
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			load(buf1); continue;
		}

		else if (strcmp(command, "save") == 0)	// save as filename
		{
			buf1 = strtok(NULL, delim);//as
			buf2 = strtok(NULL, delim);//filename

			if (buf1 == NULL || buf2 == NULL)
			{
				printf("Invaild command\n");
				continue;
			}
			save(buf2); continue;//save(filename)
		}

		else if (strcmp(command, "exit") == 0)	// exit
		{
			
			printf("\nProgram is terminated\n"); return;
		}
	}
}


int search(char* buf)
{
	int i = 0;
	while (i < n)
	{
		if (strcmp(buf, names[i]) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void freebook()
{
	//for (int i = 0; i < capacity; i++)
	//{
	//	free(names[i]);
	//	free(numbers[i]);
	//	//names[i] = NULL;
	//	//numbers[i] = NULL;
	//}
	free(names);
	free(numbers);
}

void add(char* addname, char* addnumber)//�ڿ��� ���� ���� �ٷ� ��ĭ�� ������ �ȴ�
{
	if (n>=capacity)
	{
		reallocate();
		printf("Capacity is full, Execute reallocacte\n\n");
	}
	int i = n - 1;
	while (i >= 0 && strcmp(addname, names[i]) < 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(addname);
	//names[i + 1] = addname; �����Ҵ��ϸ� ����. strdup�� �����ؼ� �Ѱ��ִ°��� ����
	numbers[i + 1] = strdup(addnumber);

	n++;

	printf("%s add is complete\n\n", addname);
}

void find(char* findname)
{
	int index = search(findname);
	if (index != -1)
	{
		printf("%s %s\n\n", names[index], numbers[index]);
		return;
	}
	printf("%s does not exist\n\n", findname);
}

void removedata(char* delname)
{
	int index = search(delname);
	if (index != -1)
	{
		printf("%s delete  success\n\n", delname);
		while (index + 1 < n)
		{
			names[index] = names[index + 1];
			numbers[index] = numbers[index + 1];
			index++;
		}
		names[index] = NULL;
		numbers[index] = NULL;
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
		for (int i = 0; i < n; i++)
		{
			printf("%s %s\n", names[i], numbers[i]);
		}
		printf("Total %d people\n\n", n);
		return;
	}
}

int main()
{
	init_directory();
	line_command();

	freebook();
	return 0;
}

void load(char* filename)
{
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
		add(buf1, buf2);
	}
	fclose(fp);
	printf("Load completed\n\n");
}

void save(char* filename)
{
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
	printf("Save completed\n\n");
}