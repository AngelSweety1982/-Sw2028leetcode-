#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    // Total number of sliding windows
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    
    // Deque to store indices of array elements
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int head = 0; // Front of the deque
    int tail = 0; // Back of the deque (exclusive pointer)
    
    int resultIdx = 0;
    
    for (int i = 0; i < numsSize; i++) {
        // 1. Remove indices that are out of the current window bounds
        if (head < tail && deque[head] < i - k + 1) {
            head++;
        }
        
        // 2. Maintain monotonic decreasing property: 
        // Remove smaller elements from the back because they can't be the maximum anymore
        while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }
        
        // 3. Add the current element's index to the back of the deque
        deque[tail++] = i;
        
        // 4. The front of the deque is the index of the largest element for the current window
        if (i >= k - 1) {
            result[resultIdx++] = nums[deque[head]];
        }
    }
    
    // Clean up allocated memory for the temporary deque
    free(deque);
    
    return result;
}
