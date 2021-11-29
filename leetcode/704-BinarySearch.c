/**
 * @file 704-BinarySearch.c
 * @author chenweipeng (bg_weapon@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-29
 * 
 * @copyright Copyright (c) 2021
 * 
 * 
 * 704. Binary Search
 * Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 *  
 * Example 1:
 * 
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 * Example 2:
 * 
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 *  
 * 
 * Constraints:
 * 
 * 1 <= nums.length <= 104
 * -104 < nums[i], target < 104
 * All the integers in nums are unique.
 * nums is sorted in ascending order.
 * 
 */



/**
 * @brief 采用二分法 
 * 
 * 
 * @param nums 
 * @param numsSize 
 * @param target 
 * @return ** int 
 */


int search(int* nums, int numsSize, int target){
	
	int ret = -1;
	
	if(numsSize > 0)
	{
	
		int first = 0;
		int last = numsSize - 1;
		int mid = (first+last)/2;

        if(nums[mid] == target)
            ret = mid;
        else
		{
            while(first <= last){
                if(nums[mid] > target)
                {
                    last = mid - 1;
                    
                }
                else if(nums[mid] < target)
                {
                    first = mid + 1;
                }
                else
                {
                    ret = mid;
                    break;
                }
                // mid = (first + last)/2;
                mid = first + (last-first)/2; //防止索引范围溢出
            }
        }
	}
	
	return ret;
}