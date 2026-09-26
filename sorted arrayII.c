#include <stdbool.h>

bool search(int* nums, int numsSize, int target) {
    if (numsSize == 0) return false;

    int low = 0;
    int high = numsSize - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // If target is found, return true
        if (nums[mid] == target) {
            return true;
        }

        // Edge Case: Handle duplicates at low, mid, and high
        if (nums[low] == nums[mid] && nums[mid] == nums[high]) {
            low++;
            high--;
            continue;
        }

        // Check if the left half is sorted
        if (nums[low] <= nums[mid]) {
            // Check if the target lies within the sorted left half
            if (target >= nums[low] && target < nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } 
        // Otherwise, the right half must be sorted
        else {
            // Check if the target lies within the sorted right half
            if (target > nums[mid] && target <= nums[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return false;
}
