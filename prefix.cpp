#include <stdio.h>  
#include <ctype.h>
#define MAXSIZE 10

int stack[MAXSIZE];  
int top = -1;

int isempty() {
    return top == -1;
}

int isfull() {
    return top == MAXSIZE - 1;
}

void push(int data) {
    if (isfull())
        printf("Stack is full.\n");
    else
        stack[++top] = data;
}

int pop() {
    if (isempty()) {
        printf("Stack is empty.\n");
        return -1;
    } else {
        return stack[top--];
    }
}

int evaluatePrefix(char* expr) {
    for (int i = MAXSIZE - 1; i >= 0; i--) {
        if (expr[i] == '\0') continue;
        
        if (isdigit(expr[i])) {
            push(expr[i] - '0');
        } else {
            int op1 = pop();
            int op2 = pop();
            
            switch (expr[i]) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/': push(op1 / op2); break;
            }
        }
    }
    return pop();
}

int main() {
    char expr[MAXSIZE];
    printf("Enter prefix expression: ");
    fgets(expr, MAXSIZE, stdin);
    int result = evaluatePrefix(expr);
    printf("Result: %d\n", result);
    return 0;
} 
