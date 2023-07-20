#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_ITEM_COUNT 128
#define MAX_NAME_LENGTH 127


//Get max between two values
int cmpMax(int a, int b) {
    int max;
    if(a > b) { max = a; }
    else { max = b; }
    return max;
}


int main(int argc, char const *argv[]) {    

    //Start timer
    clock_t start = clock(); 

    char name[MAX_ITEM_COUNT][MAX_NAME_LENGTH];
    char inputName[MAX_NAME_LENGTH];
    int weight[MAX_ITEM_COUNT];
    int value[MAX_ITEM_COUNT];
    int capacity;
    
    //Take loot information from stdin
    scanf("%d", &capacity);
    int array[MAX_ITEM_COUNT + 1][capacity + 1];

    /* Reads until EOF. \n skips line breaks before taking input */
    int i = 0;
    while(scanf("\n%[^;];%d;%d", inputName, &weight[i], &value[i]) != EOF) {
        strcpy(name[i], inputName); //Move temp value to actual name array
        i++;
    }

       // Find max value
    // Considering all items and weight combinations
    for(int row = 0; row <= MAX_ITEM_COUNT; row++) { 
        for(int col = 0; col <= capacity; col++) { 
            if(row == 0 || col == 0) { //If # of items or weight is 0
                array[row][col] = 0; 
            }
            else if(weight[row - 1] <= col) { // check whether weight of item exceeds current capacity
                // 1. Consider including(left param) or excluding(right param) item
                // 2. Assign greater value (found via cmpMax)
                array[row][col] = cmpMax(value[row - 1] + array[row - 1][col - weight[row - 1]], array[row - 1][col]);
            }
            else { 
                array[row][col] = array[row - 1][col]; 
            }
        }
    }
    int finalValue = array[MAX_ITEM_COUNT][capacity];

    int tempFV = finalValue;
    int tempCap = capacity;
    int tempWeight[MAX_ITEM_COUNT];
    int tempValue[MAX_ITEM_COUNT];
    char tempName[MAX_ITEM_COUNT][MAX_NAME_LENGTH];

    // Get matching name, weight, and values for printing
    for(int n = MAX_ITEM_COUNT; n > 0 && tempFV > 0; n--) {
        if(tempFV == array[n-1][tempCap]) {
            continue;
        }
        else {
            tempWeight[n] = weight[n-1];
            tempValue[n] = value[n-1];
            strcpy(tempName[n-1], name[n-1]);
            
            //Subtract value and weight because item is part of optimal list
            tempFV = tempFV - value[n-1];
            tempCap = tempCap - weight[n-1];
        }
    }

    //Print matching information
    int finalWeight = 0;
    for(int n = 0; n < MAX_ITEM_COUNT; n++) {
        if(tempWeight[n] > 0) {
            finalWeight += tempWeight[n];
            printf("%s, %d, %d\n", tempName[n-1], tempWeight[n], tempValue[n]);
        }
    }

    printf("final weight: %d\n", finalWeight);
    printf("final value: %d\n", finalValue);
    
    //End timer
    double time_taken_in_seconds = (double)( clock() - start ) / CLOCKS_PER_SEC;
    double time_taken_in_microseconds = time_taken_in_seconds * 1000000.0;
    printf("time taken in microseconds: %f\n", time_taken_in_microseconds);
    return 0;
}