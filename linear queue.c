#include<stdio.h>  
#define MAXSIZE 5  
int queue[MAXSIZE];
int front = 0, rear = -1;
  int isempty()
{
if(rear == -1)
return 1;
else
return 0;
}
int isfull()
{
if(rear == MAXSIZE - 1)
return 1;
else
return 0;
}
void enqueue(int data)
{
if(isfull())
printf("Queue is full.\n");
else
{
rear++;
queue[rear] = data;
}
}
void dequeue()
{
		int data, i, temp = 0;
		data = queue[front];
		if(isempty())
			    	printf("Queue is empty.\n");
		else {
				for(i=front+1;i<=rear;i++)
                {
                    if(data > queue[i])
                    {
                        temp = i;
                        data = queue[i];
                    }
                }
                for(i=temp; i<rear; i++)
                {
                    queue[i] = queue[i+1];
                }

 rear--;
                printf("Dequeuedelements:%d\n",data);
		}
}
void peek()
{
		if(isempty())
			printf("Queue is empty.\n");
		else
			printf("Element at front:%d\n", queue[front]);
}

void display()
{
		if(isempty())
			printf("Queue is empty.\n");
		else
		{
			for (int i = front; i <= rear; i++)
				printf("%d\t", queue[i]);
		}
}
int main()
{
	enqueue(3);
	enqueue(5);
	enqueue(9);
	enqueue(12);
	enqueue(1);
	peek();
	dequeue();
	dequeue();
	display();
	return 0;
}
