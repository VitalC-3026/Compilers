#include <stdio.h>

int n = 0;

int factorial(int n)
{
    int i = 2;
    int f = 1;
    while(i <= n) {
        f = f * i;
        i = i + 1;
    }
    return f;
}

int main(){
    scanf("%d", &n);
    printf("factorial is: %d\n", factorial(n));
}