#include<stdio.h>
int fibonacci(int n){
    if(n == 0)
    return 0; //base case
    if(n == 1)
    return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);//hard case
}

int main() {
    int terms = 10; 
    printf("Fibonacci series: ");
    for (int i = 0; i < terms; ++i) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
    return 0;
}