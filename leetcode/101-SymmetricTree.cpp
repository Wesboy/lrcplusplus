
/***
*
*
	Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

	For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

		1
	   / \
	  2   2
	 / \ / \
	3  4 4  3
	 

	But the following [1,2,2,null,3,null,3] is not:

		1
	   / \
	  2   2
	   \   \
	   3    3
*
**/

#include <iostream>

using namespace std;



class Solution {

public:	
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	
	TreeNode* this_p;
public:
	void TreeNodeCreate(TreeNode* p)
	{
		TreeNode* new_p_t = new TreeNode(1);
		TreeNode* new_p_left = new TreeNode(2);
		TreeNode* new_p_right = new TreeNode(2);
		
		new_p_t->left = new_p_left;
		new_p_t->right = new_p_right;
		
		p = new_p_t;
		this_p = new_p_t;
		
	}
	
	void printTreeNode(TreeNode* tn)
	{
		if(tn == NULL){
			cout<<"tn NULL"<<endl;
			return;
		}
		cout<<tn->val;
		if(tn->left!=NULL)
			printTreeNode(tn->left);
		
		if(tn->right!=NULL)
			printTreeNode(tn->right);
	}
	
	int isMirror(TreeNode* left, TreeNode* right)
	{
		if(left != NULL && right != NULL)
		{
			if(left->val == right->val)
			{
				if(!isMirror(left->left, right->right))
					return false;
				if(!isMirror(right->left, left->right))
					return false;
			}
			else
				return false;
		}
		else if(NULL == left || NULL == right)
		{
			if(left != right)
				return false;
		}
		return true;
	}
	
    bool isSymmetric(TreeNode* root) {
		if(root == NULL)
			return false;
        return isMirror(root->left, root->right);
    }
};

int main()
{
	Solution sl;
	bool ret;
	Solution::TreeNode* p;
	
	sl.TreeNodeCreate(p);
	
	sl.printTreeNode(sl.this_p);
	cout<<endl;
	
	ret = sl.isSymmetric(sl.this_p);
	cout<<ret<<endl;
	
	return 0;
}