
/**
*	输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
*
*	例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
**/


/**
* 前序排序：遍历顺序规则为【根左右】
* 中序遍历：遍历顺序规则为【左根右】
* 后序遍历：遍历顺序规则为【左右根】
*
*/

#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
**/
 
class Solution {
	
	
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	
	
public:

	
	TreeNode* ConstructBinaryTree(vector<int> pre, int pres, int pree, vector<int> vin, int vins, int vine)
    {
        if(pres > pree || vins > vine)
        {
            return NULL;
        }
        
        TreeNode *root = new TreeNode(pre[pres]);
		int i;
		
		
		for(i = vins; i<= vine; i++){
            if(vin[i] == pre[pres]){
                root->left = ConstructBinaryTree(pre, pres+1, pres+i-vins, vin, vins, i-1);
                root->right = ConstructBinaryTree(pre, pres+i-pres+1, pree, vin, i+1, vine);
                break;
            }
        }
		
		return root;
    }

    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
		
		if(pre.size() == 0 || vin.size() == 0)
			return NULL;
	
		
		return ConstructBinaryTree(pre, 0, pre.size()-1, vin, 0, vin.size()-1);
    }
	

};


int main()
{
	int pre_i[] = {1,2,4,7,3,5,6,8};
	int vin_i[] = {4,7,2,1,5,3,8,6};
	vector<int>::iterator it;
	int i;
	int len = sizeof(pre_i)/sizeof(int);
	
	Solution sl;
	
	vector<int> pre_test;
	pre_test.insert(pre_test.begin(), pre_i, pre_i+(sizeof(pre_i)/sizeof(int)));
	vector<int> vin_test;
	vin_test.insert(vin_test.begin(), vin_i, vin_i+(sizeof(vin_i)/sizeof(int)));
	
	sl.reConstructBinaryTree(pre_test, vin_test);

	return 0;
}