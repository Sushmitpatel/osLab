//Name =Sushmit patel     Reg No=20223282
#include<stdio.h>
#include<stdbool.h>

#define no_p 5 // Number of processes
#define no_i 3 // Number of resource types

int main() {
    // Arrays to store allocation, maximum, and request matrices
    int p_allocation[no_p][no_i];
    int p_req[no_p][no_i];
    int p_max[no_p][no_i];
    int avail[no_i]; // Available resources

    // Input allocation matrix
    for(int i = 0; i < no_p; i++) {
        for(int j = 0; j < no_i; j++) {
            scanf("%d", &p_allocation[i][j]);
        }
    }

    // Input maximum matrix
    for(int i = 0; i < no_p; i++) {
        for(int j = 0; j < no_i; j++) {
            scanf("%d", &p_max[i][j]);
        }
    }

    // Calculate request matrix
    for(int i = 0; i < no_p; i++) {
        for(int j = 0; j < no_i; j++) {
            p_req[i][j] = p_max[i][j] - p_allocation[i][j];
        }
    }

    // Input available resources
    for(int i = 0; i < no_i; i++) {
        scanf("%d", &avail[i]);
    }

    int sequence[no_p] = {0}; // Array to store the safe sequence
    int cnt = 1; // Counter for the safe sequence

    // Iterate through processes to find a safe sequence
    for(int i = 0; i < no_p; i++) {
        for(int j = 0; j < no_p; j++) {
            if(sequence[j] == 0) { // Check if process j is not yet in the safe sequence
                bool flag = true;
                // Check if the available resources can satisfy the request of process j
                for(int k = 0; k < no_i; k++) {
                    if(avail[k] < p_req[j][k]) {
                        flag = false;
                        break;
                    }
                }
                if(flag) { // If resources are available, add process j to the safe sequence
                    sequence[j] = cnt;
                    cnt++;
                    // Release resources allocated to process j
                    for(int k = 0; k < no_i; k++) {
                        avail[k] += p_allocation[j][k];
                    }
                }
            }
        }
    }

    // Check if a safe sequence exists
    for(int i = 0; i < no_p; i++) {
        if(sequence[i] == 0) {
            printf("No safe sequence\n");
            return 0;
        }
    }

    // Print the safe sequence
    for(int i = 0; i < no_p; i++) {
        printf("Process %d completed at step %d\n", i, sequence[i]);
    }

    return 0;
}
