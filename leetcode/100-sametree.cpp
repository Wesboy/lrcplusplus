
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
/***
*
*
*	Given two binary trees, write a function to check if they are the same or not.
*
*	Two binary trees are considered the same if they are structurally identical and the nodes have the same value.
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
	TreeNode* this_q;
	
public:
	void TreeNodeCreate(TreeNode* p, TreeNode* q)
	{
		TreeNode* new_p_t = new TreeNode(1);
		TreeNode* new_p_left = new TreeNode(2);
		TreeNode* new_p_right = new TreeNode(3);
		
		new_p_t->left = new_p_left;
		new_p_t->right = new_p_right;
		
		p = new_p_t;
		this_p = new_p_t;
		
		TreeNode* new_q_t = new TreeNode(1);
		TreeNode* new_q_left = new TreeNode(2);
		TreeNode* new_q_right = new TreeNode(3);
		
		new_q_t->left = new_q_left;
		new_q_t->right = new_q_right;
		
		q = new_q_t;
		this_q = new_q_t;
		
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
	
    bool isSameTree(TreeNode* p, TreeNode* q) {
        /*Front sort*/
		if(p != NULL && q != NULL)
		{	
			if(p->val == q->val)
			{
				if(p->left != NULL && q->left != NULL)
				{
					if(!isSameTree(p->left, q->left))
						return false;
				}
				else if(p->left == NULL || q->left == NULL)
				{
					if(p->left != q->left)
						return false;
				}
				
				if(p->right != NULL && q->right != NULL)
				{
					if(!isSameTree(p->right, q->right))
						return false;
				}
				else if(p->right == NULL || q->right == NULL)
				{
					if(p->right != q->right)
						return false;
				}
				
			}
			else
				return false;
		}
		else if(NULL == p || NULL == q)
		{
			if(p != q)
				return false;
		}
		return true;
		
    }
};

int main()
{
	Solution sl;
	bool ret;
	Solution::TreeNode* p;
	Solution::TreeNode* q;
	
	sl.TreeNodeCreate(p, q);
	
	sl.printTreeNode(sl.this_p);
	cout<<endl;
	sl.printTreeNode(sl.this_q);
	cout<<endl;
	ret = sl.isSameTree(sl.this_p, sl.this_q);
	
	cout<<ret<<endl;
	
	return 0;
}