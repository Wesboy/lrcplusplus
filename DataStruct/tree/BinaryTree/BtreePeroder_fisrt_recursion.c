/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void searchTree(struct TreeNode* p, int *len)
{
    int ret;
    if(p != NULL)
    {
        ret = p->val;
        *len+=1;
    }
    if(p->left != NULL)
    {
        searchTree(p->left, len);
    }
    if(p->right != NULL)
    {
        searchTree(p->right, len);
    }

}

void searchTreeVal(struct TreeNode* p, int *dat, int *index)
{
    if(p != NULL)
    {
        dat[*index] = p->val;
        *index += 1;
    }
    if(p->left != NULL)
    {
        searchTreeVal(p->left, dat, index);
    }
    if(p->right != NULL)
    {
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

    int nodeLen = 0, index = 0;
    struct TreeNode *p = root;

    searchTree(p, &nodeLen);

    *returnSize = nodeLen;

    result = (int *)malloc(nodeLen*sizeof(int));
    if(result)
    {
        p = root;
        searchTreeVal(p, result, &index);
    }

    return result;


}