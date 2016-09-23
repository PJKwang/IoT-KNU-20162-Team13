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
	Node * head = NULL;    // NULL ������ �ʱ�ȭ
	Node * tail = NULL;
	Node * cur = NULL;
	int i=0,j=0;
	Node * newNode = NULL;
	char readData[30]; 
	char want[30];
	char ch;

	FILE * fp = fopen("asdf.txt","rt");



	/**** �����͸� �Է� �޴� ���� ****/
	while(feof(fp)==0)
	{
		ch = fgetc(fp);
		if (ch ==' ' || feof(fp)!=0 || ch == '\n')
		{
			readData[i] = '\0';
			i=0;

			/*** ����� �߰����� ***/
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





	/**** �Է� ���� �������� ��°��� ****/
	printf("�Է� ���� �������� ��ü���\n \n");
	if(head == NULL) 
	{
		printf("����� ���ڿ��� �����ϴ�. \n");
		i=0;
	}
	else 
	{
		cur = head; 
		printf("%s  ", cur->data);   // ù ��° ������ ���
		i=1;
		
		while(cur->next != NULL)    // �� ��° ������ ������ ���
		{
			cur = cur->next;
			printf("%s  ", cur->data);
			i++;
		}
	}


	printf("\n\n\n");
	//�� ������ ����
	printf("�� �ܾ� �� : %d��\n",i);
	printf("\n\n\n");





	//////���ϴ� �ܾ� �˻�
	printf("���ϴ� �ܾ� �Է� :\n");
	scanf("%s",want);
	printf("\n\n\n");
	i=0; j=0;
	if(head == NULL) 
	{
		printf("����� ���ڿ��� �������� �ʽ��ϴ�. \n");
		
	}
	else 
	{
		j++;
		cur = head; 
		if( strcmp(cur->data,want)==0)
		{
			printf("���ϴ� �ܾ��� �ε��� : %d\n",j-1);
			i++;
		}

		while(cur->next != NULL)    // �� ��° ������ ������ ���
		{
			j++;
			cur = cur->next;
			if( strcmp(cur->data,want)==0)
			{
			printf("���ϴ� �ܾ��� �ε��� : %d\n",j-1);
			i++;
			}
		}
		printf("\n");
	}
	printf("\n\n\n");
	printf("���ϴ� �ܾ� ���� : %d\n",i);
	return 0;
}