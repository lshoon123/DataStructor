#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	char mark;
	struct node *link;
}node;

typedef struct list
{
	struct node *headnode;
}list;

list *nullnode(void)
{
	list *re;
	re = (list*)malloc(sizeof(list));
	re->headnode = NULL;
	return re;
};
void scan(FILE *input_fp, FILE *output_fp, list *list1, list *list2);//숫자를 받는 함수
void push(list *list1, char mark);//push한다.
char pop(list *list1);//pop한다.
void allpop(list *list1, list *list2, FILE *output_fp);//allpop한다.
void allpop2(list *list1, list *list2, FILE *output_fp);
void reverse(list *list1, list *list2);//스텍을 거꾸로 쌓는 함수
void calculate(list *list1, list *list2, FILE *output_fp);

int main()
{
	FILE *input_fp, *output_fp;
	input_fp = fopen("hw5.inp", "r");
	output_fp = fopen("hw5.out", "w");

	list *list1 = nullnode();
	list *list2 = nullnode();
	scan(input_fp, output_fp, list1,list2);
	fprintf(output_fp, "*");

	fclose(input_fp);
	fclose(output_fp);
}


void scan(FILE *input_fp, FILE *output_fp, list *list1,list *list2)
{
	char b = ' ';
	int check = 0;
		while (1)
		{
			fscanf(input_fp, "%c", &b);
			if (check == 1)
			{
				if (b == '*')
				{
					break;
				}
				else
				{
					check = 0;
				}
			}
			if (b == '*' || b == '/')
			{
				if (list1->headnode == NULL)//공백리스트일때
				{
					push(list1, b);
				}
				else//공백리스트가 아닐때
				{
					if (list1->headnode->mark == '+' || list1->headnode->mark == '-' || list1->headnode->mark == '(')
					{
						push(list1, b);
					}
					else if (list1->headnode->mark == '*' || list1->headnode->mark == '/')
					{
						allpop2(list1,list2,output_fp);
						push(list1, b);
					}
				}
			}
			else if (b == '+' || b == '-')
			{
				if (list1->headnode == NULL)//공백리스트일때
				{
					push(list1, b);
				}
				else//공백리스트가 아닐때
				{
					if (list1->headnode->mark == '(') 
					{
						push(list1, b);
					}
					else if (list1->headnode->mark == '*' || list1->headnode->mark == '/' || list1->headnode->mark == '+' || list1->headnode->mark == '-')
					{
						allpop(list1,list2, output_fp);
						push(list1, b);
					}
				}
			}
			else if (b == '(')
			{
				push(list1, b);
			}
			else if (b == ')')
			{
				allpop(list1,list2, output_fp);
				pop(list1);
			}
			else if (b == '\n')//줄이 바뀌면 계산하고 값을 출력 한다.
			{
				allpop(list1,list2, output_fp);
				fprintf(output_fp,"\n");
				push(list2, '#');
				reverse(list1, list2);
				calculate(list1, list2,output_fp);
				check = 1;
			}
			else//숫자일때
			{
				fprintf(output_fp, "%c", b);
				push(list2, b);
			}
		}		
	}

void push(list *list1,char mark)
{
	node *newnode = (node*)malloc(sizeof(node));
	newnode->link = list1->headnode;
	newnode->mark = mark;
	list1->headnode = newnode;
}

char pop(list *list1)
{
	char top;
	node *header = list1->headnode;
	if (list1->headnode == NULL)
	{
	}
	else
	{
		top = header->mark;
		list1->headnode = header->link;
		free(header);
		return top;
	}
}

void allpop(list *list1,list *list2, FILE *output_fp)
{
	while (1)
	{
		if (list1->headnode == NULL)
		{
			break;
		}
		else
		{
			char ch = pop(list1);
			if (ch == '(')
			{
				push(list1,ch);
				break;
			}
			else
			{
				fprintf(output_fp,"%c",ch);
				push(list2, ch);
			}
		}
	}
}
void allpop2(list *list1, list *list2, FILE *output_fp)
{
	while (1)
	{
		if (list1->headnode == NULL)
		{
			break;
		}
		else
		{
			char ch = pop(list1);
			if (ch == '(')
			{
				push(list1, ch);
				break;
			}
			else if (ch == '+' || ch == '-')
			{
				push(list1, ch);
				break;
			}
			else
			{
				fprintf(output_fp, "%c", ch);
				push(list2, ch);
			}
		}
	}
}


void reverse(list *list1, list *list2)
{
	char a;
	for (;;)
	{
		a = pop(list2);
		push(list1, a);
		if (list2->headnode->link == NULL)
		{
			a = pop(list2);
			push(list1, a);
			break;
		}
	}
}

void calculate(list *list1, list *list2,FILE *output_fp)
{
	int a, b,c, value;
	int answer;
	char temp;
	char temp1;
	while (1)
	{
		temp = pop(list1);
		if (temp != '*' && temp != '/' && temp != '+' && temp != '-' && temp != '#')
		{
			push(list2, temp);
		}

		else if (temp == '#')
		{
			answer = pop(list2) - '0';
			fprintf(output_fp, "%d\n", answer);
			break;
		}
		else
		{
			b = pop(list2)-'0';
			a = pop(list2)-'0';
			switch (temp)
			{
			case '+': 
				c =a + b;
				push(list2, c+'0');
				break;
			case '-': 
				c = a - b;
				push(list2, c+'0');
				break;
			case '*': 
				c = a * b;
				push(list2, c+'0');
				break;
			case '/': 
				c = a / b;
				push(list2, c+'0');
				break;
			}
		}
	}
}