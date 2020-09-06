#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
#define MAX 100

typedef struct Stack
{
	DataType data[MAX];
	int top;
}Stack;

void InitStack(Stack *s)   //初始化
{
	if(NULL==s)
	{
		return;
	}
	s->top=(Stack*)malloc(sizeof(Stack));
	s->top=0;
}
void StackPush(Stack *s,DataType h)
{
	if(NULL==s)
	{
		printf("栈空");
		return;
	}
	s->data[s->top]=h;
	++s->top;
}

void StackPop(Stack *s)
{
	if(NULL==s)
	{
		printf("jieshuu");
		return;
	}
	if(s->top==0)
	{
		printf("jieshu");
		return;
	}
	s->top--;
}

void Stackprint(Stack *s)
{
	int i=0;
	if(NULL==s)
	{
		printf("无元素");
		return;
	}
	while(i<s->top)
	{
		printf("%d ",s->data[i]);
		i++;
	}
	printf("\n");
	
}

int main()
{
	Stack s;
	InitStack(&s);
	StackPush(&s,2);
	StackPush(&s,5);
	Stackprint(&s);
	StackPop(&s);
	Stackprint(&s);
}
