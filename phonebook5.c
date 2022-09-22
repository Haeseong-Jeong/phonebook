//verson4 구조체 포인터변수로 배열을 동적으로 할당받아 크기 늘릴 수있게 구현 
// 배열 동적할당하고 배열요소는 구조체 포인터이다. 함수를 옮겨다닐때 포인터로 값을 복사하기때문에 메모리 최적화 좋음
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 3
#define buffer_size 100

typedef struct _person
{
	char* name;
	char* number;
	char* email;
	char* group;
}person;

person** book;//구조체 배열
int n = 0;
int capa = CAPACITY;
char* delim = " ";

void init_book();
void line_command();
void add(char* addname, char* addnumber, char* addemail, char* addgroup);
void find(char* findname);
void removedata(char* delname);
void status();
int compose_name(char* namestr, int limit);
void load(char* filename);
void save();
void handdle_add(char* addname);
void print_book_All();

void print_book_All()
{
	for (int i = 0; i < capa; i++)
	{
		printf("Name : %s\n", book[i]->name);
		printf("Number : %s\n", book[i]->number);
		printf("Email : %s\n", book[i]->email);
		printf("Group : %s\n", book[i]->group);
		printf("-------------------------------------------\n");
	}
	printf("The empty space is %d\n\n", capa - n);
}

void init_book()
{
	book = (person**)malloc(sizeof(person*) * capa);
	for (int i = 0; i < capa; i++)
	{
		book[i] = (person*)malloc(sizeof(person));
		memset(book[i], NULL, sizeof(person));
	}
}

int reallocate()
{
	capa = capa * 2;
	person** newbook;
	newbook = (person**)malloc(sizeof(person*) * capa);
	
	for (int i = 0; i < capa; i++)
	{
		newbook[i] = (person*)malloc(sizeof(person));
		memset(newbook[i], NULL, sizeof(person));
	}

	if (newbook != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			*newbook[i] = *book[i];
		}
		free(book);
		book = newbook;
		return 0;
	}
	free(newbook);
	printf("Realloc Failed!\n");
	return -1;
}
void line_command()
{
	char inputline[buffer_size];//명령입력줄
	char namestr[buffer_size];//이름받아쓰기
	char* command; char* buf1;

	while (1)
	{
		memset(inputline, NULL, buffer_size);
		memset(namestr, NULL, buffer_size);

		//command string input
		printf("$ ");
		if (read_line(stdin, inputline, buffer_size) <= 0) continue;

		//command slice
		command = strtok(inputline, delim);
		if (command == NULL) continue;

		// command가 정상적으로 입력 시작
		if (strcmp(command, "add") == 0)	// add name
		{
			//compose_name(namestr, buffer_size);
			if (compose_name(namestr, buffer_size) == 0)
			{
				handdle_add(namestr); continue;
			}
			else return;
		}

		else if (strcmp(command, "find") == 0)	// find name
		{
			if (compose_name(namestr, buffer_size) == 0)
			{
				find(namestr); continue;
			}
			else return;
		}

		else if (strcmp(command, "delete") == 0)	// delete name
		{
			if (compose_name(namestr, buffer_size) == 0)
			{
				removedata(namestr); continue;
			}
			else return;
		}

		else if (strcmp(command, "status") == 0)	// status
		{
			status(); continue;
		}

		else if (strcmp(command, "printbook") == 0)	// status
		{
			print_book_All(); continue;
		}

		else if (strcmp(command, "load") == 0)	// load filename
		{
			buf1 = strtok(NULL, delim);
			if (buf1 == NULL)
			{
				printf("Need file name\n");
				continue;
			}
			load(buf1); continue;
		}

		else if (strcmp(command, "save") == 0)	// save filename
		{
			save(); continue;//save(filename)
		}

		else if (strcmp(command, "exit") == 0)	// exit
		{
			free(book);
			printf("\nProgram is terminated\n"); return;
		}
		else
		{
			printf("Invaild command, Check your input\n");
			printf("add name\nfind name\ndelete name\nstatus\nload finename\nsave\nexit\n\n");
		}
	}
}

