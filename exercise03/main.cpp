/*
Layer count     Size
    3            5 

    4            7

Function to get size from layer count: f(x) = 2x - 1

Layer index     Layer contents      A area      B area         C area
    0               AAAAA            0:3         0:0            0:0
    1               ABBBA            0:1         1:2            0:0
    2               ABCBA            0:1         1:1            2:1
    3               ABBBA            0:1         1:2            0:0
    4               AAAAA            0:3         0:0            0:0

*/
#include <stdio.h>

int main(){
    int layerCount;
    printf("Enter the number of layers in the square: ");
    scanf("%d", &layerCount);
    const int size = 2 * layerCount - 1;
    for(int i = 0; i < size; i++){
        int rowIndex = i;
        if(i >= layerCount) rowIndex = size - 1 - i;
        for(int j = 0; j < size; j++){
            int columnIndex = j;
            if(j >= layerCount) columnIndex = size - 1 - j;
            if(rowIndex > columnIndex) printf("%c", 'A' + columnIndex);
            else printf("%c", 'A' + rowIndex);
        }
        printf("\n");
    }
    return 0;
}