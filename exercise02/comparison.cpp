#include <stdio.h>
#include <sys/time.h>
#include <bits/stdc++.h>

int betterWay(int availableDigits){
    // Identify cycle
    // Digits required d for cycle 10^x = (1 + (x-1)) * 10^(x-1)
    // For example: d for cycle 1000 (x = 3) = (1 + (3-1)) + 10^(3-1) = 300
    int cycle = -1;
    int m=1, c=1;
    int d, digitsRequired, count;
    while(m*c <= availableDigits){
        cycle = c;
        d = m * c;
        m *= 10;
        c++;
    }
    int maxCycle = cycle;
    int cycleMultiplier = m/10;
    int multiplier = m;
    int num = multiplier - 1;
    int precedingOnes = 1;
    availableDigits -= d;
    while(availableDigits > 0){
        // Phase 1: Check if cycle can be completed
        digitsRequired = cycle * cycleMultiplier + multiplier * precedingOnes;
        if(digitsRequired <= availableDigits){
            availableDigits -= digitsRequired;
            num = num + multiplier;
            // Cycle changed above value one, precedingOnes should be decremented
            precedingOnes--;
            // Phase 2: Check how many NEW cycles can be completed
            /* Since the equation
            cycle * cycleMultiplier + multiplier * precedingOnes
            is the same as the one used in phase 1, and only the parameter precedingOnes
            has changed, answers is multiplier * 1 smaller than the one in phase 1.
            */
            digitsRequired -= multiplier;
            count = availableDigits / digitsRequired;
            availableDigits -= count * digitsRequired;
            num = num + count * multiplier;

        }
        // Phase 3: Calculate inner cycle
        cycle = -1;
        m=1;
        c=1;
        multiplier = 10;
        while(c < maxCycle && m*c + multiplier * precedingOnes <= availableDigits){
            cycle = c;
            d = m * c + multiplier * precedingOnes;
            m *= 10;
            multiplier *= 10;
            c++;
        }
        if(cycle == -1){    // No inner cycle calculated
            if(precedingOnes == 0){
                num++;
                break;
            }
            count = availableDigits / precedingOnes;
            if(count > 1){
                availableDigits--;
                count = availableDigits / precedingOnes;
            }
            availableDigits -= count * precedingOnes;
            num += count;
            break;
        }
        maxCycle = cycle;
        precedingOnes++;
        availableDigits -= d;
        cycleMultiplier = m / 10;
        multiplier = m;
        num = num + multiplier;
    }
    //printf("Last number possible to be printed: %d\n", num);
    return num;
}

#define MAX_LENGTH 60
#define MAX_INDEX 59
int digitCount = 1;
int digits[MAX_LENGTH];

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

int oldWay(int digitsAvailable){
    digitCount = 1;
    // Initialize digits array
    for(int i = 0; i < MAX_LENGTH; i++){
        digits[i] = -1;
    }
    digits[MAX_INDEX] = 1;
    // Initialize digitsRequired array
    int digitsRequired[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // Main loop
    int digit, digitsUsed = 0;
    for(int i = 0; digitsUsed <= digitsAvailable; i++){
        for(int j = 0; j < digitCount; j++){
            digit = digits[MAX_INDEX-j];
            digitsRequired[digit]++;
        }
        for(int j = 0; j < 10; j++){
            if(digitsRequired[j] > digitsUsed) digitsUsed = digitsRequired[j];
        }
        if(digitsUsed <= digitsAvailable) incrementNum(digits, MAX_INDEX);
    }
    int num = 0;
    int multiplier = 1;
    for(int i = 0; i < digitCount; i++){
        digit = digits[MAX_INDEX-i];
        num += digit * multiplier;
        multiplier *= 10;
    }
    num -= 1;
    return num;
}

int main(){
    int availableDigits;
    /*printf("Give number of digits: ");
    scanf("%d", &availableDigits);
    if(availableDigits == 0) printf("Invalid input specified. No number may be printed without any digits\n");
    if(availableDigits < 0) printf("Invalid input specified. No number may be printed with a negative number of digits\n");
    */
    std::ios_base::sync_with_stdio(false);
    timespec start1, start2, end1, end2, res;
    double duration1, duration2, peak1=-1, peak2=-1, pit1=-1, pit2=-1;
    clock_getres(CLOCK_MONOTONIC, &res);
    printf("res.tv_sec: %10ld\n", res.tv_sec);
    printf("res.tv_nsec: %09ld\n", res.tv_nsec);
    printf("res: %10ld.%09ld\n", res.tv_sec, res.tv_nsec);
    //struct timespec 
    #define TEST_COUNT 9999
    for(availableDigits = 1; availableDigits <= TEST_COUNT; availableDigits++){
        clock_gettime(CLOCK_MONOTONIC, &start1);
        int num = betterWay(availableDigits);
        clock_gettime(CLOCK_MONOTONIC, &end1);
        clock_gettime(CLOCK_MONOTONIC, &start2);
        int num2 = oldWay(availableDigits);
        clock_gettime(CLOCK_MONOTONIC, &end2);


        start1.tv_nsec *= res.tv_nsec;
        start2.tv_nsec *= res.tv_nsec;
        end1.tv_nsec *= res.tv_nsec;
        end2.tv_nsec *= res.tv_nsec;
        double us1 = ((double) (end1.tv_nsec - start1.tv_nsec)) / 1000;
        double us2 = ((double) (end2.tv_nsec - start2.tv_nsec)) / 1000;
        printf("%d. Faster algorithm duration: %015lf us\n", availableDigits, us1);
        printf("%d. Slower algorithm duration: %015lf us\n", availableDigits, us2);
        //if(us1 >= 0){
            if(peak1 == -1 || us1 > peak1) peak1 = us1;
            if(pit1 == -1 || us1 < pit1) pit1 = us1;
            duration1 += us1;
        //}
        //if(us2 >= 0){
            if(peak2 == -1 || us2 > peak2) peak2 = us2;
            if(pit2 == -1 || us2 < pit2) pit2 = us2;
            duration2 += us2;
        //}
        if(num == num2){
            //printf("Working\n");
            //printf("betterWay(%d): %d\n", availableDigits, num);
        }
        else {
            printf("Digit count: %d\n", availableDigits);
            printf("Not working\n");
            printf("betterWay(%d): %d\n", availableDigits, num);
            printf("oldWay(%d): %d\n", availableDigits, num2);
            break;
        }
    }
    duration1 /= TEST_COUNT;
    duration2 /= TEST_COUNT;
    printf("\nFaster algorithm duration statistics:\n");
    printf("Average duration: %015lf us\n", duration1);
    printf("Peak duration: %015lf us\n", peak1);
    printf("Pit duration: %015lf us\n", pit1);
    
    printf("\nSlower algorithm duration statistics:\n");
    printf("Average duration: %015lf us\n", duration2);
    printf("Peak duration: %015lf us\n", peak2);
    printf("Pit duration: %015lf us\n", pit2);
    
    printf("\n");
    printf("Difference: %015lf us\n", duration2 - duration1);
    printf("Relation: %015lf\n", duration2 / duration1);
    return 0;
}