#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DIGIT_SUFFIX_COUNT 5

struct digitSuffix {
    int minDigitIndx;
    const char *suffix;
    const char *suffix2;
};

struct digitSuffix digitSuffixes[DIGIT_SUFFIX_COUNT];
const char *digitNames[9] = {"yksi", "kaksi", "kolme", "neljä", "viisi", "kuusi", "seitsemän", "kahdeksan",  "yhdeksän"};
int *digits;

void printNum(int start, int currentDigitSuffix, int digitCount){
    int digitIndx, j;
    for(int i = start; i - start < digitCount; i++){
        digitIndx = (digitCount - 1) - (i - start);
        if(digits[i] > 0){
            if(currentDigitSuffix < DIGIT_SUFFIX_COUNT && digitIndx > digitSuffixes[currentDigitSuffix].minDigitIndx){
                for(j = 1; digitIndx - j >= digitSuffixes[currentDigitSuffix].minDigitIndx; j++);
                j--;
                printNum(i, DIGIT_SUFFIX_COUNT - j, j + 1);
                printf(digitSuffixes[currentDigitSuffix].suffix);
                i += j;
                currentDigitSuffix++;
                continue;
            }
            if(digits[i] == 1){
                if(digitIndx == 1 && digits[i + 1] > 0){
                    printf("%stoista", digitNames[digits[i+1] - 1]);
                    break;
                }
                if(currentDigitSuffix < DIGIT_SUFFIX_COUNT)
                    printf(digitSuffixes[currentDigitSuffix].suffix2);
                else
                    printf("%s", digitNames[digits[i] - 1]);
            }
            else {
                printf("%s", digitNames[digits[i] - 1]);
                if(currentDigitSuffix < DIGIT_SUFFIX_COUNT)
                    printf("%s", digitSuffixes[currentDigitSuffix].suffix);
            }
        }
        if(currentDigitSuffix < DIGIT_SUFFIX_COUNT - 1){
            if(digitIndx - 1 < digitSuffixes[currentDigitSuffix].minDigitIndx)
                currentDigitSuffix++;
        }
        else
            currentDigitSuffix = DIGIT_SUFFIX_COUNT;
    }
}

int main(){
    digitSuffixes[0] = {9, "miljardia", "miljardi"};
    digitSuffixes[1] = {6, "miljoonaa", "miljoona"};
    digitSuffixes[2] = {3, "tuhatta"  , "tuhat"   };
    digitSuffixes[3] = {2, "sataa"    , "sata"    };
    digitSuffixes[4] = {1, "kymmentä" , "kymmenen"};
    int num, i, digitCount, currentDigitSuffix;
    printf("Enter the number to be printed in the range 1 - 1B: ");
    scanf("%d", &num);
    if(num < 0){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    if(num > 1000000000){
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    digitCount = floor(log10(num) + 1);
    digits = new int[digitCount];
    // Find all digits of the number
    for(i = 0; i < digitCount; i++){
        digits[(digitCount - 1) - i] = num % 10;
        num /= 10;
    }
    // Find digit suffix for rightmost digit
    currentDigitSuffix = DIGIT_SUFFIX_COUNT;
    for(i = DIGIT_SUFFIX_COUNT - 1; i >= 0; i--){
        if(digitCount - 1 >= digitSuffixes[i].minDigitIndx)
            currentDigitSuffix = i;
    }
    printNum(0, currentDigitSuffix, digitCount);
    printf("\n");
    return 0;
}