/**冒泡排序
* 原理：比较相邻两个参数，小的排前面
* 时间复杂度为O(n2)
**/


/*对象 int 类型
* 注：在原数据上进行排序
*/
void bubbleSortIntValOR(int *target, int len)
{
    unsigned int i, j;
    for(i = 0; i < len - 1; i++)
    {
        for(j = 0; j < len - 1; j++)
        {
            if(target[j] > target[j+1])
            {
                target[j] = target[j]^target[j+1];
                target[j+1] = target[j]^target[j+1];
                target[j] = target[j]^target[j+1];
            }
        }
    }
}