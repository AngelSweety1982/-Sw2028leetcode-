#include <stdlib.h>

long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    long long ans = 0;
    long long cost = 0;
    
    // Deque stores indices of nums in a non-increasing order of their values
    int* dq = (int*)malloc(sizeof(int) * numsSize);
    int head = 0;
    int tail = 0;
    
    int j = numsSize - 1; // Right pointer of the sliding window
    
    // Slide the left pointer 'i' from right to left
    for (int i = numsSize - 1; i >= 0; i--) {
        int num = nums[i];
        
        // Maintain the monotonic decreasing nature from front to back
        while (head < tail && nums[dq[tail - 1]] < num) {
            int l = dq[tail - 1];
            tail--; // pop_back
            
            // If deque is empty, the range extends up to the right bound of the window
            int r = (head < tail) ? dq[tail - 1] : (j + 1);
            
            // Add the cost of raising all elements in range [l, r-1] up to 'num'
            cost += (long long)(r - l) * (num - nums[l]);
        }
        
        dq[tail++] = i; // push_back current index
        
        // If the cost exceeds k, shrink the window from the right side
        while (cost > k) {
            // Deduct the cost contribution of the element at index j
            // It was raised to the maximum element in the window, tracked by dq[head]
            cost -= (nums[dq[head]] - nums[j]);
            
            if (dq[head] == j) {
                head++; // pop_front if the maximum element is leaving the window
            }
            j--;
        }
        
        // Valid subarrays starting at 'i' can extend up to 'j'
        ans += (long long)(j - i + 1);
    }
    
    free(dq);
    return ans;
}
