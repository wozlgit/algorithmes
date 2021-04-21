#include <stdio.h>

/*
Anna luku: 5
1 5 2 4 3

Anna luku: 8
1 8 2 7 3 6 4 5

Anna luku: 9
1 9 2 8 3 7 4 6 5

Number | Result
5      | 1 5 2 4 3
8      | 1 8 2 7 3 6 4 5
9      | 1 9 2 8 3 7 4 6 5

Stop condition: same number would be printed twice,
i.e. counter+1 == num
counter = counter + 1
num = num - 1
 = counter == num + 1
*/

int main(){
    // Number printing loop should stop before the same number gets printed twice?
    int inputNum;
    printf("Give a number: ");
    scanf("%d", &inputNum);
    int num = inputNum;
    for(int counter = 1; counter != num + 1; ++counter){    // Last number printed was num + 1, next number printed is counter
        printf("%d ", counter);
        if(num == counter) break;   // Last number printed was counter, next is num
        printf("%d ", num);
        --num;
    }
    printf("\n");
    return 0;
}