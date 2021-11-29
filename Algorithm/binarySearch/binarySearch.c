


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

		while(first <= last){
			// mid = (first + last)/2;
			int mid = first + (last-first)/2; //防止索引范围溢出
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
		}
        
	}
	
	return ret;
}