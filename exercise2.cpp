#include <stdio.h>

int main(){
    int availableDigits;
    printf("Give number of digits: ");
    scanf("%d", &availableDigits);
    if(availableDigits == 0) printf("Invalid input specified. No number may be printed without any digits\n");
    if(availableDigits < 0) printf("Invalid input specified. No number may be printed with a negative number of digits\n");
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
            // Current cycle completed, precedingOnes should be decremented
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
                // If precedingOnes = 0, availableDigits must be zero and
                // num must be of the form xyz, where x is any number of any digits,
                // y is a digit > 0, and x is the digit 9. A "free" increment can thus
                // be performed, before quitting.
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
    printf("Last number possible to be printed: %d\n", num);
    return 0;
}