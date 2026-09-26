long long countSubarrays(int* nums, int numsSize, long long k) {
    long long totalSubarrays = 0;
    long long currentSum = 0;
    int left = 0;

    for (int right = 0; right < numsSize; right++) {
        // Expand the window by adding the current element
        currentSum += nums[right];

        // Explicitly cast window length to long long to prevent integer overflow
        while (left <= right && currentSum * (long long)(right - left + 1) >= k) {
            currentSum -= nums[left];
            left++;
        }

        // Add the total count of valid subarrays ending at the current right pointer
        totalSubarrays += (right - left + 1);
    }

    return totalSubarrays;
}
