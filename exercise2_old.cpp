#include <stdio.h>

/*
Esimerkki 1

numeroita: 5
Vastaus: 12

Esimerkki 2

numeroita: 1000
Vastaus: 1499
*/

/*

0-9: 1
<precedingDigits>x
x0-x9

digitCount  start   end
1           2       2
2           1       2
3           0       2

start = 3 - digitCount
end = 2

num     0   1   2   3   4   5   6   7   8   9
1           1
2           1   1
3           1   1   1
4           1   1   1   1
5           1   1   1   1   1
6           1   1   1   1   1   1
7           1   1   1   1   1   1   1
8           1   1   1   1   1   1   1   1
9           1   1   1   1   1   1   1   1   1
10      1   2   1   1   1   1   1   1   1   1
11      1   4   1   1   1   1   1   1   1   1
12      1   5   2   1   1   1   1   1   1   1
13      1   6   2   2   1   1   1   1   1   1
14      1   7   2   2   2   1   1   1   1   1
15      1   8   2   2   2   2   1   1   1   1
16      1   9   2   2   2   2   2   1   1   1
17      1   10   2   2   2   2   2   2   1   1
18      1   11  2   2   2   2   2   2   2   1
19      1   12  2   2   2   2   2   2   2   2
20      2   12  3   2   2   2   2   2   2   2

10      1   1   0   0   0   0   0   0   0   0
11      0   2   0   0   0   0   0   0   0   0
12      0   1   1   0   0   0   0   0   0   0
13      0   1   0   1   0   0   0   0   0   0
14      0   1   0   0   1   0   0   0   0   0
15      0   1   0   0   0   1   0   0   0   0
16      0   1   0   0   0   0   1   0   0   0
17      0   1   0   0   0   0   0   1   0   0
18      0   1   0   0   0   0   0   0   1   0
19      0   1   0   0   0   0   0   0   0   1

9*1 + 1*2 = 9 + 2 = 11

20      1   0  1   0   0   0   0   0   0   0

<d><0-9> will take 11 of digits d
<d><0-9><0-9>
*/

#define MAX_LENGTH 60
#define MAX_INDEX 59
int digitCount = 1;

/**
 * Increment the number stored in the array digits
 * @param digits - The array of digits comprising the number
 * @param maxIndex - The maximum index of the digits array
 */
void incrementNum(int digits[], int maxIndex){
    digits[maxIndex]++;
    if(digits[maxIndex] == 10){
        digits[maxIndex] = 0;
        if(digits[maxIndex-1] == -1){
            digits[maxIndex-1] = 0;
            digitCount++;
        }
        incrementNum(digits, maxIndex-1);
    }
}

int main(){
    int inputNum;
    printf("Give a number: ");
    scanf("%d", &inputNum);
    int digits[MAX_LENGTH];
    // Initialize digits array
    for(int i = 0; i < MAX_LENGTH; i++){
        digits[i] = -1;
    }
    digits[MAX_INDEX] = 1;
    // Initialize digitsRequired array
    int digitsRequired[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i = 0; i < inputNum-1; i++){
        for(int j = 0; j < digitCount; j++){
            digitsRequired[digits[MAX_INDEX-j]]++;
        }
        /*for(int j = MAX_LENGTH - digitCount; j < MAX_LENGTH; j++){
            printf("%d", digits[j]);
        }
        printf("\n");*/
        incrementNum(digits, MAX_INDEX);
    }
    for(int j = 0; j < digitCount; j++){
        digitsRequired[digits[MAX_INDEX-j]]++;
    }
    /*for(int j = MAX_LENGTH - digitCount; j < MAX_LENGTH; j++){
        printf("%d", digits[j]);
    }
    printf("\n");*/
    for(int i = 0; i < 10; i++){
        printf("%d number of %d digits required to print contiguos positive integers 1-%d\n", digitsRequired[i], i, inputNum);
    }
    return 0;
}