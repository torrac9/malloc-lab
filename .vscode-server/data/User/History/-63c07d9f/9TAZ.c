#include <stdio.h>

// int mytest(int a, int b)
// {
//     int result = a + b;
//     return result;
// }

int main()
{
    // int c;
    // c = mytest(10, 20);
    // printf("c = %d\n", c);

    // int x = 10;
    // int *p = &x;

    // printf("x = %d\n", x);
    // printf("&x = %p\n", &x);
    
    // printf("p = %p\n", p);
    // printf("*p = %d\n", *p);
    // printf("&p = %p\n", &p);

    // *p = 20;
    // printf("p = %d\n", *p);
    // printf("x = %d\n", x);
    // printf("&x = %p\n", &x);

    int x[5];
    int *p = x;

    printf("p = %d\n", *p);
    printf("x = %p\n", x);
    printf("&x[0] = %p\n", &x[0]);
    printf("p+0 = %p\n", p+0);
    printf("*p = %d\n", *p);

    return 0;
}