int compose_name(char* realname, int limit)
{
	char* buff = strtok(NULL, "\n");
	if (buff == NULL)
	{
		printf("Name please\n");
		return -1;
	}
	else
	{
		int idx = 0;
		for (int i = 0; i < strlen(buff); i++)
		{
			if (buff[i] != ' ')
			{
				realname[idx] = buff[i];
				idx++;
			}
		}
		realname[idx] = '\0';
	}
	return 0;
}

int read_line(FILE* fp, char* str, int limitlen)
{
	int ch = 0, i = 0;

	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i < limitlen)
		{
			str[i++] = ch;
		}
	}

	str[i] = '\0';
	return i;
}

void handdle_add(char* addname)
{
	char addnumber[buffer_size] = " "; char addemail[buffer_size] = " "; char addgroup[buffer_size] = " ";
	printf("Number : ");
	read_line(stdin, addnumber, buffer_size);

	printf("Email : ");
	read_line(stdin, addemail, buffer_size);

	printf("Group : ");
	read_line(stdin, addgroup, buffer_size);

	add(addname, addnumber, addemail, addgroup);
	return;
}

void add(char* addname, char* addnumber, char* addemail, char* addgroup)
{
	if (n >= capa)
	{
		//printf("Capacity is Full. activate reallocate!\n");
		if (reallocate() != 0) return;
	}

	int i = n - 1;
	while (i >= 0 && strcmp(addname, book[i]->name) < 0)
	{
		*book[i + 1] = *book[i];
		/*book[i + 1]->name = book[i]->name;
		book[i + 1]->number = book[i]->number;
		book[i + 1]->email = book[i]->email;
		book[i + 1]->group = book[i]->group;*/

		i--;
	}
	book[i + 1]->name = strdup(addname);
	book[i + 1]->number = strdup(addnumber);
	book[i + 1]->email = strdup(addemail);
	book[i + 1]->group = strdup(addgroup);
	n++;

	printf("%s add is complete\n\n", addname);
}

int search(char* buf)
{
	int i = 0;
	while (i < n)
	{
		if (strcmp(buf, book[i]->name) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void find(char* findname)
{
	int idx = search(findname);
	if (idx != -1)
	{
		printf("%s\n", book[idx]->name);
		printf("Number : %s\n", book[idx]->number);
		printf("Email : %s\n", book[idx]->email);
		printf("Group : %s\n", book[idx]->group);
		return;
	}
	printf("%s does not exist\n\n", findname);
}

void removedata(char* delname)
{
	int idx = search(delname);
	if (idx != -1)
	{
		while (idx + 1 < n)
		{
			*book[idx] = *book[idx + 1];
			idx++;
		}
		memset(book[idx], NULL, sizeof(person));
		n--;
		printf("%s delete  success\n\n", delname);
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
			printf("Name : %s\n", book[i]->name);
			printf("Number : %s\n", book[i]->number);
			printf("Email : %s\n", book[i]->email);
			printf("Group : %s\n", book[i]->group);
			printf("-------------------------------------------\n");
		}
		printf("Total %d people\n\n", n);
		return;
	}
}

void load(char* filename)
{
	char buff[buffer_size];
	char* name; char* number; char* email; char* group;

	FILE* fp = fopen(filename, "r");//파일이 없으면 null ?
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	//fscanf(파일포인터, 서식, 변수의 주소1, 변수의주소 2,....)
	while (1)
	{
		if (read_line(fp, buff, buffer_size) <= 0) break;
		name = strtok(buff, "#");
		number = strtok(NULL, "#");
		email = strtok(NULL, "#");
		group = strtok(NULL, "#");
		add(name, number, email, group);
	}
	fclose(fp);
	printf("Load completed\n\n");
}

void save()
{
	char filename[buffer_size];
	printf("File name : ");
	read_line(stdin, filename, buffer_size);
	//scanf("%s", filename); -> enter buffer is exist -> have to remove '\n' 
	int i = 0;

	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open failed\n");
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%s#%s#%s#%s#\n", book[i]->name, book[i]->number, book[i]->email, book[i]->group);
	}
	fclose(fp);
	printf("Save completed\n\n");
}


int main()
{
	init_book();

	line_command();

	return 0;
}