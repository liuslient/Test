#include<stdio.h>
#include<stdlib.h>

typedef struct StackNode
{
	int data;
	struct StackNode *next;
}StackNode;

StackNode *push(StackNode *stack,int h)
{
	StackNode *line=(StackNode*)malloc(sizeof(StackNode));
	line->data=h;
	line->next=stack;
	stack=line;
	return stack;
}

StackNode *pop(StackNode *stack)
{
        if(stack)
	{
	      StackNode *p=stack;
	      stack=stack->next;
	      printf("弹栈元素:%d",p->data);
	      if(stack)
	      {
	          printf("栈顶元素：%d\n",stack->data);
	      }
	      else
	      {
	          printf("无元素");
	      }
	      free(p);
	}
	else
	{
		printf("无元素");
		return stack;
	}
	return stack;
}

int main()
{
	StackNode *s=NULL;
	s=push(s,1);
	s=push(s,2);
	s=pop(s);
	return 0;
}
