/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

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
    struct TreeNode *stackNode[100]; //栈 
    int top = -1; //栈顶

    if(result)
    {
        p = root;
        while(top > -1 || p!= NULL)
        {
            while(p != NULL)
            {
                result[(*returnSize)++] = p->val;
                stackNode[++top] = p;
                p = p->left;
            }
            p = stackNode[top--];
            p = p->right;
        }
    }

    return result;

}