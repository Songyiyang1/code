#include <stdio.h>
int main()
{
    int count = 0;
    int n = 0;
    scanf("%d", &n);
    while (n != 1)
    {
        if (n % 2)
            n = n * 3 + 1;
        else
            n /= 2;
        count++;
    }
    printf("%d", count);
    return 0;
}