#include <stdio.h>

int digitCount;
char *str = new char[digitCount];

void print_nums(int digitIndx){
    if(digitIndx == digitCount) return;
    for(int i = 0; i < 2; i++){
        str[digitIndx] = '0' + i;
        print_nums(digitIndx + 1);
        if(digitIndx == digitCount - 1) printf(str);
    }
}

int main(){
    printf("Enter the number of digits in the number: ");
    scanf("%d", &digitCount);
    str[digitCount] = '\n';
    print_nums(0);
    delete str;
    return 0;
}