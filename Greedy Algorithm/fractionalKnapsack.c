#include <stdio.h>

#define MAX_ITEMS 5

int findIndex(double value[], int weight[], int n) {
    double max_value = -10000000.0;
    int max_index = -1;
    
    for (int i = 0; i < n; i++) {
        if (value[i] > max_value) {
            max_value = value[i];
            max_index = i;
        }
    }
    return max_index;
}

int main() {
    int weight[MAX_ITEMS] = {4, 8, 2, 6, 1};
    int benefit[MAX_ITEMS] = {12, 32, 40, 30, 50};
    double value[MAX_ITEMS];
    int maxweight = 10;
    double profit = 0.0;
    int w = 0;
    
    // Calculate value-to-weight ratio
    for (int i = 0; i < MAX_ITEMS; i++) {
        value[i] = (double) benefit[i] / weight[i];
    }
    
    while (w < maxweight) {
        int index = findIndex(value, weight, MAX_ITEMS);
        
        // Check if the current item can fully fit into the remaining capacity
        if (weight[index] > (maxweight - w)) {
            int fraction = maxweight - w;
            profit += value[index] * fraction;
            w = maxweight;  // Knapsack is full
        } else {
            w += weight[index];
            profit += benefit[index];  // Add full benefit of the item
        }
        
        // Mark this item as taken
        value[index] = -1.0;  // Invalidate the item
    }
    
    printf("Total profit: %.2f\n", profit);
    return 0;
}
