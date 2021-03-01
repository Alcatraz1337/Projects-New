#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    int x, y;
}player;


int main(){
    player p1, p2;
    p1.x = 1;
    p1.y = 2;
    p2.x = 3;
    p2.y = 4;
    p2 = p1;
    printf("P2x = %d, P2y = %d", p2.x, p2.y);
    return 0;
}