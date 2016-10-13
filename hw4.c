#include <stdio.h>
#include<stdlib.h>

int a, b;
int max, min;// max =���� ū ����, min =���� ���� ����
typedef struct node//���׽� ù��°����Ʈ
{
	int coef;
	int expo;
	struct node *link;
}node;

typedef struct secondnode//���׽� ���������Ʈ
{
	int coef;
	int expo;
	struct secondnode *link1;
}secondnode;

typedef struct list
{
	node *headnode;
}list;

typedef struct secondlist
{
	secondnode *headnode2;
}secondlist;

list * nullnode(void)
{
	list *re;
	re = (list*)malloc(sizeof(list));
	re->headnode = NULL;
	return re;
};
secondlist * nullnode2(void)
{
	secondlist *re;
	re = (secondlist*)malloc(sizeof(secondlist));
	re->headnode2 = NULL;
	return re;
};
void scan(FILE *input_fp, FILE *output_fp, list **list1);//���Է� �Լ�
void print(list **list);//������ ����Լ�
void insert(list **list1);// fscanf�� ������ ����ؼ� ����Ʈ ������ ���ÿ� ���� �־��ִ� �Լ�
void calculate(list **list, secondlist **secondlist);//��� ���׽��� �����Ͽ� ����� ���ϴ� �Լ�
void final(secondlist **secondlist, int a, int b);//����� ���� ���׽��� ����� ����Ʈ
void print2(FILE *input_fp, FILE *output_fp, secondlist **secondlist);//���׽� ��¸���Ʈ

int main()
{
	FILE *input_fp, *output_fp;
	input_fp = fopen("hw4.inp", "r");
	output_fp = fopen("hw4.out", "w");

	list *list = nullnode();//���׽� ù��° ����忡 ���鸮��Ʈ ȣ��
	secondlist *list2 = nullnode2();//���׽� �ι�° ����忡 ���鸮��Ʈ ȣ��
	scan(input_fp,output_fp,&list);
	calculate(&list,&list2);
	print(&list);
	print2(input_fp, output_fp, &list2);

	fclose(input_fp);
	fclose(output_fp);
	//free(list);

	/*while (headnode != NULL)
	{
	while (head)
	}*/
}

void scan(FILE *input_fp,FILE *output_fp,list **list1)//���Է�
{
	char temp = 0;
	int temp1 = 1;

	for (;;)
	{
		fscanf(input_fp, "%c", &temp);
		if (temp == '+')
		{
			temp1 = 1;
			fscanf(input_fp, "\n");
		}
		else if (temp == '-')
		{
			temp1 = -1;
			fscanf(input_fp, "\n");
		}
		else if (temp == '*')
		{
			break;
		}
		else
		{
			fscanf(input_fp, "%d,%d]\n", &a, &b);
			a = temp1*a;
			insert(list1);
		}
	}

}

void insert(list **list)//����Ʈ ���� and �� ȣ���Լ�
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->link = NULL;
	newnode->coef = a;
	newnode->expo = b;
	node *temp = (*list)->headnode;
	if ((*list)->headnode == NULL) //����尡 ������ �˻�
	{
		(*list)->headnode = newnode;//���̸� ��� �ʱ�ȭ
	}
	else
	{
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = newnode;
	}
}

void print(list **list)//����Ʈ ���� and �� ȣ���Լ�
{
	node * temp = (*list)->headnode;

	while (1)
	{
		//printf("[%d, %d]\n", temp->coef, temp->expo);
		if (temp->link == NULL)
			break;
		temp = temp ->link;
	}
	//printf("*\n");
}

void calculate(list **list, secondlist **secondlist)
{
	max = 0, min = 100;
	int i;
	int co=0;//������ �޴� ����

	node * temp = (*list)->headnode;

	while (1)//�ִ� �ּ� ���� ���ϴ� �ݺ��� 
	{
		if (max < temp->expo)
		{
			max = temp->expo;
		}
		else
		{
			if (min > temp->expo)
			{
				min = temp->expo;
			}
		}

		if (temp->link == NULL)
			break;
		temp = temp->link;
	}

	for (i = max; i >= min; i--)
	{
		temp = (*list)->headnode;
		while (1)
		{
			if (temp->expo == i)
			{
				co += temp->coef;
			}
			if (temp->link == NULL)
				break;
			temp = temp->link;
		}
		final(secondlist,co,i);
		co = 0;

	}

}

void final(secondlist **secondlist,int a,int b)//��갪�� ����ִ� �Լ�
{
	secondnode *newnode = (secondnode*)malloc(sizeof(secondnode));
	newnode->link1 = NULL;
	newnode->coef = a;
	newnode->expo = b;
	secondnode *temp = (*secondlist)->headnode2;
	if ((*secondlist)->headnode2 == NULL) //����尡 ������ �˻�
	{
		(*secondlist)->headnode2 = newnode;//���̸� ��� �ʱ�ȭ
	}
	else
	{
		while (temp->link1 != NULL)
		{
			temp = temp->link1;
		}
		temp->link1 = newnode;
	}

}

void print2(FILE *input_fp, FILE *output_fp, secondlist **secondlist)//����Ʈ ���� and �� ȣ���Լ�
{
	secondnode * temp = (*secondlist)->headnode2;

	while (1)
	{
		if (temp->coef != 0)
			fprintf(output_fp,"[%d,%d]\n", temp->coef, temp->expo);
		if (temp->link1 == NULL)
			break;
		temp = temp->link1;
	}
	fprintf(output_fp,"*\n");
}