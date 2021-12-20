/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

void searchTreeVal(struct TreeNode* p, int *dat, int *index)
{
    if(p != NULL)
    {
        dat[*index] = p->val;
        *index += 1;
		searchTreeVal(p->left, dat, index);
		searchTreeVal(p->right, dat, index);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    int *result = NULL;
    *returnSize = 0;
    if(root == NULL)
        return result;

    struct TreeNode *p = root;

    result = (int *)malloc(100*sizeof(int));
    if(result)
    {
        p = root;
        searchTreeVal(p, result, returnSize);
    }

    return result;
}