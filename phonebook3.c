#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CAPACITY 100
#define buffer_size 100

typedef struct
{
	char* name;
	char* number;
	char* email;
	char* group;
}person;

person book[_CAPACITY];//구조체 배열
int n = 0;
int capacity = _CAPACITY;
char* delim = " ";


//void init_directory();
void line_command();
void add(char* addname, char* addnumber, char* addemail,char* addgroup);
void find(char* findname);
void removedata(char* delname);
void status();
void compose_name(char* namestr, int limit);
void load(char* filename);
void save();
void handdle_add(char* addname);
void print_book();

void print_book()
{
	for (int i = 0; i < capacity; i++)
	{
		printf("BOOK[%d] = %s %s\n", i, book[i].name, book[i].number);
	}
}

int read_line(FILE *fp, char* str, int limitlen)
{
	//file standard input = stdin (keyboard)
	int ch = 0, i = 0;
	//버퍼에 입력되어 있는것 하나씩 가져오기
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
	{
		if (i<limitlen)
		{
			str[i++] = ch;
		}
	}
	str[i] = '\0';
	return i;
}

void compose_name(char* namestr, int limit)
{
	char* buff;
	buff = strtok(NULL, "\n");
	if (buff == NULL)
	{
		printf("Name please\n");
		return;
	}
	else
	{
		strcat(namestr, buff);
		while ((buff = strtok(NULL, " ")) != NULL)
		{
			if (strlen(namestr) <= limit)
			{
				strcat(namestr, buff);
			}
		}
	}
	/*else 이게 안되네;
	{
		int idx = 0;
		for (int i = 0; i < strlen(buff); i++)
		{
			if (buff[i] != ' ');
			{
				namestr[idx++] = buff[i];
			}
		}
		namestr[idx] = '\0';
	}*/
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

void line_command()
{
	char inputline[buffer_size] = "\0";//명령입력줄
	char name_str[buffer_size] = "\0";//이름받아쓰기
	char* command; char* buf1;	

	while (1)
	{
		memset(inputline, NULL, buffer_size);
		memset(name_str, NULL, buffer_size);
		//command = "\0"; buf1 = "\0";

		//command string input
		printf("$ ");
		if (read_line(stdin, inputline, buffer_size) <= 0) continue;

		//command slice
		command = strtok(inputline, delim);
		if (command == NULL) continue;

	    // command가 정상적으로 입력 시작
		if (strcmp(command, "add") == 0)	// add name
		{
			//compose_name(name_str, buffer_size);
			buf1 = strtok(NULL, "\n");
			int idx = 0;
			for (int i = 0; i < strlen(buf1); i++)
			{
				if (buf1[i] != ' ');
				{
					name_str[idx++] = buf1[i];
				}
			}
			name_str[idx] = '\0';
			handdle_add(name_str); continue;
		}

		else if (strcmp(command, "find") == 0)	// find name
		{
			compose_name(name_str, buffer_size);
			find(name_str); continue;
		}

		else if (strcmp(command, "delete") == 0)	// delete name
		{
			compose_name(name_str, buffer_size);
			removedata(name_str); continue;
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
				printf("Need file name\n");
				continue;
			}
			load(buf1); continue;
		}

		else if (strcmp(command, "save") == 0)	// save as filename
		{
			save(); continue;//save(filename)
		}

		else if (strcmp(command, "exit") == 0)	// exit
		{

			printf("\nProgram is terminated\n"); return;
		}
		else
		{
			printf("Invaild command, Check your input\n");
			printf("add name\nfind name\ndelete name\nstatus\nload finename\nsave\nexit\n\n");
		}
	}
}


int search(char* buf)
{
	int i = 0;
	while (i < n)
	{
		if (strcmp(buf, book[i].name) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}


void add(char* addname, char* addnumber, char* addemail, char* addgroup)
{
	int i = n - 1;
	while (i >= 0 && strcmp(addname, book[i].name) < 0)
	{
		book[i + 1] = book[i];
		i--;
	}
	book[i + 1].name = strdup(addname);
	book[i + 1].number = strdup(addnumber);
	book[i + 1].email = strdup(addemail);
	book[i + 1].group = strdup(addgroup);
	n++;

	printf("%s add is complete\n\n", addname);
}

void find(char* findname)
{
	int index = search(findname);
	if (index != -1)
	{
		printf("%s\n", book[index].name);
		printf("Number : %s\n",book[index].number);
		printf("Email : %s\n", book[index].email);
		printf("Group : %s\n", book[index].group);
		return;
	}
	printf("%s does not exist\n\n", findname);
}

void removedata(char* delname)
{
	int index = search(delname);
	if (index != -1)
	{
		while (index + 1 < n)
		{
			book[index] = book[index + 1];
			index++;
		}
		//memset(&book[index], NULL, sizeof(book[0]));
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
			printf("%s\n", book[i].name);
			printf("Number : %s\n", book[i].number);
			printf("Email : %s\n", book[i].email);
			printf("Group : %s\n", book[i].group);

			printf("==================================\n");
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
		add(name,number,email,group);
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
		fprintf(fp, "%s#%s#%s#%s#\n", book[i].name, book[i].number, book[i].email, book[i].group);
	}
	fclose(fp);
	printf("Save completed\n\n");
}


int main()
{
	line_command();

	return 0;
}