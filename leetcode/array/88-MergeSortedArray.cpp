/**************************************************************************
Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

Example 1:

Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.
Example 2:

Given nums = [0,0,1,1,1,2,2,3,3,4],

Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.

It doesn't matter what values are set beyond the returned length.
**************************************************************************/


#include <iostream>
#include <vector>


using namespace std;

int main()
{
    int test1[] = {1, 2, 3, 0, 0, 0};
    int test2[] = {4, 5};
    int i;

    vector<int> p;
    vector<int> q;
    p.insert(p.begin(), test1, test1+(sizeof(test1)/sizeof(int)));
    q.insert(q.begin(), test2, test2+(sizeof(test2)/sizeof(int)));

    cout<<"p addr="<<&p<<endl;
    cout<<"q addr="<<&q<<endl;
    p.swap(q);

    cout<<"p addr="<<&p<<endl;
    cout<<"q addr="<<&q<<endl;
    for(i = 0; i < q.size(); i++)
        cout<<q[i];
    cout<<endl;
    for(i = 0; i < p.size(); i++)
        cout<<p[i]<<endl;

    return 0;
}
