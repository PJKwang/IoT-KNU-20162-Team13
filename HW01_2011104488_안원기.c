#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node
{
	char data[30];
	struct _node * next;
} Node;

int main(void)
{
	Node * head = NULL;    // NULL 포인터 초기화
	Node * tail = NULL;
	Node * cur = NULL;
	int i=0,j=0;
	Node * newNode = NULL;
	char readData[30]; 
	char want[30];
	char ch;

	FILE * fp = fopen("asdf.txt","rt");



	/**** 데이터를 입력 받는 과정 ****/
	while(feof(fp)==0)
	{
		ch = fgetc(fp);
		if (ch ==' ' || feof(fp)!=0 || ch == '\n')
		{
			readData[i] = '\0';
			i=0;

			/*** 노드의 추가과정 ***/
		newNode = (Node*)malloc(sizeof(Node));
		
		strcpy(newNode->data,readData);
		newNode->data[strlen(readData)+1] = '\0';
		newNode->next = NULL;

		if(head == NULL)
		{head = newNode;}
		else
		{tail->next = newNode;}
		tail = newNode;
			continue;

		}
		else
		{
			readData[i] = ch;
			i++;
		}
	}
	printf("\n\n");
	fclose(fp);





	/**** 입력 받은 데이터의 출력과정 ****/
	printf("입력 받은 데이터의 전체출력\n \n");
	if(head == NULL) 
	{
		printf("저장된 문자열이 없습니다. \n");
		i=0;
	}
	else 
	{
		cur = head; 
		printf("%s  ", cur->data);   // 첫 번째 데이터 출력
		i=1;
		
		while(cur->next != NULL)    // 두 번째 이후의 데이터 출력
		{
			cur = cur->next;
			printf("%s  ", cur->data);
			i++;
		}
	}


	printf("\n\n\n");
	//총 데이터 갯수
	printf("총 단어 수 : %d개\n",i);
	printf("\n\n\n");





	//////원하는 단어 검색
	printf("원하는 단어 입력 :\n");
	scanf("%s",want);
	printf("\n\n\n");
	i=0; j=0;
	if(head == NULL) 
	{
		printf("저장된 문자열이 존재하지 않습니다. \n");
		
	}
	else 
	{
		j++;
		cur = head; 
		if( strcmp(cur->data,want)==0)
		{
			printf("원하는 단어의 인덱스 : %d\n",j-1);
			i++;
		}

		while(cur->next != NULL)    // 두 번째 이후의 데이터 출력
		{
			j++;
			cur = cur->next;
			if( strcmp(cur->data,want)==0)
			{
			printf("원하는 단어의 인덱스 : %d\n",j-1);
			i++;
			}
		}
		printf("\n");
	}
	printf("\n\n\n");
	printf("원하는 단어 갯수 : %d\n",i);
	return 0;
}