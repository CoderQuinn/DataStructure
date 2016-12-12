#include <stdio.h>

void Move(int n, char start, char gogal, char temp)
{
    if (n == 0)
        return;
    Move(n-1, start, temp, gogal);
    printf("%c -> %c\n", start, gogal);
    Move(n-1, temp, gogal, start);
}

int main()
{
    int N;
    scanf("%d", &N);
    
    Move(N, 'a', 'c', 'b');
    
    return 0;
}